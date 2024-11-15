#pragma once
#include "ItemBase.h"
class ItemBigHp : public ItemBase
{
public:
	ItemBigHp();
	virtual ~ItemBigHp() {};

	void Update();
	void Draw();

private:
	std::shared_ptr<Player> pPlayer;

	float m_animationHeight;

	//アイテムの加速度
	float m_moveX;
	float m_moveY;

	//アニメーションのフレーム
	int m_animationFrame;
	//歩きアニメーション
	int m_animFrame;
	int m_animCount;
};

