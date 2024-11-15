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

	//�A�C�e���̉����x
	float m_moveX;
	float m_moveY;

	//�A�j���[�V�����̃t���[��
	int m_animationFrame;
	//�����A�j���[�V����
	int m_animFrame;
	int m_animCount;
};

