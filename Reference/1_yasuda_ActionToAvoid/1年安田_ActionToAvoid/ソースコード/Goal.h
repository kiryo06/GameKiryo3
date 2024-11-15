#pragma once
#include <memory>

class Player;
class Map;
class TutorialMap;
class Goal
{
public:
	Goal();
	virtual ~Goal();

	void Init();
	void Update();
	void Draw();

	//�}�b�v�̃|�C���^��ݒ肷��
	void SetMap(std::shared_ptr<Map> pMap) { m_pMap = pMap; }
	void SetTutorialMap(std::shared_ptr<TutorialMap> pTutorialMap) { m_pTutorialMap = pTutorialMap; }

	void SetPlayer(std::shared_ptr<Player> pPlayer) { m_pPlayer = pPlayer; }

	//�����o�[�ϐ��ɃA�N�Z�X����
	void SetHandle(int handle) { m_handle = handle; }

	//�A�C�e���̈ʒu�����擾
	float GetX()const { return m_posX; }
	float GetY()const { return m_posY; }

	//�A�C�e���̔��a���擾
	float GetRadius();

	//�v���C���[�Ƃ̓����蔻��t���b�O
	bool GetHitPlayerFlag(std::shared_ptr<Player> pPlayer);

private:
	//�O���t�B�b�N�n���h��
	int m_handle;
	//�A�C�e���̈ʒu
	float m_posX;
	float m_posY;

	std::shared_ptr<Map> m_pMap;
	std::shared_ptr<TutorialMap> m_pTutorialMap;
	std::shared_ptr<Player>m_pPlayer;

	int m_animFrame = 0;

};

