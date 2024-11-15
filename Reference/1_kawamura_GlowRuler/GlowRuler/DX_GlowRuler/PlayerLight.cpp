#include "DxLib.h"
#include "PlayerLight.h"



PlayerLight::PlayerLight() :
	m_pos(0.0f, 0.0f),
	m_lightRadius(20.0f),
	m_radiusMove(0.08f),
	m_isFloorHit(false),
	m_clearColor(0xff0000),
	m_R(255),
	m_G(0),
	m_B(0),
	m_alpha(255),
	m_isInColor(false),
	m_EfectAngle(0),
	m_isInApp(false),
	m_efectRad(300)
{
	for (int x = 0; x < kLightMaxRadius * 2; x++)
	{
		for (int y = 0; y < kLightMaxRadius * 2; y++)
		{
			m_color[x][y] = 0xf0f0f0;
			m_isClearColor[x][y] = false;
		}
	}
	m_posLightDir[0] = 0;
	m_posLightDir[1] = 30;
	m_posLightDir[2] = 60;
}

PlayerLight::~PlayerLight()
{
}

void PlayerLight::Init(Vec2 player)
{
	m_pos = player;
	m_colRect.SetCenter(m_pos.x,
						m_pos.y,
						Game::kGraphWidth,
						Game::kGraphHeight);

	for (int i = 0; i < 8; i++)
	{
		m_circlePos[i] = { m_pos.x + cos((45 * i) * 0.0174f * 5) * 100,
							m_pos.y + sin((45 * i) * 0.0174f * 5) * 100 };
	}
}

void PlayerLight::Update(Vec2 player)
{
	m_pos = player;
	// 当たり判定の更新
	m_colRect.SetCenter(m_pos.x, 
						m_pos.y, 
						Game::kGraphWidth, 
						Game::kGraphHeight);

	if (m_lightRadius > kLightMaxRadius || m_lightRadius < kLightMinRadius) m_radiusMove *= -1;
	m_lightRadius += m_radiusMove;

	// クリア時のカラー
	if (m_B == 0)
	{
		if (!(m_R == 0))
		{
			m_R -= kLightColorSpeed;
			m_G += kLightColorSpeed;
		}
	}
	if (m_R == 0)
	{
		if (!(m_G == 0))
		{
			m_G -= kLightColorSpeed;
			m_B += kLightColorSpeed;
		}
	}
	if (m_G == 0)
	{
		if (!(m_B == 0))
		{
			m_B -= kLightColorSpeed;
			m_R += kLightColorSpeed;
		}
	}
	m_clearColor = (16 * 16 * 16 * 16 * m_R) + (16 * 16 * m_G) + (m_B);
	for (int x = 0; x < kLightMaxRadius * 2; x++)
	{
		for (int y = 0; y < kLightMaxRadius * 2; y++)
		{
			if(m_isClearColor[x][y]) m_color[x][y] = m_clearColor;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		m_posLightDir[i] += 2;

		if (m_posLightDir[i] > 300) m_posLightDir[i] = 0;
	}

	for (int i = 0; i < 8; i++)
	{
		m_circlePos[i] = m_pos;
	}

	// エフェクト
	if (m_EfectAngle == 360)
	{
		m_isInApp = true;
	}

	if (m_isInApp)
	{
		if (m_efectRad > 0)
			m_efectRad -= 15;
		else
		{
			m_isInApp = false;
		}
	}
	if(!m_isInApp)
	{
		m_efectRad = 300;
		m_EfectAngle = 30;
	}
}

void PlayerLight::Draw()
{
	
	// プレイヤーからドット位置までの距離計測
	// -> Lengthが半径以上ならばDraw
	for (int x = -kLightMaxRadius; x < kLightMaxRadius; x++)
	{
		for (int y = -kLightMaxRadius; y < kLightMaxRadius; y++)
		{
			if (!m_isClearColor[x + kLightMaxRadius][y + kLightMaxRadius])
			{
				Vec2 DrawPoint = { m_pos.x + x + 1, m_pos.y + y + 1 };
				Vec2 PosVec = DrawPoint - m_pos;
				float langth = PosVec.Length() + 1;
				if (langth < m_lightRadius)
				{
					// 円範囲の外側に行くほどアルファ値を低くする
					m_alpha = 255 - (255 - static_cast<int>(m_lightRadius - langth) * kLightAlphaPow);
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alpha);
					DrawPixel(static_cast<int>(DrawPoint.x), static_cast<int>(DrawPoint.y),
						m_color[x + kLightMaxRadius]
						[y + kLightMaxRadius]);

				}
			}
			
		}
	}

	if (m_isInApp)
	{
		if (m_EfectAngle < 30)
			m_EfectAngle++;
		else
			m_EfectAngle = 0;

		for (int i = 0; i < 8; i++)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - m_EfectAngle * 8);
			DrawCircle(static_cast<int>(m_circlePos[i].x + cos((i * 45 + m_EfectAngle) * 0.0174f * 5) * m_efectRad),
				static_cast<int>(m_circlePos[i].y + sin((i * 45 + m_EfectAngle) * 0.0174f * 5) * m_efectRad),
				40, m_color[kLightMaxRadius][kLightMaxRadius], true);
		}
	}

	// 描写後はアルファ値を戻しておく
	m_alpha = 255;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alpha);
}

void PlayerLight::ColorFloorHit(Rect& inColor, int color)
{
	for (int x = 0; x < kLightMaxRadius * 2; x++)
	{
		for (int y = 0; y < kLightMaxRadius * 2; y++)
		{
			Vec2 point = { m_pos.x + x - kLightMaxRadius + 1, m_pos.y + y - kLightMaxRadius + 1 };
			if (inColor.IsPointInRect(point) == 1 && m_color[x][y] != color)
			{
				m_color[x][y] = 0x000000;
			}
			else if (inColor.IsPointInRect(point) == 2) m_color[x][y] = color;
		}
	}
}

void PlayerLight::ClearHit(Rect& Goal)
{
	for (int x = 0; x < kLightMaxRadius * 2; x++)
	{
		for (int y = 0; y < kLightMaxRadius * 2; y++)
		{
			Vec2 point = { m_pos.x + x - kLightMaxRadius + 1, m_pos.y + y - kLightMaxRadius + 1 };
			if (Goal.IsPointInRect(point))
			{
				m_isClearColor[x][y] = true;
			}
		}
	}
}

void PlayerLight::ColorEffect()
{
	// プレイヤー位置を知らせるレーダー的な円
	for (int i = 0; i < 3; i++)
	{
		if (m_posLightDir[i] < 100)
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		else
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - static_cast<int>((m_posLightDir[i] - 100) * 3));

		if (m_posLightDir[i] < 200)
			for (int j = 0; j < 3; j++)
			{
				DrawCircle(m_pos.x, m_pos.y, m_posLightDir[i] - j, this->GetColor(), false);
			}
	}
	
	// 描写後はアルファ値を戻しておく
	m_alpha = 255;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alpha);
}

void PlayerLight::InColorEffect()
{
	m_isInApp = true;
}

void PlayerLight::ResetColor()
{
	for (int x = 0; x < kLightMaxRadius * 2; x++)
	{
		for (int y = 0; y < kLightMaxRadius * 2; y++)
		{
			m_color[x][y] = 0xf0f0f0;
			m_isClearColor[x][y] = false;
		}
	}
}
