#pragma once
#include <memory>
#include "Rect.h"

class Player;
class Map;
class TutorialMap;
class ItemBase
{
public:
	ItemBase();
	virtual ~ItemBase() {};

	//�����o�[�ϐ��ɃA�N�Z�X����
	void SetHandle(int handle) { m_handle = handle; }

	//�}�b�v�̃|�C���^��ݒ肷��
	void SetMap(std::shared_ptr<Map> pMap) { m_pMap = pMap; }
	void SetTutorialMap(std::shared_ptr<TutorialMap> pTutorialMap) { m_pTutorialMap = pTutorialMap; }

	void SetPlayer(std::shared_ptr<Player> pPlayer) { m_pPlayer = pPlayer; }

	void Start(int x, int y) { m_posX = x; m_posY = y; }
	virtual void Update() = 0;
	virtual void Draw() = 0;

	//�A�C�e���������鏈��
	void ItemLost();

	//�A�C�e���̈ʒu�����擾
	float GetX()const { return m_posX; }
	float GetY()const { return m_posY; }

	//�A�C�e���̔��a���擾
	float GetRadius();

	//�v���C���[�Ƃ̓����蔻��t���b�O
	bool GetHitPlayerFlag(std::shared_ptr<Player> pPlayer);

	bool isExist()const { return m_isExist; }

protected:
	//�O���t�B�b�N�n���h��
	int m_handle;
	//�A�C�e���̈ʒu
	float m_posX;
	float m_posY;

	bool m_isExist = false;


	std::shared_ptr<Map> m_pMap;
	std::shared_ptr<TutorialMap> m_pTutorialMap;
	std::shared_ptr<Player>m_pPlayer;

};

