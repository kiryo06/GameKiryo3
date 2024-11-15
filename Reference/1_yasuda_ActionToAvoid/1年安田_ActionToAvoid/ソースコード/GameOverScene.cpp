#include "DxLib.h"
#include "Input.h"
#include "SceneManager.h"
#include "GameOverScene.h"
#include "GamePlayingScene.h"
#include "TitleScene.h"

#include "Game.h"
#include "Pad.h"
#include <cassert>

namespace
{
	//�L�����N�^�[�̕`��T�C�Y
	constexpr int kDrawWidth = 32;
	constexpr int kDrawHeight = 32;

	//���x
	constexpr float kSpeed = 6.0f;

	//�L�����N�^�[�̃A�j���[�V����
	constexpr int kUseFrame[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
	//�A�j���[�V�����P�R�}�̃t���[����
	constexpr int kAnimFrameNum = 4;
	//�A�j���[�V�����̂P�T�C�N���̃t���[����
	constexpr int kAnimFrameCycle = _countof(kUseFrame) * kAnimFrameNum;

	constexpr float kHalf = 0.5f;
	constexpr int kVolume = 128;
}


GameOverScene::GameOverScene(SceneManager& manager):Scene(manager)
{

	m_handle = LoadGraph("date/image/GameOver.png");
	assert(m_handle >= 0);

	m_playerHandle = LoadGraph("date/image/GameOverPlayer.png");
	assert(m_playerHandle >= 0);

	m_retryHandle01 = LoadGraph("date/image/Retry003.png");
	assert(m_retryHandle01 >= 0);
	m_retryHandle02 = LoadGraph("date/image/Retry004.png");
	assert(m_retryHandle02 >= 0);

	m_titleHandle01 = LoadGraph("date/image/Title003.png");
	assert(m_titleHandle01 >= 0);
	m_titleHandle02 = LoadGraph("date/image/Title004.png");
	assert(m_titleHandle02 >= 0);



	//BGM�����[�h
	m_bgmHandle = LoadSoundMem("date/sound/bgm/GameOverBgm.mp3");

	//SE���[�h
	m_seHandle001 = LoadSoundMem("date/sound/se/decisionSe.wav");
	m_seHandle002 = LoadSoundMem("date/sound/se/selectSe.wav");

	//BGM�𗬂�
	PlaySoundMem(m_bgmHandle, DX_PLAYTYPE_LOOP);

	m_frame = 60;
	updateFunc_ = &GameOverScene::FadeInUpdate;
	drawFunc_ = &GameOverScene::FadeDraw;
}

GameOverScene::~GameOverScene()
{
	DeleteGraph(m_handle);
	DeleteGraph(m_playerHandle);

	DeleteGraph(m_retryHandle01);
	DeleteGraph(m_retryHandle02);
	DeleteGraph(m_titleHandle01);
	DeleteGraph(m_titleHandle02);

	//BGM���폜
	DeleteSoundMem(m_bgmHandle);

	//SE�폜
	DeleteSoundMem(m_seHandle001);
	DeleteSoundMem(m_seHandle002);
}

void GameOverScene::FadeInUpdate(Input&)
{
	m_frame--;
	if (m_frame <= 0) {
		updateFunc_ = &GameOverScene::NormalUpdate;
		drawFunc_ = &GameOverScene::NormalDraw;
	}
}

void GameOverScene::NormalUpdate(Input& input)
{
	///*�@�I��������ʁX�̃V�[���Ɉړ�����@*/
	Pad::Update();

	ChangeVolumeSoundMem(kVolume, m_bgmHandle);
	ChangeVolumeSoundMem(kVolume, m_seHandle001);
	ChangeVolumeSoundMem(kVolume, m_seHandle002);

	//��������������Ƃ�
	if (Pad::IsTrigger(PAD_INPUT_UP))
	{
		if (nowButton == Retry)
		{
			nowButton = Title;
			PlaySoundMem(m_seHandle002, DX_PLAYTYPE_BACK, true);//�I����
		}
		else if (nowButton == Title)
		{
			nowButton = Retry;
			PlaySoundMem(m_seHandle002, DX_PLAYTYPE_BACK, true);//�I����
		}
	}

	//���������������Ƃ�
	if (Pad::IsTrigger(PAD_INPUT_DOWN))
	{
		if (nowButton == Retry)
		{
			nowButton = Title;
			PlaySoundMem(m_seHandle002, DX_PLAYTYPE_BACK, true);//�I����
		}
		else if (nowButton == Title)
		{
			nowButton = Retry;
			PlaySoundMem(m_seHandle002, DX_PLAYTYPE_BACK, true);//�I����
		}
	}
	//if (input.IsTriggered("OK") && nowButton == Retry)
	if (nowButton == Retry && Pad::IsTrigger(PAD_INPUT_1))
	{
		StopSoundMem(m_bgmHandle);
		PlaySoundMem(m_seHandle001, DX_PLAYTYPE_BACK, true);//���艹
		updateFunc_ = &GameOverScene::FadeOutUpdate;
		drawFunc_ = &GameOverScene::FadeDraw;
		m_frame = 0;
		m_isActionR = true;


	}
	//if(input.IsTriggered("OK") && nowButton == Title)
	if (nowButton == Title && Pad::IsTrigger(PAD_INPUT_1))
	{
		StopSoundMem(m_bgmHandle);
		PlaySoundMem(m_seHandle001, DX_PLAYTYPE_BACK, true);//���艹
		updateFunc_ = &GameOverScene::FadeOutUpdate;
		drawFunc_ = &GameOverScene::FadeDraw;
		m_frame = 0;
		m_isActionL = true;

	}

}

void GameOverScene::FadeOutUpdate(Input&)
{
	m_frame++;
	if (m_frame >= 180)
	{
		if (nowButton == Retry)
		{
			manager_.ChangeScene(new GamePlayingScene(manager_));
		}
		else if (nowButton == Title)
		{
			manager_.ChangeScene(new TitleScene(manager_));
		}
		
	}
}

void GameOverScene::FadeDraw()
{
	//�ʏ�`��
	//�w�i�ƃQ�[���I�[�o�[���S��`��
	DrawGraph(Game::kScreenWidth * 0.25, 0, m_handle, true);

	if (nowButton == Retry)
	{
		DrawExtendGraph(490, 500, 690, 610, m_retryHandle02, true);
	}
	else
	{
		DrawExtendGraph(540, 500, 740, 610, m_retryHandle01, true);
	}

	if (nowButton == Title)
	{
		DrawExtendGraph(490, 610, 690, 710, m_titleHandle02, true);
	}
	else
	{
		DrawExtendGraph(540, 610, 740, 710, m_titleHandle01, true);
	}

	int animFrame = m_animFrame / kAnimFrameNum;

	int srcX = kUseFrame[animFrame] * kDrawWidth;
	int srcY = kDrawHeight * m_dir;

	DrawRectRotaGraph(m_playerPosX, m_playerPosY , srcX, srcY, kDrawWidth, kDrawHeight, 3.0, 0.0, m_playerHandle, true, m_isTurn);


	//�t�F�[�h�Ö�
	int alpha = 255 * (float)m_frame / 120.0f;
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 1280, 720, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void GameOverScene::NormalDraw()
{

}


void GameOverScene::Update(Input& input)
{
	ChangeVolumeSoundMem(kVolume, m_bgmHandle);
	ChangeVolumeSoundMem(kVolume, m_seHandle001);
	ChangeVolumeSoundMem(kVolume, m_seHandle002);

	m_playerPosX += m_moveX;

	if (m_isActionR)
	{
		m_dir = kWalkRight;
		m_moveX = kSpeed;
		m_isTurn = false;
	}
	else if (m_isActionL)
	{
		m_dir = kWalkRight;
		m_moveX = -kSpeed;
		m_isTurn = true;
	}


	m_animFrame++;
	if (m_animFrame >= kAnimFrameCycle) m_animFrame = 0;

	(this->*updateFunc_)(input);
}

void GameOverScene::Draw()
{
	//�w�i�ƃQ�[���I�[�o�[���S��`��
	//DrawGraph(0, 0, m_bgHandle, false);
	DrawGraph(Game::kScreenWidth * 0.25, 0, m_handle, true);

	if (nowButton == Retry)
	{
		DrawExtendGraph(490, 500, 690, 610, m_retryHandle02, true);
	}
	else
	{
		DrawExtendGraph(540, 500, 740, 610, m_retryHandle01, true);
	}

	if (nowButton == Title)
	{
		DrawExtendGraph(490, 610, 690, 710, m_titleHandle02, true);
	}
	else
	{
		DrawExtendGraph(540, 610, 740, 710, m_titleHandle01, true);
	}

	int animFrame = m_animFrame / kAnimFrameNum;

	int srcX = kUseFrame[animFrame] * kDrawWidth;
	int srcY = kDrawHeight * m_dir;

	DrawRectRotaGraph(m_playerPosX, m_playerPosY , srcX, srcY, kDrawWidth, kDrawHeight, 3.0, 0.0, m_playerHandle, true, m_isTurn);

	(this->*drawFunc_)();
}
