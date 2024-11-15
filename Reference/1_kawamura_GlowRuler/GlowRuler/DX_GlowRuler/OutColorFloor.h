#pragma once
#include "Vec2.h"
#include "Rect.h"
#include "Game.h"

namespace
{
	constexpr int kAlphaMax = 240;
	constexpr int kAlphaSpeed = 8;

	// Boxの分厚さ（回数）
	constexpr int kBoxNum = 4;

	// エフェクト用
	constexpr int kDirMax = 100;
	constexpr int kDrawDirMax = 30;
	// フレーム辺りのアルファ変化量
	constexpr int kAlphaPow = 10;

}

class Handle;

class OutColorFloor
{
public:
	OutColorFloor();
	~OutColorFloor();
	void Init(int x, int y, int color);
	void Update();
	void Draw(const Handle& handle);

	void Effect();

	// 配置座標の設定
	void SetPos(float x, float y) { m_pos = { x,y }; }
	// 当たり判定
	Rect GetRect() const { return m_colRect; }

	Vec2 GetPos() const { return m_pos; }

	// 色渡し
	int GetColor() const { return m_checkColor; }

	// 塗られた判定
	bool GetChack() const { return m_isClear; }

	// ステージやり直し
	void Reset();

private:
	// 壁グラフィック(画像データ未定)
	// int m_handle;

	// 配置座標
	Vec2 m_pos;
	// playerとの当たり判定
	Rect m_colRect;
	// つけるべき色
	int m_checkColor;
	// 着色判定
	bool m_isClear;
	// 着色部分のアルファ値
	int m_alpha;

	// 広げるエフェクト
	int m_dir;
	// 白光のアルファ
	int m_filterAlpha;
	// アルファ値上下フラグ
	int m_isFilter;
};

