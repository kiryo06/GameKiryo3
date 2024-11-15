#include "ItemHp.h"
#include "Player.h"
#include "Map.h"
#include "DxLib.h"

#include <cmath>

namespace
{
	//半径
	constexpr int kRadius = 16;

	constexpr int kWidth = 16;
	constexpr int kHeight = 16;

	constexpr int kDrawWidth = 16;
	constexpr int kDrawHeight = 16;

	constexpr float kSinSpeed = 0.02f;
	constexpr float kAnimationSize = 4.0f;

}

ItemHp::ItemHp():
	m_animFrame(0),
	m_animCount(0),
	m_animationFrame(0),
	m_animationHeight(0.0f)
{
	m_isExist = true;
}

void ItemHp::Update()
{
	if (!m_isExist)
	{
		return;
	}
	static float SinCount = 0;
	SinCount += kSinSpeed;
	m_animationHeight = sinf(SinCount) * kAnimationSize;
}

void ItemHp::Draw()
{
	if (!m_isExist)
	{
		return;
	}

	//足元座標を左上座標に変換
	int x = static_cast<int>(m_posX - kWidth * 0.5);
	int y = static_cast<int>(m_posY - kHeight);

	//スクロール量を反映
	x -= m_pMap->GetScrollX();
	y -= m_pMap->GetScrollY();

	DrawExtendGraph(x, y + m_animationHeight, x + kDrawWidth, y + kDrawHeight, m_handle, true);


	//if (!m_isExist)
	//{
	//	DrawExtendGraph(x, y + m_animationHeight, x + kDrawWidth, y + kDrawHeight, m_handle, true);		
	//}
}
