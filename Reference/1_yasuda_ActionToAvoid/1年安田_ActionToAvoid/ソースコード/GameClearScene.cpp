#include "DxLib.h"
#include "Input.h"
#include "SceneManager.h"
#include "GameClearScene.h"
#include "GameOverScene.h"
#include "GamePlayingScene.h"
#include "TitleScene.h"
#include "Game.h"
#include "Pad.h"

#include <cassert>

namespace
{
	//キャラクターの描画サイズ
	constexpr int kDrawWidth = 32;
	constexpr int kDrawHeight = 32;

	constexpr int kGoalDrawWidth = 64;
	constexpr int kGoalDrawHeight = 64;

	//速度
	constexpr float kSpeed = 5.0f;

	//キャラクターのアニメーション
	constexpr int kUseFrame[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, };
	//アニメーション１コマのフレーム数
	constexpr int kAnimFrameNum = 4;
	//アニメーションの１サイクルのフレーム数
	constexpr int kAnimFrameCycle = _countof(kUseFrame) * kAnimFrameNum;

	//ゴールのアニメーション
	constexpr int kGoalUseFrame[] = { 0, 1, 2, 3, 4, 5, 6, 7, };
	//アニメーション１コマのフレーム数
	constexpr int kGoalAnimFrameNum = 6;
	//アニメーションの１サイクルのフレーム数
	constexpr int kGoalAnimFrameCycle = _countof(kGoalUseFrame) * kGoalAnimFrameNum;

	constexpr int kFadeScreenWidth = 1280;
	constexpr int kFadeScreenHeight = 720;

	constexpr int kFadeFrame = 60;

	constexpr int kVolume = 128;

	constexpr int kTitlePosXLeft = 540;
	constexpr int kTitlePosXRight = 490;
	constexpr int kTitlePosYTop = 740;
	constexpr int kTitlePosYBottom = 590;
}

GameClearScene::GameClearScene(SceneManager& manager) :
	Scene(manager),
	m_titleHandle01	(-1),
	m_bgHandle		(-1),
	m_bgmHandle		(-1),
	m_frame			(0),
	m_animFrame		(0),
	m_clearFrame	(0),
	m_goalFrame		(0),
	m_playerPosX	(Game::kScreenWidth * 0.5),
	m_playerPosY	(420.0f),
	m_goalPosX		(Game::kScreenWidth * 0.5),
	m_goalPosY		(400),
	m_moveX			(0.0f),
	m_moveY			(0.0f),
	m_dir			(kWalkRight),
	m_isTurn		(false),
	m_isAction		(false),
	m_isClear		(true),
	nowButton		(Title),
	m_pad			(GetJoypadInputState(DX_INPUT_KEY_PAD1))

{


	m_handle = LoadGraph("date/image/GameClear.png");
	assert(m_handle >= 0);

	m_goalHandle = LoadGraph("date/image/Goal.png");
	assert(m_goalHandle >= 0);

	m_bgHandle = LoadGraph("date/image/Bg001.png");
	assert(m_bgHandle >= 0);

	m_playerHandle = LoadGraph("date/image/Player.png");
	assert(m_playerHandle >= 0);

	m_titleHandle01 = LoadGraph("date/image/Title004.png");
	assert(m_titleHandle01 >= 0);

	//BGMをロード
	m_bgmHandle = LoadSoundMem("date/sound/bgm/GameClearBgm.mp3");

	//SEロード
	m_seHandle001 = LoadSoundMem("date/sound/se/decisionSe.wav");
	m_seHandle002 = LoadSoundMem("date/sound/se/selectSe.wav");
	
	//BGMを流す
	PlaySoundMem(m_bgmHandle, DX_PLAYTYPE_LOOP);

	m_frame = 60;
	updateFunc_ = &GameClearScene::FadeInUpdate;
	drawFunc_ = &GameClearScene::FadeDraw;
}

GameClearScene::~GameClearScene()
{
	//メモリからグラフィックを削除
	DeleteGraph(m_handle);
	DeleteGraph(m_playerHandle);
	DeleteGraph(m_bgHandle);
	DeleteGraph(m_goalHandle);
	DeleteGraph(m_titleHandle01);


	//BGMを削除
	DeleteSoundMem(m_bgmHandle);

	//SE削除
	DeleteSoundMem(m_seHandle001);
	DeleteSoundMem(m_seHandle002);
}

void GameClearScene::FadeInUpdate(Input&)
{
	m_frame--;
	if (m_frame <= 0) {
		updateFunc_ = &GameClearScene::NormalUpdate;
		drawFunc_ = &GameClearScene::NormalDraw;
	}
}

void GameClearScene::NormalUpdate(Input& input)
{
	ChangeVolumeSoundMem(kVolume, m_bgmHandle);
	ChangeVolumeSoundMem(kVolume, m_seHandle001);
	ChangeVolumeSoundMem(kVolume, m_seHandle002);

	/*　選択したら別々のシーンに移動する　*/
	Pad::Update();
	

	if (nowButton == Title && Pad::IsTrigger(PAD_INPUT_1))
	{
		StopSoundMem(m_bgmHandle);
		PlaySoundMem(m_seHandle001, DX_PLAYTYPE_BACK, true);//決定音
		updateFunc_ = &GameClearScene::FadeOutUpdate;
		drawFunc_ = &GameClearScene::FadeDraw;
		m_frame = 0;
	}
}

void GameClearScene::FadeOutUpdate(Input&)
{
	m_frame++;
	if (m_frame >= kFadeFrame)
	{
		if (nowButton == Title)
		{
			manager_.ChangeScene(new TitleScene(manager_));
		}
	}
}

void GameClearScene::FadeDraw()
{
	//背景とクリアロゴの描画
	DrawGraph(0, 0, m_bgHandle, false);
	if (m_isClear)
	{
		DrawGraph(Game::kScreenWidth * 0.25, 0, m_handle, true);
	}

	int goalAnimFrame = m_goalFrame / kGoalAnimFrameNum;

	int GsrcX = kGoalUseFrame[goalAnimFrame] * kGoalDrawWidth;
	int GsrcY = kGoalDrawHeight * 0;

	DrawRectRotaGraph(m_goalPosX, m_goalPosY, GsrcX, GsrcY, kGoalDrawWidth, kGoalDrawHeight, 2.0, 0.0, m_goalHandle, true, false);

	DrawExtendGraph(kTitlePosXLeft, kTitlePosXRight, kTitlePosYTop, kTitlePosYBottom, m_titleHandle01, true);
	

	int animFrame = m_animFrame / kAnimFrameNum;

	int srcX = kUseFrame[animFrame] * kDrawWidth;
	int srcY = kDrawHeight * m_dir;

	for (int i = 0; i < 3; i++)
	{
		DrawRectRotaGraph(m_playerPosX + 90 * i, m_playerPosY, srcX, srcY, kDrawWidth, kDrawHeight, 3.0, 0.0, m_playerHandle, true, m_isTurn);
	}


	//フェード暗幕
	int alpha = 255 * (float)m_frame / 60.0f;
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, kFadeScreenWidth, kFadeScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void GameClearScene::NormalDraw()
{

}

void GameClearScene::Update(Input& input)
{
	m_playerPosX += m_moveX;

	ChangeVolumeSoundMem(kVolume, m_bgmHandle);
	ChangeVolumeSoundMem(kVolume, m_seHandle001);
	ChangeVolumeSoundMem(kVolume, m_seHandle002);

	if (m_playerPosX > 960) m_isTurn = true;
	if (m_playerPosX < 220) m_isTurn = false;

	if (m_isTurn)
	{
		m_moveX = -kSpeed;

	}
	else if (!m_isTurn)
	{
		m_moveX = kSpeed;
	}
	
	m_goalFrame++;
	if (m_goalFrame >= kGoalAnimFrameCycle) m_goalFrame = 0;

	m_animFrame++;
	if (m_animFrame >= kAnimFrameCycle) m_animFrame = 0;

	(this->*updateFunc_)(input);
}

void GameClearScene::Draw()
{
	//背景とクリアロゴの描画
	DrawGraph(0, 0, m_bgHandle, false);

	if (m_isClear)
	{
		DrawGraph(Game::kScreenWidth * 0.25, 0, m_handle, true);
	}

	int goalAnimFrame = m_goalFrame / kGoalAnimFrameNum;

	int GsrcX = kGoalUseFrame[goalAnimFrame] * kGoalDrawWidth;
	int GsrcY = kGoalDrawHeight * 0;

	DrawRectRotaGraph(m_goalPosX, m_goalPosY, GsrcX, GsrcY, kGoalDrawWidth, kGoalDrawHeight, 2.0, 0.0, m_goalHandle, true, false);

	DrawExtendGraph(kTitlePosXLeft, kTitlePosXRight, kTitlePosYTop, kTitlePosYBottom, m_titleHandle01, true);


	int animFrame = m_animFrame / kAnimFrameNum;

	int srcX = kUseFrame[animFrame] * kDrawWidth;
	int srcY = kDrawHeight * m_dir;

	for (int i = 0; i < 3; i++)
	{
		DrawRectRotaGraph(m_playerPosX + 90 * i, m_playerPosY, srcX, srcY, kDrawWidth, kDrawHeight, 3.0, 0.0, m_playerHandle, true, m_isTurn);
	}


	(this->*drawFunc_)();
}
