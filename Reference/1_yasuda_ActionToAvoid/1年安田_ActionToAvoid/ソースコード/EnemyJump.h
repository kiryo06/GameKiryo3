#pragma once
#include "EnemyBase.h"

class Player;
class EnemyJump : public EnemyBase
{
public:
	EnemyJump();
	virtual ~EnemyJump() {};


	void Update();
	void Draw();

	enum Dir
	{
		kNutralRight,
		kNutralLeft,
	};

private:

	std::shared_ptr<Player> pPlayer;

	float m_animationHeight;

	//�G�̉����x
	float m_moveX;
	float m_moveY;

	int m_jumpCount = 0;

	bool m_isturnFlag;

	//�����Ă������
	Dir m_dir;
	bool m_isAnimRight;
	bool m_isAnimLeft;

	bool m_isJump;

	//�A�j���[�V�����̃t���[��
	int m_animationFrame;
	//�����A�j���[�V����
	int m_animFrame;
	int m_animCount;
};

