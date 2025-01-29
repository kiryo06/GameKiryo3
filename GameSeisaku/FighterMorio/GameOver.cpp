#include "GameOver.h"
#include <cmath>
#include "DxLib.h"

namespace
{
	constexpr float kGameOverGravity = 0.3f;	// �Q�[���I�[�o�[�Ɋ|����d�͉����x
	constexpr int kGameOverX = Game::kScreenWidth;				// �Q�[���I�[�o�[�\���ʒuX
	constexpr int kGameOverY = Game::kScreenHeight;				// �Q�[���I�[�o�[�\���ʒuY
	constexpr int ksada = 100;
}
GameOver::GameOver():
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
	//// �������x���X�V
	//fallSpeed += kGameOverGravity;
	//// ��ɐݒ蔻�������
	//CheckIsGround();
	//// �������x���ړ��ʂɉ�����
	//auto fallVelocity = VGet(0, fallSpeed, 0);	// �������x�N�g���ɁBy���W�����ω����Ȃ��̂ōŌ�Ƀx�N�g���ɂ���
	//velocity = VAdd(velocity, fallVelocity);
}

void GameOver::Draw()
{
	DrawExtendGraph(kGameOverX / 2 - 400, kGameOverY / 2 - 50, kGameOverX / 2 - 300, kGameOverY / 2 + 50, m_GameOverGraph_G, TRUE);
	DrawExtendGraph(kGameOverX / 2 - 300, kGameOverY / 2 - 50, kGameOverX / 2 - 200, kGameOverY / 2 + 50, m_GameOverGraph_A, TRUE);
	DrawExtendGraph(kGameOverX / 2 - 200, kGameOverY / 2 - 50, kGameOverX / 2 - 100, kGameOverY / 2 + 50, m_GameOverGraph_M, TRUE);
	DrawExtendGraph(kGameOverX / 2 - 100, kGameOverY / 2 - 50, kGameOverX / 2      , kGameOverY / 2 + 50, m_GameOverGraph_E, TRUE);
	DrawExtendGraph(kGameOverX / 2      , kGameOverY / 2 - 50, kGameOverX / 2 + 100, kGameOverY / 2 + 50, m_GameOverGraph_O, TRUE);
	DrawExtendGraph(kGameOverX / 2 + 100, kGameOverY / 2 - 50, kGameOverX / 2 + 200, kGameOverY / 2 + 50, m_GameOverGraph_V, TRUE);
	DrawExtendGraph(kGameOverX / 2 + 200, kGameOverY / 2 - 50, kGameOverX / 2 + 300, kGameOverY / 2 + 50, m_GameOverGraph_E, TRUE);
	DrawExtendGraph(kGameOverX / 2 + 300, kGameOverY / 2 - 50, kGameOverX / 2 + 400, kGameOverY / 2 + 50, m_GameOverGraph_R, TRUE);

}
