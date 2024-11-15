#pragma once
#include "Vec2.h"
#include "Rect.h"

class Handle;

class Wall
{
public:
	Wall();
	~Wall();
	void Init(int x, int y);
	void Update();
	void Draw(const Handle& handle);

	// 配置座標の設定
	void SetPos(float x, float y) { m_pos = { x,y }; }

	// 当たり判定
	Rect GetRect() { return m_colRect; }



private:
	// 配置座標
	Vec2 m_pos;
	// playerとの当たり判定
	Rect m_colRect;
	// 動かない壁との差別化
	bool m_isFixed;
	// 壁が動いている途中かどうか
	bool m_isMove;
	// マウスキー入力
	bool m_isClick;
	// マウス入力座標
	Vec2 m_mousePos;
};

