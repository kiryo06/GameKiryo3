#include "EfectColor.h"
#include "DxLib.h"
#include "Game.h"

EfectColor::EfectColor() :
	m_color(0xffffff),
	m_rad(0),
	m_speed(15),
	m_isStart(false),
	m_isClear(false),
	m_isReduct(true),
	m_isApp(true),
	m_goalRad(0)
{
	m_pos = { 0,0 };
	m_goalPos = { 0,0 };
}

EfectColor::~EfectColor()
{
}

void EfectColor::Init(Vec2 pos, int color)
{
	m_firstPos = pos;
	m_pos = m_firstPos;
	m_color = color;
	m_isStart = true;
}

void EfectColor::Update()
{
	if (m_isStart)
	{
		if (m_rad < 800) m_rad += m_speed;
		else
		{
			m_isStart = false;
		}
	}
	if (m_goalRad > 0) m_goalRad -= m_speed * 2;
	
}

void EfectColor::Draw()
{
	if (m_rad > 0)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - static_cast<int>(m_rad * 0.5f));
		for (int i = 0; i <= 10; i++)
		{
			if (i == 0)
				DrawCircle(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), m_rad - i, 0xffffff, false);
			else
				DrawCircle(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), m_rad - i, m_color, false);
		}
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}

	if (m_isClear && m_isApp)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - static_cast<int>(m_goalRad * 0.25f + 50));
		for (int i = 0; i <= 10; i++)
		{
			if (i == 0)
				DrawCircle(static_cast<int>(m_goalPos.x), static_cast<int>(m_goalPos.y), m_goalRad - i, 0xffffff, false);
			else
				DrawCircle(static_cast<int>(m_goalPos.x), static_cast<int>(m_goalPos.y), m_goalRad - i, m_color, false);

			if (m_goalRad <= 0) m_isApp = false;
		}
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
}

void EfectColor::ClearChack(int efeNum, Vec2 goalPos)
{
	m_isClear = true;

	if (m_isReduct)
	{
		m_isReduct = false;
		m_goalPos = goalPos;
		m_goalRad = 1500 + efeNum * 15;
	}
}

void EfectColor::Reset()
{ 
	m_pos = m_firstPos; 
	m_rad = 0;
	m_isStart = false;
	m_isClear = false;
	m_isReduct = true;
	m_isApp = true;
	m_goalRad = 0;
}
