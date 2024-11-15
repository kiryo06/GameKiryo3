#pragma once
#include "EnemyBase.h"

class EnemyRun : public EnemyBase
{
public:
	EnemyRun();
	virtual ~EnemyRun() {};


	void Update();
	void Draw();

	enum Dir
	{
		kRunRight,
		kRunLeft,
	};

private:

	float m_animationHeight;

	//�G�̉����x
	float m_moveX;
	float m_moveY;

	bool m_isturnFlag;

	//�����Ă������
	Dir m_dir;
	bool m_isAnimRight;
	bool m_isAnimLeft;

	//�A�j���[�V�����̃t���[��
	int m_animationFrame;
	//�����A�j���[�V����
	int m_animFrame;
	int m_animCount;
};

