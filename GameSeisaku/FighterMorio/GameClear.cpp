#include "GameClear.h"
#include <cmath>
#include "DxLib.h"

namespace
{
	/*int spriteSheet = LoadGraph("data/image/Enemy.png");*/
	int GraphSizeX = 3840;
	int frameWidth = 128;  // フレームの幅
	int frameHeight = 128; // フレームの高さ
	int currentFrame = 0; // 現在のフレーム
	int frameCount = GraphSizeX/ frameWidth;   // フレームの総数
	int frameTime = 10;   // フレームの表示時間
	int frameTimer = 0;   // フレームタイマー
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
	// フレームタイマーの更新
	frameTimer++;
	if (frameTimer >= frameTime) {
		frameTimer = 0;
		currentFrame = (currentFrame + 1) % frameCount;
	}



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
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x999999,TRUE);
	int x = (currentFrame % frameCount) * frameWidth;
	int y = frameHeight;
	DrawRectGraph(64,128, x, y, frameWidth, frameHeight, m_Graph_, FALSE);
	//DrawExtendGraph(0, 0,Game::kScreenWidth,Game::kScreenHeight, m_Graph_GAMECLEAR, true);
	DrawRectExtendGraph(0,0,64,64, x, y, frameWidth, frameHeight, m_Graph_, FALSE);
	//DrawGraph(0,0, m_Graph_, true);
#ifdef _DEBUG
	// 点滅用の変数の値が 30 未満のときだけ --- PRESS SPACE KEY --- を描画する
	if (m_BrinkCounter < 30)
	{
		SetFontSize(20);
		DrawString(185, 450, "--- PRESS SPACE KEY ---", GetColor(255, 255, 255));
	}
#endif // _DEBUG
}
