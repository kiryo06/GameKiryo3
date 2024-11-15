#pragma once
#include "Rect.h"

class Rect;

namespace 
{
	// �F�ω����x
	constexpr int kColorSpeed = 15;

	// �G�t�F�N�g
	constexpr int kCircleDir = 50;
	constexpr int kCircleMoveDir = 100;
	constexpr int kCurcleNum = 8;
}

class GoalPoint
{
public:
	GoalPoint();
	~GoalPoint();
	void Init(int& x, int& y);
	void Update(bool& isClear);
	void Draw();

	void Effect();
	void GoalEffect();

	Rect GetRect()const { return m_colRect; }
	int GetColor()const { return m_color; }

	Vec2 GetPos()const { return m_pos; }

private:
	// �S�[���_���t���O
	bool m_isApp;
	// �����蔻��
	Rect m_colRect;
	// ���W
	Vec2 m_pos;
	// �S�[���̐F
	int m_color;
	int m_R;
	int m_G;
	int m_B;
	// ���X�ɓ_���̃A���t�@
	int m_alpha;
	

	// �S�[���G�t�F�N�g
	int m_dir;
	// �G�t�F�N�g�~�̈ʒu
	Vec2 m_circlePos[kCurcleNum];
	// �G�t�F�N�g�~�̃S�[�����S����̋���
	int m_EfectAngle;

	
};

