#pragma once
#include "EnemyBase.h"
class EnemyJumpRun : public EnemyBase
{
public:
	EnemyJumpRun();
	virtual ~EnemyJumpRun() {};


	void Update();
	void Draw();

	enum Dir
	{
		kJump,
	};

private:


	float m_animationHeight;

	//�G�̉����x
	float m_moveX;
	float m_moveY;

	bool m_isturnFlag;

	//�����Ă������
	Dir m_dir;
	bool m_isAnimTurn;
	bool m_isJump;

	//�A�j���[�V�����̃t���[��
	int m_animationFrame;
	//�����A�j���[�V����
	int m_animFrame;
	int m_animCount;
};

