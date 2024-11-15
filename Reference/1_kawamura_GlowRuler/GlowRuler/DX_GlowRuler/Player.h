#pragma once
#include "Vec2.h"
#include "Rect.h"

class Map;
class Sound;

namespace
{
	// 移動速度
	constexpr float kSpeed = 16.0f;
	constexpr float kGoalSpeed = 0.25f;

	// プレイヤーサイズ
	constexpr int kSize = 15;
	constexpr int kEyeSize = 3;
	constexpr int kDontEyeSize = 5;
}

class Player
{
public:
	// 向いている方向
	enum Dir
	{
		kDirDown,	// 下
		kDirLeft,	// 左
		kDirRight,	// 右
		kDirUp		// 上
	};

	Player();
	~Player();
	void Init(float x, float y);
	void Update();
	void Draw();
	bool DrawPlayer(Vec2 point);

	void WallHit (Rect& wall);
	void DirWallHit(Rect& DirWall, bool& isPass);
	void GoalIn(Rect& goal);


	// プレイヤーの現在位置を取得する
	Vec2 GetPos() const { return m_pos; }
	// プレイヤーの当たり判定を取得する
	Rect GetColRect() const { return m_colRect; }
	// プレイヤーのゴール状況を取得
	bool GetGoal() const { return m_isClear; }
	// 壁との当たり判定
	bool GetHitFlag() const { return m_wallHit; }
	// 移動回数
	int GetMoveTime() const { return m_moveTime; }
	// 場所リセット
	void ResetPos() { m_pos = m_firstPos;	m_dir = kDirDown;  m_moveTime = 0; }
	
private:
	// グラフィック
	// int m_handle;
	// 移動中かどうか
	bool m_isMove;
	// 位置
	Vec2 m_pos;
	Vec2 m_firstPos;
	// 移動量
	Vec2 m_move;
	// 当たり判定用の矩形
	Rect m_colRect;
	// 方向
	Dir m_dir;
	// playerアニメーション
	// int m_animaFrame;

	bool m_wallHit;

	// 各キーが押しっぱなかどうか
	bool m_isLongUpKey; 
	bool m_isLongDownKey;
	bool m_isLongLeftKey;
	bool m_isLongRightKey;
	// プレイヤーがゴールに触れたかどうか
	bool m_isClear;
	// 移動回数
	Vec2 m_moving;
	int m_moveTime;
};