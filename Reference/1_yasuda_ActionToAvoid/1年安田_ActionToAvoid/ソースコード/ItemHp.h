#pragma once
#include "ItemBase.h"
#include "Rect.h"

class ItemHp : public ItemBase
{
public:
	ItemHp();
	virtual ~ItemHp() {};

	void Update();
	void Draw();

private:
	std::shared_ptr<Player> pPlayer;


	//アニメーションのフレーム
	int m_animationFrame;
	//歩きアニメーション
	int m_animFrame;
	int m_animCount;

	float m_animationHeight;
};

