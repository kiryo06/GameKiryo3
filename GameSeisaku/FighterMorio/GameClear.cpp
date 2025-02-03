#include "GameClear.h"
#include <cmath>
#include "DxLib.h"

GameClear::GameClear():
	m_Graph_GAMECLEAR(0),
	m_BrinkCounter(0)
{
}

GameClear::~GameClear()
{
	DeleteGraph(m_Graph_GAMECLEAR);
}

void GameClear::Init()
{
	m_Graph_GAMECLEAR = LoadGraph("data/image/GameClear.png");
}

void GameClear::Update()
{

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
	DrawExtendGraph(0, 0,Game::kScreenWidth,Game::kScreenHeight, m_Graph_GAMECLEAR, true);
	// �_�ŗp�̕ϐ��̒l�� 30 �����̂Ƃ����� --- PRESS SPACE KEY --- ��`�悷��
	if (m_BrinkCounter < 30)
	{
		SetFontSize(20);
		DrawString(185, 450, "--- PRESS SPACE KEY ---", GetColor(255, 255, 255));
	}
}
