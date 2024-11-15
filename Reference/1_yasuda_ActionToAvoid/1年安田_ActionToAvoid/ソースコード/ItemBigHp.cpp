#include "ItemBigHp.h"
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

ItemBigHp::ItemBigHp()
{
	m_isExist = true;
}

void ItemBigHp::Update()
{
	if (!m_isExist)
	{
		return;
	}
	static float SinCount = 0;
	SinCount += kSinSpeed;
	m_animationHeight = sinf(SinCount) * kAnimationSize;
}

void ItemBigHp::Draw()
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

	DrawExtendGraph(x, y + m_animationHeight, x + kDrawWidth + 16, y + kDrawHeight + 16, m_handle, true);
}
