#include "SystemEngineer.h"
#include "DxLib.h"

namespace
{
	constexpr int kAddScore = 100;		// スコア加算値
	constexpr int kTimer = 500;			// タイマー
	constexpr int kTimerX = 1000;		// タイマー表示位置X
	constexpr int kTimerY = 30;			// タイマー表示位置Y
	constexpr int kScoreX = 1000;		// スコア表示位置X
	constexpr int kScoreY = 60;			// スコア表示位置Y
}

SystemEngineer::SystemEngineer():
	IsScore(false),
	m_Score(0),
	m_Timer(kTimer),
	m_FrameCounter(0)
{
}

SystemEngineer::~SystemEngineer()
{
}

void SystemEngineer::Init()
{
}

void SystemEngineer::Update()
{
	m_FrameCounter++;
	if (m_FrameCounter >= 60)
	{
		m_Timer--;
		m_FrameCounter -= 60;
	}
	if (IsScore)
	{
		m_Score += kAddScore;
		IsScore = false;
	}
}

void SystemEngineer::Draw()
{
	DrawSetUp();
}

void SystemEngineer::DrawSetUp()
{
	int fontHandle = CreateFontToHandle("MS ゴシック", 25, -1, DX_FONTTYPE_ANTIALIASING);
	// 残り時間の表示
	if (m_Timer >= 0 && m_Timer < 10)
	{
		//DrawFormatString(kTimerX, kTimerY, 0xff0000, "残り時間:00%d", m_Timer, true);
		DrawFormatStringToHandle(kTimerX, kTimerY, 0xff0000, fontHandle, "残り時間:00%d", m_Timer);
	}
	else if (m_Timer >= 10 && m_Timer < 100)
	{
		//DrawFormatString(kTimerX, kTimerY, 0xff0000, "残り時間:0%d", m_Timer, true);
		DrawFormatStringToHandle(kTimerX, kTimerY, 0xff0000, fontHandle, "残り時間:0%d", m_Timer);
	}
	else if (m_Timer >= 100 && m_Timer < 1000)
	{
		//DrawFormatString(kTimerX, kTimerY, 0xff0000, "残り時間:%d", m_Timer, true);
		DrawFormatStringToHandle(kTimerX, kTimerY, 0xff0000, fontHandle, "残り時間:%d", m_Timer);
	}
	// スコアの表示
	if (m_Score >= 0 && m_Score < 10)
	{
		//DrawFormatString(kScoreX, kScoreY, 0xff0000, "スコア:00000%d", m_Score, true);
		DrawFormatStringToHandle(kScoreX, kScoreY, 0xff0000, fontHandle, "スコア:00000%d", m_Score, true);
	}
	else if (m_Score >= 10 && m_Score < 100)
	{
		//DrawFormatString(kScoreX, kScoreY, 0xff0000, "スコア:0000%d", m_Score, true);
		DrawFormatStringToHandle(kScoreX, kScoreY, 0xff0000, fontHandle, "スコア:0000%d", m_Score, true);
	}
	else if (m_Score >= 100 && m_Score < 1000)
	{
		//DrawFormatString(kScoreX, kScoreY, 0xff0000, "スコア:000%d", m_Score, true);
		DrawFormatStringToHandle(kScoreX, kScoreY, 0xff0000, fontHandle, "スコア:000%d", m_Score, true);
	}
	else if (m_Score >= 1000 && m_Score < 10000)
	{
		//DrawFormatString(kScoreX, kScoreY, 0xff0000, "スコア:00%d", m_Score, true);
		DrawFormatStringToHandle(kScoreX, kScoreY, 0xff0000, fontHandle, "スコア:00%d", m_Score, true);
	}
	else if (m_Score >= 10000 && m_Score < 100000)
	{
		//DrawFormatString(kScoreX, kScoreY, 0xff0000, "スコア:0%d", m_Score, true);
		DrawFormatStringToHandle(kScoreX, kScoreY, 0xff0000, fontHandle, "スコア:0%d", m_Score, true);
	}
	else if (m_Score >= 100000 && m_Score < 1000000)
	{
		//DrawFormatString(kScoreX, kScoreY, 0xff0000, "スコア:%d", m_Score, true);
		DrawFormatStringToHandle(kScoreX, kScoreY, 0xff0000, fontHandle, "スコア:%d", m_Score, true);
	}
	else
	{
		DrawString(kScoreX, kScoreY, "スコア:oversukoa",0xff0000,true);
	}
#ifdef _DEBUG
	DrawFormatString(kScoreX, 90, 0xff0000, "スコア:%d", m_Score, true);
#endif // _DEBUG
	DeleteFontToHandle(fontHandle);
}
}
