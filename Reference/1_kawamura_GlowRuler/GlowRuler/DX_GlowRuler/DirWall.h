#pragma once
#include "Vec2.h"
#include "Rect.h"

class Handle;

class DirWall
{
	// 向いている方向
	enum Dir
	{
		kDirDown,	// 下
		kDirLeft,	// 左
		kDirRight,	// 右
		kDirUp		// 上
	};
public:
	DirWall();
	~DirWall();
	void Init(int x, int y, int dir);
	void Update(Rect& player);
	void Draw(const Handle& handle);

	// 配置座標の設定
	void SetPos(float x, float y) { m_pos = { x,y }; }
	// 配置座標の獲得
	// Vec2 GetRect() { return { m_pos.x + kGraphHalfWidth, m_pos.y + kGraphHalfHeight }; }

	// 当たり判定
	Rect GetRect() const { return m_colRect; }
	bool GetPass() const { return m_isPass; }
	int GetDir() const;

private:
	// 配置座標
	Vec2 m_pos;
	// playerとの当たり判定
	Rect m_colRect;
	// 通行方向
	Dir m_wallDir;

	bool m_isPass;
};

