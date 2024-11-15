#include "Goal.h"
#include "DxLib.h"
#include "Player.h"
#include "Map.h"
#include <cmath>

namespace
{
	//���a
	constexpr int kRadius = 32;

	constexpr int kDrawWidth = 64;
	constexpr int kDrawHeight = 64;

	constexpr int kWidth = 64;
	constexpr int kHeight = 64;

	//�A�j���[�V����
	constexpr int kUseFrame[] = { 0, 1, 2, 3, 4, 5, 6, 7, };
	//�A�j���[�V�����P�R�}�̃t���[����
	constexpr int kAnimFrameNum = 6;
	//�A�j���[�V�����̂P�T�C�N���̃t���[����
	constexpr int kAnimFrameCycle = _countof(kUseFrame) * kAnimFrameNum;
}

Goal::Goal():
	m_posX(3760.0f),
	m_posY(610.0f),
	m_handle(0)
{
}

Goal::~Goal()
{
}

void Goal::Init()
{
}

void Goal::Update()
{
	m_animFrame++;
	if (m_animFrame >= kAnimFrameCycle) m_animFrame = 0;
}

void Goal::Draw()
{
	//�������W��������W�ɕϊ�
	int x = static_cast<int>(m_posX - kWidth * 0.5);
	int y = static_cast<int>(m_posY - kHeight);

	//�X�N���[���ʂ𔽉f
	x -= m_pMap->GetScrollX();
	y -= m_pMap->GetScrollY();

	int animFrame = m_animFrame / kAnimFrameNum;

	int srcX = kUseFrame[animFrame] * kDrawWidth;
	int srcY = kDrawHeight * 0;

	DrawRectRotaGraph(x + 32 , y + 32 , srcX, srcY, kDrawWidth, kDrawHeight, 1.0, 0.0, m_handle, true, false);

}

float Goal::GetRadius()
{
    return kRadius;
}

bool Goal::GetHitPlayerFlag(std::shared_ptr<Player> pPlayer)
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
