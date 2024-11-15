#include "DxLib.h"
#include "Input.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "OperationScene.h"
#include "GamePlayingScene.h"
#include "GameOverScene.h"
#include "GameClearScene.h"
#include "Game.h"
#include "Pad.h"
#include <cassert>

namespace
{
	//�L�����N�^�[�̕`��T�C�Y
	constexpr int kDrawWidth = 32;
	constexpr int kDrawHeight = 32;

	//���x
	constexpr float kSpeed = 4.0f;
	//����
	constexpr float kAccel = 0.5f;

	//�d��
	constexpr float kGravity = 1.0f;
	//�W�����v��
	constexpr float kJumpAcc = -20.0f;

	//�L�����N�^�[�̃A�j���[�V����
	constexpr int kUseFrame[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
	//�A�j���[�V�����P�R�}�̃t���[����
	constexpr int kAnimFrameNum = 4;
	//�A�j���[�V�����̂P�T�C�N���̃t���[����
	constexpr int kAnimFrameCycle = _countof(kUseFrame) * kAnimFrameNum;

	//�{�^���̕`��T�C�Y
	constexpr int kDrawButtonSize = 16;

	//�{�^���̃A�j���[�V����
	constexpr int kButtonUseFrame[] = { 0,1,2 };
	//�{�^���̂P�R�}�̃t���[����
	constexpr int kButtonAnimFrameNum = 16;
	//�{�^���̃A�j���[�V�����̂P�T�C�N���̃t���[����
	constexpr int kButtonAnimFrameCycle = _countof(kButtonUseFrame) * kButtonAnimFrameNum;

	constexpr float kHalf = 0.5f;
	constexpr int kVolume = 128;

}

OperationScene::OperationScene(SceneManager& manager):
	Scene(manager),
	m_explationHandle	(-1),
	m_playerHandle01	(-1),
	m_playerHandle02	(-1),
	m_buttonHandle		(-1),
	m_bgmHandle			(-1),
	m_seHandle001		(-1),
	m_seHandle002		(-1),
	m_animFrame			(0),
	m_buttonAnimFrame	(0),
	m_animCount			(0),
	m_jumpCount			(0),
	m_playerPosX		(Game::kScreenWidth * kHalf),
	m_playerPosY		(700),
	m_moveX				(0.0f),
	m_moveY				(0.0f),
	m_dir				(kNutral),
	m_frame				(60),
	m_isRight			(true),
	m_isLeft			(false),
	m_isAnimJump		(false),
	m_isJump			(false),
	m_isAnimTurn		(false),
	m_updateFunc		(&OperationScene::FadeInUpdate),
	m_drawFunc			(&OperationScene::FadeDraw)
{
	//�O���t�B�b�N�����[�h
	m_explationHandle = LoadGraph("date/image/Explation.png");
	assert(m_explationHandle >= 0);

	m_playerHandle01 = LoadGraph("date/image/Player001.png");
	assert(m_playerHandle01 >= 0);
	m_playerHandle02 = LoadGraph("date/image/PlayerJump.png");
	assert(m_playerHandle02 >= 0);

	m_buttonHandle = LoadGraph("date/image/button.png");
	assert(m_buttonHandle >= 0);

	//BGM�����[�h
	m_bgmHandle = LoadSoundMem("date/sound/bgm/OperationBgm.mp3");

	//SE�����[�h
	m_seHandle001 = LoadSoundMem("date/sound/se/jumpSe.wav");
	m_seHandle002 = LoadSoundMem("date/sound/se/cancelSe.wav");

	//BGM�𗬂�
	PlaySoundMem(m_bgmHandle, DX_PLAYTYPE_LOOP);


}

OperationScene::~OperationScene()
{
	DeleteGraph(m_explationHandle);
	DeleteGraph(m_playerHandle01);
	DeleteGraph(m_playerHandle02);
	DeleteGraph(m_buttonHandle);

	//BGM���폜
	DeleteSoundMem(m_bgmHandle);

	//SE�폜
	DeleteSoundMem(m_seHandle001);
	DeleteSoundMem(m_seHandle002);
}

void OperationScene::FadeInUpdate(Input&)
{
	ChangeVolumeSoundMem(kVolume, m_bgmHandle);
	ChangeVolumeSoundMem(kVolume, m_seHandle001);
	ChangeVolumeSoundMem(kVolume, m_seHandle002);

	m_frame--;
	if (m_frame <= 0) {
		m_updateFunc = &OperationScene::NormalUpdate;
		m_drawFunc = &OperationScene::NormalDraw;
	}
}

void OperationScene::NormalUpdate(Input& input)
{
	ChangeVolumeSoundMem(kVolume, m_bgmHandle);
	ChangeVolumeSoundMem(kVolume, m_seHandle001);
	ChangeVolumeSoundMem(kVolume, m_seHandle002);

	if (input.IsTriggered("OK") || Pad::IsTrigger(PAD_INPUT_2)) {
		StopSoundMem(m_bgmHandle);
		PlaySoundMem(m_seHandle002, DX_PLAYTYPE_BACK, true);//���艹
		m_updateFunc = &OperationScene::FadeOutUpdate;
		m_drawFunc = &OperationScene::FadeDraw;
		m_frame = 0;
	}
}

void OperationScene::FadeOutUpdate(Input&)
{
	m_frame++;
	if (m_frame >= 30)
	{
		manager_.ChangeScene(new TitleScene(manager_));
	}
}

void OperationScene::FadeDraw()
{
	DrawGraph(0, 0, m_explationHandle, false);

	int buttonAnimFrame = m_buttonAnimFrame / kButtonAnimFrameNum;

	int BsrcX = kButtonUseFrame[buttonAnimFrame] * kDrawButtonSize;
	int BsrcY = kDrawButtonSize * 1;

	DrawRectRotaGraph(320, 660, BsrcX, BsrcY, kDrawButtonSize, kDrawButtonSize, 3.0, 0.0, m_buttonHandle, true, false);

	int animFrame = m_animFrame / kAnimFrameNum;

	int srcX = kUseFrame[animFrame] * kDrawWidth;
	int srcY = kDrawHeight * m_dir;

	if (m_isAnimJump)
	{
		DrawRectRotaGraph(m_playerPosX + 9, m_playerPosY + 6, 0, 0, kDrawWidth, kDrawHeight, 3.0, 0.0, m_playerHandle02, true, m_isAnimTurn);
	}
	else
	{
		DrawRectRotaGraph(m_playerPosX + 9, m_playerPosY + 6, srcX, srcY, kDrawWidth, kDrawHeight, 3.0, 0.0, m_playerHandle01, true, m_isAnimTurn);
	}

	//�t�F�[�h�Ö�
	int alpha = 255 * (float)m_frame / 30.0f;
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 1280, 720, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void OperationScene::NormalDraw()
{
}


void OperationScene::Init()
{

}

void OperationScene::Update(Input& input)
{
	Pad::Update();
	m_dir = kNutral;

	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	m_moveX = 0.0f;

	if (pad & PAD_INPUT_LEFT)
	{
		m_moveX -= kSpeed;
		m_playerPosX += m_moveX;
		m_isLeft = true;
		m_isAnimTurn = true;
		m_dir = kWalk;
	}
	else
	{
		m_isLeft = false;
	}

	if (pad & PAD_INPUT_RIGHT)
	{
		m_moveX += kSpeed;
		m_playerPosX += m_moveX;
		m_isRight = true;
		m_isAnimTurn = false;
		m_dir = kWalk;
	}
	else
	{
		m_isRight = false;
	}

	//�_�b�V������
	if (pad & PAD_INPUT_3 && m_isRight)
	{
		m_moveX += kAccel;
		m_playerPosX += m_moveX;
		m_dir = kWalk;
		m_isAnimTurn = false;
	}

	if (pad & PAD_INPUT_3 && m_isLeft)
	{
		m_moveX -= kAccel;
		m_playerPosX += m_moveX;
		m_dir = kWalk;
		m_isAnimTurn = true;
	}

	////��ʒ[����o�Ă����Ȃ�
	if (m_playerPosX < 50) m_playerPosX = 50;
	if (m_playerPosX > Game::kScreenWidth - 65) m_playerPosX = Game::kScreenWidth - 65;

	//�A�j���[�V��������
	m_animFrame++;
	if (m_animFrame >= kAnimFrameCycle) m_animFrame = 0;

	//�{�^���̃A�j���[�V��������
	m_buttonAnimFrame++;
	if (m_buttonAnimFrame >= kButtonAnimFrameCycle) m_buttonAnimFrame = 0;

	m_playerPosY += m_moveY;
	m_moveY += kGravity;

	if (m_playerPosY > 650)
	{
		m_playerPosY = 650;
		m_moveY = 0.0f;
		m_isJump = false;
		m_isAnimJump = false;
	}

	if (!m_isJump)
	{
		//�W�����v����
		if (pad & PAD_INPUT_1 && m_isJump == false)
		{
			m_isJump = true;
			m_jumpCount++;
			//m_isAnimJump = true;
		}
		else m_jumpCount = 0;

		if (m_jumpCount == 1 && m_isJump)
		{
			m_moveY = kJumpAcc;
			m_isAnimJump = true;
			PlaySoundMem(m_seHandle001, DX_PLAYTYPE_BACK, true);//�W�����v��

		}
		else m_isJump = false;
	}

	(this->*m_updateFunc)(input);
}

void OperationScene::Draw()
{
	DrawGraph(0, 0, m_explationHandle, false);

	int buttonAnimFrame = m_buttonAnimFrame / kButtonAnimFrameNum;

	int BsrcX = kButtonUseFrame[buttonAnimFrame] * kDrawButtonSize;
	int BsrcY = kDrawButtonSize * 1;

	DrawRectRotaGraph(320, 660, BsrcX, BsrcY, kDrawButtonSize, kDrawButtonSize, 3.0, 0.0, m_buttonHandle, true, false);

	int animFrame = m_animFrame / kAnimFrameNum;
	
	int srcX = kUseFrame[animFrame] * kDrawWidth;
	int srcY = kDrawHeight * m_dir;


	if (m_isAnimJump)
	{
		DrawRectRotaGraph(m_playerPosX + 9, m_playerPosY + 6, 0, 0, kDrawWidth, kDrawHeight, 3.0, 0.0, m_playerHandle02, true, m_isAnimTurn);
	}
	else
	{
		DrawRectRotaGraph(m_playerPosX + 9, m_playerPosY + 6, srcX, srcY, kDrawWidth, kDrawHeight, 3.0, 0.0, m_playerHandle01, true, m_isAnimTurn);
	}

	(this->*m_drawFunc)();
}
