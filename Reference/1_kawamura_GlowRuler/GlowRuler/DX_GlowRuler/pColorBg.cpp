#include "pColorBg.h"
#include "DxLib.h"
#include "Game.h"

pColorBg::pColorBg() :
	m_waveLange(0),
	m_waveMove(1),
	m_rad(0),
	m_dir(0),
	m_angle(0),
	m_alpha(0),
	m_timer(0),
	m_color(0xffffff),
	m_isMove(true)
{
	m_pos = { Game::kScreenWidth * 0.5f, Game::kScreenHeight * 0.5f };
}

pColorBg::~pColorBg()
{
}

void pColorBg::Init()
{
}

void pColorBg::Update(int color)
{
	m_color = color;

	


	if (m_rad < 359) m_rad += 1;
	else m_rad = 0;

	if (m_waveLange >= 100)
	{
		m_waveMove = -2;
	}
	if (m_waveLange <= -100)
	{
		m_waveMove = 2;
	}

	m_waveLange += m_waveMove;
}

void pColorBg::Draw()
{
	for (int i = 0; i < 360 * 2; i++)
	{
		// 3.14 / 180 == 0.0174
		m_dir = Game::kScreenWidth * 0.25f + static_cast<int>(sin(m_rad * 0.0174f) * m_waveLange) * 0.5f;
		int nextDir = Game::kScreenWidth * 0.25f + static_cast<int>(sin((m_rad + 8) * 0.0174f) * m_waveLange) * 0.5f;
		// DrawCircle(static_cast<int>(m_pos.x + cos(i * 0.0174f) * m_dir), static_cast<int>(m_pos.y + sin(i * 0.0174f) * m_dir), 4, m_color, true);
		for (int j = 0; j < 5; j++)
		{
			DrawLineAA(static_cast<int>(m_pos.x + cos(i * 0.0174f) * (m_dir - j)), static_cast<int>(m_pos.y + sin(i * 0.0174f) * (m_dir - j)),
				static_cast<int>(m_pos.x + cos((i + 1) * 0.0174f) * (nextDir - j)), static_cast<int>(m_pos.y + sin((i + 1) * 0.0174f) * (nextDir - j)),
				m_color);
			/*DrawLineAA(static_cast<int>(m_pos.x + sin(i * 0.0174f) * (m_dir - j)), static_cast<int>(m_pos.y + cos(i * 0.0174f) * (m_dir - j)),
				static_cast<int>(m_pos.x + sin((i + 1) * 0.0174f) * (m_dir - j)), static_cast<int>(m_pos.y + cos((i + 1) * 0.0174f) * (m_dir - j)),
				m_color);*/
		}

		if (m_isMove)
		{
			if (m_rad < 360 * 2 * 8 * 2 - 8) m_rad += 8;
			else m_rad = 0;
		}
	}
}
