#include "GoalPoint.h"
#include "Game.h"
#include "DxLib.h"


GoalPoint::GoalPoint() :
	m_isApp(false),
	m_color(0xffffff),
	m_pos(0.0f, 0.0f),
	m_R(255),
	m_G(0),
	m_B(0),
	m_alpha(0),
	m_dir(0),
	m_EfectAngle(180)
{
}

GoalPoint::~GoalPoint()
{
}

void GoalPoint::Init(int& x, int& y)
{
	m_pos = { static_cast<float>(x) * Game::kGraphWidth + Game::kMapStartPosX + Game::kGraphHalfWidth,
				static_cast<float>(y)* Game::kGraphHeight + Game::kMapStartPosY + Game::kGraphHalfHeight };
	m_colRect.SetCenter(0,0,0,0);

	for (int i = 0; i < kCurcleNum; i++)
	{
		m_circlePos[i] = { m_pos.x + cos((45 * i) * 0.0174f * 5) * kCircleMoveDir,
							m_pos.y + sin((45 * i) * 0.0174f * 5) * kCircleMoveDir };
	}
}

void GoalPoint::Update(bool& isClear)
{
	m_isApp = isClear;
	// èåèêÆÇ¢éüëÊìñÇΩÇËîªíËÇïtó^
	if (m_isApp)
	{
		m_colRect.SetCenter(m_pos.x,
			m_pos.y,
			Game::kGraphWidth,
			Game::kGraphHeight);
	}
	else
	{
		m_colRect.SetCenter(0, 0, 0, 0);
	}
	// ì¯Ç…åıÇÁÇπÇÈ
	if (m_B == 0)
	{
		if (!(m_R == 0))
		{
			m_R-= kColorSpeed;
			m_G+= kColorSpeed;
		}
	}
	if (m_R == 0)
	{
		if (!(m_G == 0))
		{
			m_G-= kColorSpeed;
			m_B+= kColorSpeed;
		}
	}
	if (m_G == 0)
	{
		if (!(m_B == 0))
		{
			m_B-= kColorSpeed;
			m_R+= kColorSpeed;
		}
	}
	m_color = (16 * 16 * 16 * 16 * m_R) + (16 * 16 * m_G) + (m_B);
}

void GoalPoint::Draw()
{
	if (m_isApp)
	{
		if (m_alpha < 255) m_alpha += 5;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alpha);
	}
	else SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0);
	for (int x = - static_cast<int>(Game::kGraphHalfWidth); 
			x < static_cast<int>(Game::kGraphHalfWidth-1);
			x++)
	{
		for (int y = -static_cast<int>(Game::kGraphHalfHeight); 
				y < static_cast<int>(Game::kGraphHalfHeight -1);
				y++)
		{
			DrawPixel(static_cast<int>(m_pos.x + x), static_cast<int>(m_pos.y + y), m_color);
			
		}
	}
	if (m_isApp) SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	else  SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);

	DrawBox(static_cast<int>(m_pos.x - Game::kGraphHalfWidth),
			static_cast<int>(m_pos.y - Game::kGraphHalfHeight),
			static_cast<int>(m_pos.x + Game::kGraphHalfWidth),
			static_cast<int>(m_pos.y + Game::kGraphHalfHeight),
			0xffffff, false);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

void GoalPoint::Effect()
{
	m_dir++;
	if (m_dir > 30) m_dir = 0;

	if (m_isApp)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - m_dir * 10);
		// ÉtÉåÅ[ÉÄïîï™
		if (m_dir < 30)
		{
			for (int i = 0; i < 4; i++)
			{
				if (i == 0)
					DrawBox(static_cast<int>(m_pos.x - Game::kGraphWidth * 0.5f + i - m_dir),
						static_cast<int>(m_pos.y - Game::kGraphHeight * 0.5f + i - m_dir),
						static_cast<int>(m_pos.x + Game::kGraphWidth * 0.5f - 1 - i + m_dir),
						static_cast<int>(m_pos.y + Game::kGraphHeight * 0.5f - 1 - i + m_dir),
						0xffffff, false);
				else if (i <= 2)
					DrawBox(static_cast<int>(m_pos.x - Game::kGraphWidth * 0.5f) + i - m_dir,
						static_cast<int>(m_pos.y - Game::kGraphHeight * 0.5f) + i - m_dir,
						static_cast<int>(m_pos.x + Game::kGraphWidth * 0.5f) - 1 - i + m_dir,
						static_cast<int>(m_pos.y + Game::kGraphHeight * 0.5f) - 1 - i + m_dir,
						m_color, false);
				else if (i <= 3)
					DrawBox(static_cast<int>(m_pos.x - Game::kGraphWidth * 0.5f) + i - m_dir,
						static_cast<int>(m_pos.y - Game::kGraphHeight * 0.5f) + i - m_dir,
						static_cast<int>(m_pos.x + Game::kGraphWidth * 0.5f) - 1 - i + m_dir,
						static_cast<int>(m_pos.y + Game::kGraphHeight * 0.5f) - 1 - i + m_dir,
						0xffffff, false);
			}
		}
	}
}

void GoalPoint::GoalEffect()
{
	if (m_EfectAngle < 360)
		m_EfectAngle ++;

	for (int i = 0; i < kCurcleNum; i++)
	{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - (m_EfectAngle - 200) * 3);
			DrawCircle(static_cast<int>(m_circlePos[i].x + cos((i * 45 + m_EfectAngle) * 0.0174f * 5) * kCircleMoveDir),
				static_cast<int>(m_circlePos[i].y + sin((i * 45 + m_EfectAngle) * 0.0174f * 5) * kCircleMoveDir),
				kCircleDir, m_color, true);
	}
}
