#pragma once
#include "game.h"
class GameOver
{
public:
	GameOver();
	~GameOver();
	void Init();
	void Update();
	void Draw();
private:
	int m_GameOverGraph_A;
	int m_GameOverGraph_E;
	int m_GameOverGraph_G;
	int m_GameOverGraph_M;
	int m_GameOverGraph_O;
	int m_GameOverGraph_R;
	int m_GameOverGraph_V;
};

