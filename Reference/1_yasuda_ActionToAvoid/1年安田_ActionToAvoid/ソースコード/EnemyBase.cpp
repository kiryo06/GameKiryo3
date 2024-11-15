#include "EnemyBase.h"
#include "Map.h"
#include "Player.h"
#include "DxLib.h"
#include <cmath>

namespace
{
	//敵のサイズ
	constexpr int kWidth = 20;
	constexpr int kHeight = 20;

	//敵の描画サイズ
	constexpr int kDrawWidth = 32;
	constexpr int kDrawHeight = 32;

	//円の当たり判定の半径
	constexpr int kRadius = 10;

}

EnemyBase::EnemyBase():
	m_handle(-1),
	m_posX(0.0f),
	m_posY(0.0f)
{

}

float EnemyBase::GetRadius()
{
	return kRadius;
}

float EnemyBase::GetLeft()
{
	return m_posX - kWidth * 0.5;
}

float EnemyBase::GetRight()
{
	return m_posX + kWidth * 0.5;
}

float EnemyBase::GetTop()
{
	return m_posY - kHeight;
}

float EnemyBase::GetBottom()
{
	return m_posY;
}

bool EnemyBase::GetHitPlayerFlag(std::shared_ptr<Player> pPlayer)
{
	float Rlength = kRadius + pPlayer->GetRadius();// プレイヤーと敵の半径の合計
	float delX = pPlayer->GetX() - m_posX; //X成分の距離
	float delY = pPlayer->GetY() - m_posY; //Y成分の距離

	float del = sqrt((delX * delX) + (delY * delY));

	if (del <= Rlength)
	{


		return true;
	}

	return false;
}



Rect EnemyBase::getRect()
{
	Rect rect;
	rect.top = GetTop();
	rect.bottom = GetBottom();
	rect.right = GetRight();
	rect.left = GetLeft();
	return rect;
}

bool EnemyBase::IsCol(Rect rect, Rect& enemyRect)
{
	//敵の当たり判定
	float enemyLeft = kWidth;
	float enemyRight = enemyLeft + kWidth;
	float enemyTop = kHeight;
	float enemyBottom = enemyTop + kHeight;

	//絶対に当たらないパターンをはじく
	if (enemyLeft > rect.right) return false;
	if (enemyRight > rect.bottom) return false;
	if (enemyTop < rect.left) return false;
	if (enemyBottom < rect.top) return false;

	//ぶつかったマップチップの矩形を設定する
	enemyRect.left = enemyLeft;
	enemyRect.right = enemyRight;
	enemyRect.top = enemyTop;
	enemyRect.bottom = enemyBottom;

	return true;

}