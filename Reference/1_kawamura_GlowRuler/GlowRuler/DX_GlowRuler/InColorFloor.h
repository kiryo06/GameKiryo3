#pragma once
#include "Vec2.h"
#include "Game.h"
#include "Rect.h"

class Handle;

namespace
{
	// 楕円の数
	constexpr int kEffectNum = 4;
	// 楕円のx,yの半径
	constexpr int kCircleRX = 20;
	constexpr int kCircleRY = 10;
	// 楕円の間隔
	constexpr int kEffectSpace = 10;
	// 楕円の最大位置
	constexpr int kEffectMaxY = -40;
	// 楕円の消え始め位置
	constexpr int kDisAppY = -30;
}

class InColorFloor
{
public:
	InColorFloor();
	~InColorFloor();
	void Init(int x, int y, int color);
	void Update();
	void Draw(const Handle& handle);

	void colorEffect();

	// 配置座標の設定
	void SetPos(float x, float y) { m_pos = { x,y }; }
	// 当たり判定
	Rect GetRect() const { return m_colRect; }
	// 色渡し
	int GetColor() const { return m_color; }

private:
	// 配置座標
	Vec2 m_pos;
	// playerとの当たり判定
	Rect m_colRect;
	// 色
	int m_color;
	// 楕円エフェクト
	int m_animaY[kEffectNum];
};

