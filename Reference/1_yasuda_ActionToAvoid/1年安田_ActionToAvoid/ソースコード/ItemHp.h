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


	//�A�j���[�V�����̃t���[��
	int m_animationFrame;
	//�����A�j���[�V����
	int m_animFrame;
	int m_animCount;

	float m_animationHeight;
};

