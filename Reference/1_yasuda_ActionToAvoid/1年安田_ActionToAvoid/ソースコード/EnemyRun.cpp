#include "EnemyRun.h"
#include "DxLib.h"
#include "Map.h"

namespace
{
	//�G�̃T�C�Y
	constexpr int kWidth = 30;
	constexpr int kHeight = 30;

	//�G�̕`��T�C�Y
	constexpr int kDrawWidth = 32;
	constexpr int kDrawHeight = 32;

	//���x
	constexpr float kSpeed = 2.5f;
	//�d��
	constexpr float kGravity = 0.5f;

	constexpr float kSinSpeed = 0.1f;
	constexpr float kAnimationSize = 3.0f;

	/* �A�j���[�V���� */

	//�L�����N�^�[�̃A�j���[�V����
	constexpr int kUseFrame[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
	//�A�j���[�V�����P�R�}�̃t���[����
	constexpr int kAnimFrameNum = 4;
	//�A�j���[�V�����̂P�T�C�N���̃t���[����
	constexpr int kAnimFrameCycle = _countof(kUseFrame) * kAnimFrameNum;
}

EnemyRun::EnemyRun():
	m_moveX(0.0f),
	m_moveY(0.0f),
	m_animationHeight(0.0f),
	m_isturnFlag(false),
	m_isAnimLeft(false),
	m_isAnimRight(false),
	m_animationFrame(0),
	m_animFrame(0),
	m_animCount(0),
	m_dir(kRunRight)
{
}

void EnemyRun::Update()
{
	bool isMove = false;

	//���t���[���������ɉ�������(�d�͂̉e�����󂯂�)
	m_moveY += kGravity;

	if (m_isturnFlag == false)
	{
		m_moveX = kSpeed; //�E����
		m_isAnimRight = true;
		isMove = true;
		m_dir = kRunRight;
	}
	if (m_isturnFlag == true)
	{
		m_moveX = -kSpeed; //������
		m_isAnimLeft = true;
		isMove = true;
		m_dir = kRunLeft;
	}

	if (isMove)
	{
		//�A�j���[�V����
		m_animFrame++;
		if (m_animFrame >= kAnimFrameCycle) m_animFrame = 0;
	}

	//��ʒ[����o�Ă����Ȃ�
	if (m_posX < 15) m_isturnFlag = false;
	if (m_posX > 3840 - 15) m_isturnFlag = true;

	m_posX += m_moveX;
	Rect chipRect;	//���������}�b�v�`�b�v�̋�`
	//�����瓖�����������`�F�b�N����
	if (m_pMap->IsCol(getRect(), chipRect))
	{
		if (m_moveX > 0.0f)//�G���E�����Ɉړ����Ă���
		{
			m_posX = chipRect.left - kWidth * 0.5 - 1; //�}�b�v�`�b�v�̍����ɂԂ���Ȃ��ʒu�ɕ␳
			m_isturnFlag = true;
		}
		else if (m_moveX < 0.0f)
		{
			m_posX = chipRect.right + kWidth * 0.5 + 1; //�@��ɓ���
			m_isturnFlag = false;
		}
	}

	m_posY += m_moveY;
	//�c���瓖�����������`�F�b�N����
	if (m_pMap->IsCol(getRect(), chipRect))
	{
		if (m_moveY > 0.0f)//�G���㉺�����Ɉړ����Ă���
		{
			//�n�ʂɗ����Ă���ꍇ�͉������Ȃ�
			m_posY = chipRect.top - 1;
			m_moveY = 0.0f;
		}
		else if (m_moveY < 0.0f)
		{
			m_posY = chipRect.bottom + kHeight + 1; //�@��ɓ���
		}
	}
}

void EnemyRun::Draw()
{
	//�������W��������W�ɕϊ�
	int x = static_cast<int>(m_posX - kWidth * 0.5);
	int y = static_cast<int>(m_posY - kHeight);

	//�X�N���[���ʂ𔽉f
	x -= m_pMap->GetScrollX();
	y -= m_pMap->GetScrollY();

	int animFrame = m_animFrame / kAnimFrameNum;

	int srcX = kUseFrame[animFrame] * kDrawWidth;
	int srcY = kDrawHeight * m_dir;

	//x = 210;
	//y = 650;
	DrawRectRotaGraph(x + 16, y + 16, srcX, srcY, kDrawWidth, kDrawHeight, 1.0, 0.0, m_handle, true, false);
	//DrawFormatString(0, 32, 0x00ff00, "%d", x + 16);
	//DrawFormatString(0, 48, 0x00ff00, "%d", y + 16);
}
