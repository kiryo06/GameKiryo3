#pragma once
#include <memory>
#include "Rect.h"

/// <summary>
/// �G�l�~�[�̊��N���X
/// </summary>
class Map;
class TutorialMap;
class Player;
class EnemyBase
{
public:

	EnemyBase(); //�R���X�g���N�^
	virtual ~EnemyBase() {};//�f�X�g���N�^

	//�����o�[�ϐ��ɃA�N�Z�X����
	void SetHandle(int handle) { m_handle = handle; }

	//�}�b�v�̃|�C���^��ݒ肷��
	void SetMap(std::shared_ptr<Map> pMap) { m_pMap = pMap; }
	//void SetTutorialMap(std::shared_ptr<TutorialMap> pTutorialMap) { m_pTutorialMap = pTutorialMap; }
	void SetPlayer(std::shared_ptr<Player> pPlayer) { m_pPlayer = pPlayer; }

	//
	void Start(float x, float y) { m_posX = x; m_posY = y; };
	virtual void Update() = 0;
	virtual void Draw() = 0;

	//�G�̈ʒu�����擾
	float GetX()const { return m_posX; }
	float GetY()const { return m_posY; }

	float GetRadius();

	float GetLeft();
	float GetRight();
	float GetTop();
	float GetBottom();

	bool GetHitPlayerFlag(std::shared_ptr<Player> pPlayer);

	//���݂̓G�̋�`���
	Rect getRect();

	bool IsCol(Rect rect, Rect& enemyRect);

protected:
	//Map�Ō��肵���X�N���[���ʂ��擾���邽�߂�Map�N���X�̏�񂪕K�v
	std::shared_ptr<Map> m_pMap;
	std::shared_ptr<TutorialMap> m_pTutorialMap;
	std::shared_ptr<Player>m_pPlayer;

	//�O���t�B�b�N�n���h��
	int m_handle;

	Rect m_colRect;

	float m_posX;
	float m_posY;
};

