#include "GameClear.h"
#include <cmath>
#include "DxLib.h"

GameClear::GameClear():
	m_Graph_GAMECLEAR(0)
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
}

void GameClear::Draw()
{
	DrawExtendGraph(0, 0,Game::kScreenWidth,Game::kScreenHeight, m_Graph_GAMECLEAR, true);
}
