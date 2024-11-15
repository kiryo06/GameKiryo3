#include "DxLib.h"
#include "InColorFloor.h"
#include "Handle.h"


InColorFloor::InColorFloor() :
	m_pos{ 0,0 },
	m_color(0xffffff)
{
	for (int i = 0; i < kEffectNum; i++)
	{
		m_animaY[i] = - kEffectSpace * i;
	}
}

InColorFloor::~InColorFloor()
{
}

void InColorFloor::Init(int x, int y, int color)
{
	m_pos = { static_cast<float>(x) * Game::kGraphWidth + Game::kMapStartPosX + Game::kGraphHalfWidth,
				static_cast<float>(y) * Game::kGraphHeight + Game::kMapStartPosY + Game::kGraphHalfHeight };
	m_colRect.SetCenter(m_pos.x,
						m_pos.y,
						Game::kGraphWidth,
						Game::kGraphHeight);
	m_color = color;

}

void InColorFloor::Update()
{
	for (int i = 0; i < kEffectNum; i++)
	{
		m_animaY[i]--;

		if (m_animaY[i] <= kEffectMaxY) m_animaY[i] = 0;
	}
}

void InColorFloor::Draw(const Handle& handle)
{
	// 色部分
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawCircle(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), static_cast<int>(Game::kGraphHalfWidth - 2), m_color, true);
	// 色変えの機械部分
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	DrawExtendGraph(static_cast<int>(m_pos.x - Game::kGraphHalfWidth), static_cast<int>(m_pos.y - Game::kGraphHalfHeight),
		static_cast<int>(m_pos.x + Game::kGraphHalfWidth), static_cast<int>(m_pos.y + Game::kGraphHalfHeight),
		handle.h_data.hi_inColor, true);
}

void InColorFloor::colorEffect()
{
	// 楕円エフェクト
	for (int i = 0; i < 4; i++)
	{
		// 一定以上上にあげたらAlphaを下げていく
		if(m_animaY[i] < kDisAppY)
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 + ((m_animaY[i]+ kDisAppY) * 25));
		// それまではAlphaは255で固定
		else
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		DrawOval(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y + 5 + m_animaY[i]), kCircleRX, kCircleRY, m_color, false);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
}
