#include "DxLib.h"
#include "Application.h"
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
	//�w�i�X�s�[�h
	constexpr int kBgSpeed = 2;
	constexpr float kSpeed = 8.0f;

	//�L�����N�^�[�̕`��T�C�Y
	constexpr int kDrawWidth = 32;
	constexpr int kDrawHeight = 32;

	//�{�^���̕`��T�C�Y
	constexpr int kDrawButtonSize = 16;


	//�{�^���̃A�j���[�V����
	constexpr int kButtonUseFrame[] = { 0,1,2 };
	//�{�^���̂P�R�}�̃t���[����
	constexpr int kButtonAnimFrameNum = 10;
	//�{�^���̃A�j���[�V�����̂P�T�C�N���̃t���[����
	constexpr int kButtonAnimFrameCycle = _countof(kButtonUseFrame) * kButtonAnimFrameNum;


	//�L�����N�^�[�̃A�j���[�V����
	constexpr int kUseFrame[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
	//�A�j���[�V�����P�R�}�̃t���[����
	constexpr int kAnimFrameNum = 4;
	//�A�j���[�V�����̂P�T�C�N���̃t���[����
	constexpr int kAnimFrameCycle = _countof(kUseFrame) * kAnimFrameNum;

	//�}�W�b�N�i���o�[
	constexpr int kButtonPosXLeft = 860;
	constexpr int kButtonPosXRight = 1060;

	constexpr int kSelectButtonPosXLeft = 910;
	constexpr int kSelectButtonPosXRight = 1160;


	constexpr int kStartPosYTop = 100;
	constexpr int kStartPosYBottom = 200;

	constexpr int kExplanationPosYTop = 250;
	constexpr int kExplanationPosYBottom = 350;

	constexpr int kEndPosYTop = 400;
	constexpr int kEndPosYBottom = 500;

	constexpr int kTitleLogPosXLeft = -100;
	constexpr int kTitleLogPosXRight = 900;
	constexpr int kTitleLogPosYTop = 0;
	constexpr int kTitleLogPosYBottom = 540;

	constexpr int kVolume = 128;

	constexpr int kOperationFadeFrame = 35;
	constexpr int kPlayingFadeFrame = 120;

	constexpr int kdecisionHandleLeft = -10;
	constexpr int kdecisionHandleRight = 190;
	constexpr int kdecisionHandleTop = 630;
	constexpr int kdecisionHandleBottom = 730;

	constexpr int kButtonPosX = 200;
	constexpr int kButtonPosY = 685;
	
	constexpr int kFadeScreenWidth = 1280;
	constexpr int kFadeScreenHeight = 720;

	constexpr float kHalf = 0.5f;
}

TitleScene::TitleScene(SceneManager& manager):
	Scene(manager),
	m_TitleLogHandle	(-1),
	m_bgHandle			(-1),
	m_playerHandle		(-1),
	m_startHandle01		(-1),
	m_explationHandle01 (-1),
	m_optionHandle01	(-1),
	m_endHandle01		(-1),
	m_startHandle02		(-1),
	m_explationHandle02	(-1),
	m_optionHandle02	(-1),
	m_endHandle02		(-1),
	m_decisionHandle	(-1),
	m_buttonHandle		(-1),
	m_areaX				(0),
	m_nowButton			(Start)
{
	

	//�^�C�g���A�w�i�̃O���t�B�b�N�����[�h
	m_TitleLogHandle = LoadGraph("date/image/TitleLogo001.png");
	assert(m_TitleLogHandle >= 0);
	m_bgHandle = LoadGraph("date/image/Bg002.png");
	assert(m_bgHandle >= 0);
	m_playerHandle = LoadGraph("date/image/Player.png");
	assert(m_playerHandle >= 0);


	//�I���̃O���t�B�b�N�����[�h
	m_startHandle01 = LoadGraph("date/image/Start003.png");
	assert(m_startHandle01 >= 0);
	m_startHandle02 = LoadGraph("date/image/Start004.png");
	assert(m_startHandle02 >= 0);

	m_explationHandle01 = LoadGraph("date/image/Explanation003.png");
	assert(m_explationHandle01 >= 0);
	m_explationHandle02 = LoadGraph("date/image/Explanation004.png");
	assert(m_explationHandle02 >= 0);

	m_endHandle01 = LoadGraph("date/image/End003.png");
	assert(m_endHandle01 >= 0);
	m_endHandle02 = LoadGraph("date/image/End004.png");
	assert(m_endHandle02 >= 0);


	m_buttonHandle = LoadGraph("date/image/button.png");
	assert(m_buttonHandle >= 0);
	m_decisionHandle = LoadGraph("date/image/decide001.png");
	assert(m_decisionHandle >= 0);

	//BGM�����[�h
	m_bgmHandle = LoadSoundMem("date/sound/bgm/TitleBgm.mp3");

	//SE�����[�h
	m_seHandle001 = LoadSoundMem("date/sound/se/decisionSe.wav");
	m_seHandle002 = LoadSoundMem("date/sound/se/selectSe.wav");
	m_seHandle003 = LoadSoundMem("date/sound/se/cancelSe.wav");

	//BGM���Đ�
	PlaySoundMem(m_bgmHandle, DX_PLAYTYPE_LOOP);

	m_frame = 60;
	m_updateFunc = &TitleScene::FadeInUpdate;
	m_drawFunc = &TitleScene::FadeDraw;
}

TitleScene::~TitleScene()
{
	//����������O���t�B�b�N���폜
	DeleteGraph(m_TitleLogHandle);
	DeleteGraph(m_bgHandle);
	DeleteGraph(m_playerHandle);

	//�I���̃O���t�B�b�N�폜
	DeleteGraph(m_startHandle01);
	DeleteGraph(m_startHandle02);
	DeleteGraph(m_explationHandle01);
	DeleteGraph(m_explationHandle02);
	DeleteGraph(m_endHandle01);
	DeleteGraph(m_endHandle02);
	
	DeleteGraph(m_decisionHandle);
	DeleteGraph(m_buttonHandle);

	//BGM���폜
	DeleteSoundMem(m_bgmHandle);

	//SE�폜
	DeleteSoundMem(m_seHandle001);
	DeleteSoundMem(m_seHandle002);
}

void TitleScene::FadeInUpdate(Input&)
{
	//�T�E���h�̉��̑傫���ݒ�
	ChangeVolumeSoundMem(kVolume, m_bgmHandle);
	ChangeVolumeSoundMem(kVolume, m_seHandle001);
	ChangeVolumeSoundMem(kVolume, m_seHandle002);

	m_frame--;
	if (m_frame <= 0) {
		m_updateFunc = &TitleScene::NormalUpdate;
		m_drawFunc = &TitleScene::NormalDraw;
	}
}

void TitleScene::NormalUpdate(Input& input)
{
	//�T�E���h�̉��̑傫���ݒ�
	ChangeVolumeSoundMem(kVolume, m_bgmHandle);
	ChangeVolumeSoundMem(kVolume, m_seHandle001);
	ChangeVolumeSoundMem(kVolume, m_seHandle002);

	//��������������Ƃ�
	if (Pad::IsTrigger(PAD_INPUT_UP))
	{
		if (m_nowButton == Start)
		{
			m_nowButton = End;
			PlaySoundMem(m_seHandle002, DX_PLAYTYPE_BACK, true);//�I����
		}
		else if (m_nowButton == Explation)
		{
			m_nowButton = Start;
			PlaySoundMem(m_seHandle002, DX_PLAYTYPE_BACK, true);//�I����
		}
		else if (m_nowButton == End)
		{
			m_nowButton = Explation;
			PlaySoundMem(m_seHandle002, DX_PLAYTYPE_BACK, true);//�I����
		}
	}
	
	//���������������Ƃ�
	if (Pad::IsTrigger(PAD_INPUT_DOWN))
	{
		if (m_nowButton == Start)
		{
			m_nowButton = Explation;
			PlaySoundMem(m_seHandle002, DX_PLAYTYPE_BACK, true);//�I����
		}
		else if (m_nowButton == Explation)
		{
			m_nowButton = End;
			PlaySoundMem(m_seHandle002, DX_PLAYTYPE_BACK, true);//�I����
		}
		else if (m_nowButton == End)
		{
			m_nowButton = Start;
			PlaySoundMem(m_seHandle002, DX_PLAYTYPE_BACK, true);//�I����
		}
	}
	

	if (m_nowButton == Start && Pad::IsTrigger(PAD_INPUT_1))//�Q�[���X�^�[�g
	{
		StopSoundMem(m_bgmHandle);
		PlaySoundMem(m_seHandle001, DX_PLAYTYPE_BACK, true);//���艹
		m_updateFunc = &TitleScene::FadeOutUpdateStart;
		m_drawFunc = &TitleScene::FadeDraw;
		m_frame = 0;
		m_isAction = true;
		m_isStartFade = true;
	}

	if (m_nowButton == Explation && Pad::IsTrigger(PAD_INPUT_1))//�������
	{
		StopSoundMem(m_bgmHandle);
		PlaySoundMem(m_seHandle001, DX_PLAYTYPE_BACK, true);//���艹
		m_updateFunc = &TitleScene::NoFadeOutUpdate;
		m_drawFunc = &TitleScene::FadeDraw;
		m_frame = 0;
		m_isHalfFade = true;
	}

	if (m_nowButton == End && Pad::IsTrigger(PAD_INPUT_1))//�Q�[���I��
	{
		StopSoundMem(m_bgmHandle);
		PlaySoundMem(m_seHandle001, DX_PLAYTYPE_BACK, true);//���艹
		m_updateFunc = &TitleScene::FadeOutUpdate;
		m_drawFunc = &TitleScene::FadeDraw;
		m_frame = 0;
	}

	
}

void TitleScene::FadeOutUpdate(Input&)
{
	if (m_nowButton == End )
	{
		Application::GetInstance().Terminate();
	}
}

void TitleScene::FadeOutUpdateStart(Input&)
{
	m_frame++;
	if (m_frame >= kPlayingFadeFrame)
	{
		if (m_nowButton == Start)
		{
			manager_.ChangeScene(new GamePlayingScene(manager_));
		}
	}

}

void TitleScene::NoFadeOutUpdate(Input&)
{
	m_frame++;
	if (m_frame >= kOperationFadeFrame)
	{
		manager_.ChangeScene(new OperationScene(manager_));
	}
}

void TitleScene::FadeDraw()
{
	//�ʏ�̕`��
	BackScroll(m_areaX, m_bgHandle, Game::kScreenWidth, Game::kScreenHeight);
	DrawExtendGraph(kTitleLogPosXLeft, kTitleLogPosYTop, kTitleLogPosXRight, kTitleLogPosYBottom, m_TitleLogHandle, true);

	//�X�^�[�g���I�����ꂽ��X�^�[�g�{�^���\����ς���
	if (m_nowButton == Start)
	{
		DrawExtendGraph(kButtonPosXLeft, kStartPosYTop, kButtonPosXRight, kStartPosYBottom, m_startHandle02, true);
	}
	else//�������F�̈Ⴄ�X�^�[�g�{�^����\��
	{
		DrawExtendGraph(kSelectButtonPosXLeft, kStartPosYTop, kSelectButtonPosXRight, kStartPosYBottom, m_startHandle01, true);
	}

	if (m_nowButton == Explation)
	{
		DrawExtendGraph(kButtonPosXLeft, kExplanationPosYTop, kButtonPosXRight, kExplanationPosYBottom, m_explationHandle02, true);
	}
	else
	{
		DrawExtendGraph(kSelectButtonPosXLeft, kExplanationPosYTop, kSelectButtonPosXRight, kExplanationPosYBottom, m_explationHandle01, true);
	}

	if (m_nowButton == End)
	{
		DrawExtendGraph(kButtonPosXLeft, kEndPosYTop, kButtonPosXRight, kEndPosYBottom, m_endHandle02, true);
	}
	else
	{
		DrawExtendGraph(kSelectButtonPosXLeft, kEndPosYTop, kSelectButtonPosXRight, kEndPosYBottom, m_endHandle01, true);
	}

	int buttonAnimFrame = m_animFrame / kButtonAnimFrameNum;

	int BsrcX = kButtonUseFrame[buttonAnimFrame] * kDrawButtonSize;
	int BsrcY = kDrawButtonSize * 0;

	DrawExtendGraph(kdecisionHandleLeft, kdecisionHandleTop, kdecisionHandleRight, kdecisionHandleBottom, m_decisionHandle, true);

	DrawRectRotaGraph(kButtonPosX, kButtonPosY, BsrcX, BsrcY, kDrawButtonSize, kDrawButtonSize, 3.0, 0.0, m_buttonHandle, true, false);

	int animFrame = m_animFrame / kAnimFrameNum;

	int srcX = kUseFrame[animFrame] * kDrawWidth;
	int srcY = kDrawHeight * m_dir;

	DrawRectRotaGraph(m_playerPosX, m_playerPosY - 16, srcX, srcY, kDrawWidth, kDrawHeight, 3.0, 0.0, m_playerHandle, true, false);


	//�t�F�[�h�Ö�
	if (m_isStartFade)
	{
		int alpha = 255 * (float)m_frame / 120.0f;
		SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
		DrawBox(0, 0, kFadeScreenWidth, kFadeScreenHeight, 0x000000, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	if (m_isFade)
	{
		int alpha = 255 * (float)m_frame / 60.0f;
		SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
		DrawBox(0, 0, kFadeScreenWidth, kFadeScreenHeight, 0x000000, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	if (m_isHalfFade)
	{
		int alpha = 255 * (float)m_frame / 30.0f;
		SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
		DrawBox(0, 0, kFadeScreenWidth, kFadeScreenHeight, 0x000000, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

void TitleScene::NormalDraw()
{
	
}


void TitleScene::Init()
{
}


void TitleScene::Update(Input& input)
{
	m_animFrame++;
	m_buttonAnimFrame++;

	if (m_animFrame >= kAnimFrameCycle) m_animFrame = 0;

	if (m_animFrame >= kButtonAnimFrameCycle) m_buttonAnimFrame = 0;

	Pad::Update();
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	m_playerPosX += m_moveX;




	if (m_isAction)
	{
		m_moveX = kSpeed;
	}
	else if(!m_isAction)
	{
		m_moveX = kSpeed;
		if (m_playerPosX == Game::kScreenWidth * kHalf)
		{
			m_moveX = 0.0;
		}
	}

	/*�@�w�i�̃X�N���[�������@*/
	m_areaX += kBgSpeed;
	if (m_areaX > Game::kScreenWidth)
	{
		m_areaX = 0;
	}

	//�E�ɔw�i���X�N���[������
	if (m_areaX < 0)
	{
		m_areaX = Game::kScreenWidth;
	}

	(this->*m_updateFunc)(input);
	
}

void TitleScene::Draw()
{
	BackScroll(m_areaX, m_bgHandle, Game::kScreenWidth, Game::kScreenHeight);
	DrawExtendGraph(kTitleLogPosXLeft, kTitleLogPosYTop, kTitleLogPosXRight, kTitleLogPosYBottom, m_TitleLogHandle, true);

	//�X�^�[�g���I�����ꂽ��X�^�[�g�{�^���\����ς���
	if (m_nowButton == Start)
	{
		DrawExtendGraph(kButtonPosXLeft, kStartPosYTop, kButtonPosXRight, kStartPosYBottom, m_startHandle02, true);
	}
	else//�������F�̈Ⴄ�X�^�[�g�{�^����\��
	{
		DrawExtendGraph(kSelectButtonPosXLeft, kStartPosYTop, kSelectButtonPosXRight, kStartPosYBottom, m_startHandle01, true);
	}

	if (m_nowButton == Explation)
	{
		DrawExtendGraph(kButtonPosXLeft, kExplanationPosYTop, kButtonPosXRight, kExplanationPosYBottom, m_explationHandle02, true);
	}
	else
	{
		DrawExtendGraph(kSelectButtonPosXLeft, kExplanationPosYTop, kSelectButtonPosXRight, kExplanationPosYBottom, m_explationHandle01, true);
	}

	if (m_nowButton == End)
	{
		DrawExtendGraph(kButtonPosXLeft, kEndPosYTop, kButtonPosXRight, kEndPosYBottom, m_endHandle02, true);
	}
	else
	{
		DrawExtendGraph(kSelectButtonPosXLeft, kEndPosYTop, kSelectButtonPosXRight, kEndPosYBottom, m_endHandle01, true);
	}
	
	DrawExtendGraph(kdecisionHandleLeft, kdecisionHandleTop, kdecisionHandleRight, kdecisionHandleBottom, m_decisionHandle, true);

	//�{�^���̃A�j���[�V����
	int buttonAnimFrame = m_animFrame / kButtonAnimFrameNum;

	int BsrcX = kButtonUseFrame[buttonAnimFrame] * kDrawButtonSize;
	int BsrcY = 0;

	DrawRectRotaGraph(kButtonPosX, kButtonPosY, BsrcX, BsrcY, kDrawButtonSize, kDrawButtonSize, 3.0, 0.0, m_buttonHandle, true, false);

	//�L�����̃A�j���[�V����
	int animFrame = m_animFrame / kAnimFrameNum;

	int srcX = kUseFrame[animFrame] * kDrawWidth;
	int srcY = kDrawHeight * m_dir;

	DrawRectRotaGraph(m_playerPosX, m_playerPosY - 16, srcX, srcY, kDrawWidth, kDrawHeight, 3.0, 0.0, m_playerHandle, true, false);

	(this->*m_drawFunc)();
}

void TitleScene::BackScroll(const int areaX, const int handle, const int width, const int height)
{
	DrawRectGraph(0, 0, areaX, 0, width, height, handle, false);
	DrawRectGraph(width - areaX, 0, 0, 0, areaX, height, handle, false);
}
