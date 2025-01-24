#include "SystemEngineer.h"
#include "DxLib.h"

namespace
{
	constexpr int kAddScore = 100;		// スコア加算値
	constexpr int kTimer = 500;			// タイマー
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
	if (m_FrameCounter == 60)
	{
		m_Timer--;
		m_FrameCounter = 0;
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
	if (m_Timer >= 0 && m_Timer < 10)
	{
		DrawFormatString(1000, 30, 0xff0000, "残り時間:00%d", m_Timer, true);
	}
	else if (m_Timer >= 10 && m_Timer < 100)
	{
		DrawFormatString(1000, 30, 0xff0000, "残り時間:0%d", m_Timer, true);
	}
	else if (m_Timer >= 100 && m_Timer < 1000)
	{
		DrawFormatString(1000, 30, 0xff0000, "残り時間:%d", m_Timer, true);
	}
	if (m_Score >= 0 && m_Score < 10)
	{
		DrawFormatString(1000, 60, 0xff0000, "スコア:00000%d", m_Score, true);
	}
	else if (m_Score >= 10 && m_Score < 100)
	{
		DrawFormatString(1000, 60, 0xff0000, "スコア:0000%d", m_Score, true);
	}
	else if (m_Score >= 100 && m_Score < 1000)
	{
		DrawFormatString(1000, 60, 0xff0000, "スコア:000%d", m_Score, true);
	}
	else if (m_Score >= 1000 && m_Score < 10000)
	{
		DrawFormatString(1000, 60, 0xff0000, "スコア:00%d", m_Score, true);
	}
	else if (m_Score >= 10000 && m_Score < 100000)
	{
		DrawFormatString(1000, 60, 0xff0000, "スコア:0%d", m_Score, true);
	}
	else if (m_Score >= 100000 && m_Score < 1000000)
	{
		DrawFormatString(1000, 60, 0xff0000, "スコア:%d", m_Score, true);
	}
	else
	{
		DrawString(1000, 60, "スコア:oversukoa",0xff0000,true);
	}
#ifdef _DEBUG
	DrawFormatString(1000, 90, 0xff0000, "スコア:%d", m_Score, true);
#endif // _DEBUG
}
