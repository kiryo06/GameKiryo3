#include "GameClear.h"
#include <cmath>
#include "DxLib.h"

namespace
{
	/*int spriteSheet = LoadGraph("data/image/Enemy.png");*/
	int GraphSizeX = 3840;
	int frameWidth = 128;  // �t���[���̕�
	int frameHeight = 128; // �t���[���̍���
	int currentFrame = 0; // ���݂̃t���[��
	int frameCount = GraphSizeX/ frameWidth;   // �t���[���̑���
	int frameTime = 10;   // �t���[���̕\������
	int frameTimer = 0;   // �t���[���^�C�}�[
}
GameClear::GameClear():
	m_Graph_GAMECLEAR(0),
	m_Graph_(0),
	m_BrinkCounter(0)
{
}

GameClear::~GameClear()
{
	DeleteGraph(m_Graph_GAMECLEAR);
	DeleteGraph(m_Graph_);
}

void GameClear::Init()
{
	m_Graph_GAMECLEAR = LoadGraph("data/image/GameClear.png");
	m_Graph_ = LoadGraph("data/image/BackGround.png");
	//m_Graph_ = LoadGraph("data/image/GameClear.png");
}

void GameClear::Update()
{
	// �t���[���^�C�}�[�̍X�V
	frameTimer++;
	if (frameTimer >= frameTime) {
		frameTimer = 0;
		currentFrame = (currentFrame + 1) % frameCount;
	}



	// �_�ŗp�̕ϐ��� 1 �𑫂�
	m_BrinkCounter++;

	// �_�ŗp�̕ϐ��� 60 �ɂȂ��Ă����� 0 �ɂ���
	if (m_BrinkCounter == 60)
	{
		m_BrinkCounter = 0;
	}
}

void GameClear::Draw()
{
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x999999,TRUE);
	int x = (currentFrame % frameCount) * frameWidth;
	int y = frameHeight;
	DrawRectGraph(64,128, x, y, frameWidth, frameHeight, m_Graph_, FALSE);
	//DrawExtendGraph(0, 0,Game::kScreenWidth,Game::kScreenHeight, m_Graph_GAMECLEAR, true);
	DrawRectExtendGraph(0,0,64,64, x, y, frameWidth, frameHeight, m_Graph_, FALSE);
	//DrawGraph(0,0, m_Graph_, true);
#ifdef _DEBUG
	// �_�ŗp�̕ϐ��̒l�� 30 �����̂Ƃ����� --- PRESS SPACE KEY --- ��`�悷��
	if (m_BrinkCounter < 30)
	{
		SetFontSize(20);
		DrawString(185, 450, "--- PRESS SPACE KEY ---", GetColor(255, 255, 255));
	}
#endif // _DEBUG
}
