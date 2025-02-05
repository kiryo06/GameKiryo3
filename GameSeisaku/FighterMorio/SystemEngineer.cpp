#include "SystemEngineer.h"
#include "DxLib.h"

namespace
{
	constexpr int kAddScore = 100;						// �X�R�A���Z�l
	constexpr int kTimer = 500;							// �^�C�}�[
	constexpr int kTimerX = 1000;						// �^�C�}�[�\���ʒuX
	constexpr int kTimerY = 30;							// �^�C�}�[�\���ʒuY
	constexpr int kScoreX = 1000;						// �X�R�A�\���ʒuX
	constexpr int kScoreY = 60;							// �X�R�A�\���ʒuY
	constexpr const char* kFontName = "MS �S�V�b�N";	// �t�H���g��
	constexpr int kFontSize = 25;						// �t�H���g�T�C�Y
	constexpr const char* kBGMFile = "data/Sound/BGM_3_Maker.mp3";			// BGM�t�@�C��
}

SystemEngineer::SystemEngineer():
	IsScore(false),
	m_Score(0),
	m_Timer(kTimer),
	m_FrameCounter(0),
	m_fontHandle(0),
	dsad(0),
	m_Bgm(false)
{
}

SystemEngineer::~SystemEngineer()
{
	DeleteFontToHandle(m_fontHandle);
	delete kBGMFile;
}

void SystemEngineer::Init()
{
	m_fontHandle = CreateFontToHandle("kFontName", kFontSize, -1, DX_FONTTYPE_ANTIALIASING);
	if (!m_Bgm)
	{
		PlayMusic(kBGMFile, DX_PLAYTYPE_LOOPBIT);
	}
	PlayMusic(kBGMFile, DX_PLAYTYPE_LOOPBIT);
	//PlayMusicByMemImage(void kBGMFile, )
}

void SystemEngineer::Update()
{
	if (m_Bgm)
	{
		StopMusic();
	}
	m_FrameCounter++;
	if (m_FrameCounter >= 60)
	{
		m_Timer--;
		m_FrameCounter -= 60;
	}
	if (IsScore)
	{
		dsad += kAddScore;
		IsScore = false;
	}
	if (m_Score < dsad)
	{
		m_Score += 3;
		if (m_Score > dsad)
		{
			m_Score = dsad;
		}
		return;
	}
}

void SystemEngineer::Draw()
{
	DrawSetUp();
}

void SystemEngineer::DrawSetUp()
{
	// �c�莞�Ԃ̕\��
	if (m_Timer >= 0 && m_Timer < 10)
	{
		//DrawFormatString(kTimerX, kTimerY, 0xff0000, "�c�莞��:00%d", m_Timer, true);
		DrawFormatStringToHandle(kTimerX, kTimerY, 0x990000, m_fontHandle, "�c�莞��:00%d", m_Timer);
	}
	else if (m_Timer >= 10 && m_Timer < 100)
	{
		//DrawFormatString(kTimerX, kTimerY, 0xff0000, "�c�莞��:0%d", m_Timer, true);
		DrawFormatStringToHandle(kTimerX, kTimerY, 0x990000, m_fontHandle, "�c�莞��:0%d", m_Timer);
	}
	else if (m_Timer >= 100 && m_Timer < 1000)
	{
		//DrawFormatString(kTimerX, kTimerY, 0xff0000, "�c�莞��:%d", m_Timer, true);
		DrawFormatStringToHandle(kTimerX, kTimerY, 0x990000, m_fontHandle, "�c�莞��:%d", m_Timer);
	}
	// �X�R�A�̕\��
	if (m_Score >= 0 && m_Score < 10)
	{
		//DrawFormatString(kScoreX, kScoreY, 0xff0000, "�X�R�A:00000%d", m_Score, true);
		DrawFormatStringToHandle(kScoreX, kScoreY, 0x990000, m_fontHandle, "�X�R�A:00000%d", m_Score, true);
	}
	else if (m_Score >= 10 && m_Score < 100)
	{
		//DrawFormatString(kScoreX, kScoreY, 0xff0000, "�X�R�A:0000%d", m_Score, true);
		DrawFormatStringToHandle(kScoreX, kScoreY, 0x990000, m_fontHandle, "�X�R�A:0000%d", m_Score, true);
	}
	else if (m_Score >= 100 && m_Score < 1000)
	{
		//DrawFormatString(kScoreX, kScoreY, 0xff0000, "�X�R�A:000%d", m_Score, true);
		DrawFormatStringToHandle(kScoreX, kScoreY, 0x990000, m_fontHandle, "�X�R�A:000%d", m_Score, true);
	}
	else if (m_Score >= 1000 && m_Score < 10000)
	{
		//DrawFormatString(kScoreX, kScoreY, 0xff0000, "�X�R�A:00%d", m_Score, true);
		DrawFormatStringToHandle(kScoreX, kScoreY, 0x990000, m_fontHandle, "�X�R�A:00%d", m_Score, true);
	}
	else if (m_Score >= 10000 && m_Score < 100000)
	{
		//DrawFormatString(kScoreX, kScoreY, 0xff0000, "�X�R�A:0%d", m_Score, true);
		DrawFormatStringToHandle(kScoreX, kScoreY, 0x990000, m_fontHandle, "�X�R�A:0%d", m_Score, true);
	}
	else if (m_Score >= 100000 && m_Score < 1000000)
	{
		//DrawFormatString(kScoreX, kScoreY, 0xff0000, "�X�R�A:%d", m_Score, true);
		DrawFormatStringToHandle(kScoreX, kScoreY, 0x990000, m_fontHandle, "�X�R�A:%d", m_Score, true);
	}
	else
	{
		DrawString(kScoreX, kScoreY, "�X�R�A:oversukoa",0xff0000,true);
	}
#ifdef _DEBUG
	DrawFormatString(kScoreX, 90, 0xff0000, "�X�R�A:%d", m_Score, true);
#endif // _DEBUG
}
