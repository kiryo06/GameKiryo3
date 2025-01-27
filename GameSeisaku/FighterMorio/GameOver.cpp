#include "GameOver.h"
#include <cmath>
#include "DxLib.h"

namespace
{
	constexpr float kGameOverGravity = 0.3f;	// �Q�[���I�[�o�[�Ɋ|����d�͉����x
	constexpr int kGameOverX = 200;				// �Q�[���I�[�o�[�\���ʒuX
	constexpr int kGameOverY = 600;				// �Q�[���I�[�o�[�\���ʒuY
}
GameOver::GameOver():
	w(120),
	h(120),
	fallSpeed(0.0f),
	pos(VGet(20.0f, 992, 0)),
	velocity(VGet(0, 0, 0)),
	m_GameOverGraph_A(0),
	m_GameOverGraph_E(0),
	m_GameOverGraph_G(0),
	m_GameOverGraph_M(0),
	m_GameOverGraph_O(0),
	m_GameOverGraph_R(0),
	m_GameOverGraph_V(0)
{
}

GameOver::~GameOver()
{
	DeleteGraph(m_GameOverGraph_A);
	DeleteGraph(m_GameOverGraph_E);
	DeleteGraph(m_GameOverGraph_G);
	DeleteGraph(m_GameOverGraph_M);
	DeleteGraph(m_GameOverGraph_O);
	DeleteGraph(m_GameOverGraph_R);
	DeleteGraph(m_GameOverGraph_V);
}

void GameOver::Init()
{
	m_GameOverGraph_A = LoadGraph("data/image/moji_A.png");
	m_GameOverGraph_E = LoadGraph("data/image/moji_E.png");
	m_GameOverGraph_G = LoadGraph("data/image/moji_G.png");
	m_GameOverGraph_M = LoadGraph("data/image/moji_M.png");
	m_GameOverGraph_O = LoadGraph("data/image/moji_O.png");
	m_GameOverGraph_R = LoadGraph("data/image/moji_R.png");
	m_GameOverGraph_V = LoadGraph("data/image/moji_V.png");
}

void GameOver::Update()
{
	// �������x���X�V
	fallSpeed += kGameOverGravity;
	// ��ɐݒ蔻�������
	CheckIsGround();
	// �������x���ړ��ʂɉ�����
	auto fallVelocity = VGet(0, fallSpeed, 0);	// �������x�N�g���ɁBy���W�����ω����Ȃ��̂ōŌ�Ƀx�N�g���ɂ���
	velocity = VAdd(velocity, fallVelocity);
}

void GameOver::Draw()
{
	DrawGraph(kGameOverX, kGameOverY, m_GameOverGraph_G, TRUE);
	DrawGraph(kGameOverX + 100, kGameOverY, m_GameOverGraph_A, TRUE);
	DrawGraph(kGameOverX + 200, kGameOverY, m_GameOverGraph_M, TRUE);
	DrawGraph(kGameOverX + 300, kGameOverY, m_GameOverGraph_E, TRUE);
	DrawGraph(kGameOverX + 400, kGameOverY, m_GameOverGraph_O, TRUE);
	DrawGraph(kGameOverX + 500, kGameOverY, m_GameOverGraph_V, TRUE);
	DrawGraph(kGameOverX + 600, kGameOverY, m_GameOverGraph_E, TRUE);
	DrawGraph(kGameOverX + 700, kGameOverY, m_GameOverGraph_R, TRUE);
}

void GameOver::CheckIsGround()
{
	// 1�h�b�g���ɂ��炵�ē�����Βn�ʂɑ����Ԃ����Ă��� �i�����_�����j
	VECTOR checkPos = VGet(pos.x, kGameOverY, pos.z);
	// �S�}�b�v�`�b�v���J��Ԃ�
	bool isHit = false;
	isHit = IsHitGround(checkPos);
}

bool GameOver::IsHitGround(const VECTOR& checkPos)
{
	return false;
}
