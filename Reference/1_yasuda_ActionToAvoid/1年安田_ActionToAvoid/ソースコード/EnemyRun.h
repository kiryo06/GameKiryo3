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

	//敵の加速度
	float m_moveX;
	float m_moveY;

	bool m_isturnFlag;

	//向いている方向
	Dir m_dir;
	bool m_isAnimRight;
	bool m_isAnimLeft;

	//アニメーションのフレーム
	int m_animationFrame;
	//歩きアニメーション
	int m_animFrame;
	int m_animCount;
};

