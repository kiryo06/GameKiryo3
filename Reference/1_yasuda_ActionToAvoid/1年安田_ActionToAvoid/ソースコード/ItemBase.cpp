#include "ItemBase.h"
#include "Player.h"
#include "Map.h"
#include "DxLib.h"
#include <cmath>

namespace
{
	//���a
	constexpr int kRadius = 16;

	constexpr int kWidth = 16;
	constexpr int kHeight = 16;

	constexpr int kDrawWidth = 16;
	constexpr int kDrawHeight = 16;

	constexpr float kSinSpeed = 0.1f;
	constexpr float kAnimationSize = 3.0f;

}

ItemBase::ItemBase():
	m_handle(-1),
	m_posX(0.0f),
	m_posY(0.0f)
{
}

void ItemBase::ItemLost()
{

	m_isExist = false;
}

float ItemBase::GetRadius()
{
	return kRadius;
}

bool ItemBase::GetHitPlayerFlag(std::shared_ptr<Player> pPlayer)
{
	float Rlength = kRadius + pPlayer->GetRadius();// �v���C���[�ƓG�̔��a�̍��v
	float delX = pPlayer->GetX() - m_posX; //X�����̋���
	float delY = pPlayer->GetY() - m_posY; //Y�����̋���

	float del = sqrt((delX * delX) + (delY * delY));

	if (del <= Rlength)
	{


		return true;
	}

	return false;
}

