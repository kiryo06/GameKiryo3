#pragma once
#include "DxLib.h"
class GameOver
{
public:
	GameOver();
	~GameOver();
	void Init();
	void Update();
	void Draw();
	void CheckIsGround();
	bool IsHitGround(const VECTOR& checkPos);
private:
	float w, h;					// �v���C���[�̕��ƍ���
	float fallSpeed;			// �������x
	VECTOR pos;					// ���W ���F���S�@�c�F���S
	VECTOR dir;					// ���W�̈ړ�����
	VECTOR velocity;
	bool isGround;
	int m_GameOverGraph_A;
	int m_GameOverGraph_E;
	int m_GameOverGraph_G;
	int m_GameOverGraph_M;
	int m_GameOverGraph_O;
	int m_GameOverGraph_R;
	int m_GameOverGraph_V;
};

