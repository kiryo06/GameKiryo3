#include "GameOver.h"
#include <cmath>
#include "DxLib.h"

namespace
{
	constexpr float kGameOverGravity = 0.3f;	// �Q�[���I�[�o�[�Ɋ|����d�͉����x
	constexpr int kGameOverX = Game::kScreenWidth;				// �Q�[���I�[�o�[�\���ʒuX
	constexpr int kGameOverY = Game::kScreenHeight;				// �Q�[���I�[�o�[�\���ʒuY
	constexpr int ksada = 100;
	/*int spriteSheet = LoadGraph("data/image/Enemy.png");*/
	int GraphSizeX = 3840;
	int frameWidth = 128;  // �t���[���̕�
	int frameHeight = 128; // �t���[���̍���
	int currentFrame = 0; // ���݂̃t���[��
	int frameCount = GraphSizeX / frameWidth;   // �t���[���̑���
	int frameTime = 10;   // �t���[���̕\������
	int frameTimer = 0;   // �t���[���^�C�}�[
}
GameOver::GameOver():
	m_GameOverGraph_A(0),
	m_GameOverGraph_E(0),
	m_GameOverGraph_G(0),
	m_GameOverGraph_M(0),
	m_GameOverGraph_O(0),
	m_GameOverGraph_R(0),
	m_GameOverGraph_V(0),
	m_Graph_MojiA(0),
	m_Graph_MojiB(0),
	m_BrinkCounter(0)
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
	DeleteGraph(m_Graph_MojiA);
	DeleteGraph(m_Graph_MojiB);
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
	m_Graph_MojiA = LoadGraph("data/image/Botann_A.png");
	m_Graph_MojiB = LoadGraph("data/image/Botann_B.png");
}

void GameOver::Update()
{
	// �_�ŗp�̕ϐ��� 1 �𑫂�
	m_BrinkCounter++;

	// �_�ŗp�̕ϐ��� 60 �ɂȂ��Ă����� 0 �ɂ���
	if (m_BrinkCounter == 60)
	{
		m_BrinkCounter = 0;
	}
}

void GameOver::Draw()
{
	int x = (currentFrame % frameCount) * frameWidth;
	int y = frameHeight;
	DrawExtendGraph(kGameOverX / 2 - 400, kGameOverY / 2 - 50, kGameOverX / 2 - 300, kGameOverY / 2 + 50, m_GameOverGraph_G, TRUE);
	DrawExtendGraph(kGameOverX / 2 - 300, kGameOverY / 2 - 50, kGameOverX / 2 - 200, kGameOverY / 2 + 50, m_GameOverGraph_A, TRUE);
	DrawExtendGraph(kGameOverX / 2 - 200, kGameOverY / 2 - 50, kGameOverX / 2 - 100, kGameOverY / 2 + 50, m_GameOverGraph_M, TRUE);
	DrawExtendGraph(kGameOverX / 2 - 100, kGameOverY / 2 - 50, kGameOverX / 2      , kGameOverY / 2 + 50, m_GameOverGraph_E, TRUE);
	DrawExtendGraph(kGameOverX / 2      , kGameOverY / 2 - 50, kGameOverX / 2 + 100, kGameOverY / 2 + 50, m_GameOverGraph_O, TRUE);
	DrawExtendGraph(kGameOverX / 2 + 100, kGameOverY / 2 - 50, kGameOverX / 2 + 200, kGameOverY / 2 + 50, m_GameOverGraph_V, TRUE);
	DrawExtendGraph(kGameOverX / 2 + 200, kGameOverY / 2 - 50, kGameOverX / 2 + 300, kGameOverY / 2 + 50, m_GameOverGraph_E, TRUE);
	DrawExtendGraph(kGameOverX / 2 + 300, kGameOverY / 2 - 50, kGameOverX / 2 + 400, kGameOverY / 2 + 50, m_GameOverGraph_R, TRUE);
#ifdef _DEBUG
	DrawExtendGraph(450, 480, 550, 580, m_Graph_MojiA, true);
	DrawExtendGraph(1050, 530, 1150, 630, m_Graph_MojiB, true);
#endif // _DEBUG
}
