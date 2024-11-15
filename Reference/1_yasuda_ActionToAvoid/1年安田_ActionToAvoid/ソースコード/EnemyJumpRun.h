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

	//敵の加速度
	float m_moveX;
	float m_moveY;

	bool m_isturnFlag;

	//向いている方向
	Dir m_dir;
	bool m_isAnimTurn;
	bool m_isJump;

	//アニメーションのフレーム
	int m_animationFrame;
	//歩きアニメーション
	int m_animFrame;
	int m_animCount;
};

