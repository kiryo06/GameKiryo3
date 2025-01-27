#pragma once
#include "DxLib.h"
class GameOver
{
public:
	GameOver();
	~GameOver();
	void Init();
	void Update();
	void Draw();
	void CheckIsGround();
	bool IsHitGround(const VECTOR& checkPos);
private:
	float w, h;					// プレイヤーの幅と高さ
	float fallSpeed;			// 落下速度
	VECTOR pos;					// 座標 横：中心　縦：中心
	VECTOR dir;					// 座標の移動方向
	VECTOR velocity;
	bool isGround;
	int m_GameOverGraph_A;
	int m_GameOverGraph_E;
	int m_GameOverGraph_G;
	int m_GameOverGraph_M;
	int m_GameOverGraph_O;
	int m_GameOverGraph_R;
	int m_GameOverGraph_V;
};

