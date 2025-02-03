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

	// 点滅用の変数に 1 を足す
	m_BrinkCounter++;

	// 点滅用の変数が 60 になっていたら 0 にする
	if (m_BrinkCounter == 60)
	{
		m_BrinkCounter = 0;
	}
}

void GameClear::Draw()
{
	DrawExtendGraph(0, 0,Game::kScreenWidth,Game::kScreenHeight, m_Graph_GAMECLEAR, true);
	// 点滅用の変数の値が 30 未満のときだけ --- PRESS SPACE KEY --- を描画する
	if (m_BrinkCounter < 30)
	{
		SetFontSize(20);
		DrawString(185, 450, "--- PRESS SPACE KEY ---", GetColor(255, 255, 255));
	}
}
