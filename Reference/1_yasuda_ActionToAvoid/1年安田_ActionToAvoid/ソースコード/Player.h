#pragma once
#include <memory>
#include "Rect.h"

/// <summary>
/// プレイヤークラス
/// </summary>
class Map;
class GamePlayingScene;
class Player
{
public:
	Player(); //コンストラクタ
	virtual ~Player();//デストラクタ

	//マップのポインタを設定する
	void SetMap(std::shared_ptr<Map> pMap) { m_pMap = pMap; }
	//void SetGamePlaying(std::shared_ptr<GamePlayingScene> pGamePlayingScene) { m_pGamePlaying = pGamePlayingScene; }
	

	void Init();//初期化処理
	void Update();//アップデート処理
	void Draw();//描画処理


	//プレイヤーの位置情報を取得
	float GetX() const { return m_posX; }
	float GetY() const { return m_posY; }
	//円の当たり判定
	float GetRadius();

	//ダメージを
	void Damage();

	//プレイヤーの上下左右座標を取得
	float GetLeft();
	float GetRight();
	float GetTop();
	float GetBottom();

	void CommandOff();//プレイヤーが死んだら操作オフの関数
	void FallRestart();//プレイヤーが落ちたら初期位置に戻る

	//現在のプレイヤーの矩形情報取得
	Rect getRect();

private:

	enum Dir//向いてる方向
	{
		kNutral, //通常状態 0
		kWalk,	 //歩き状態 1
		kNo,	 //いらない 2
		kFall,   //落ちる状態 3
		kDash,	//当たった状態 4
	};

	//Mapで決定したスクロール量を取得するためにMapクラスの情報が必要
	std::shared_ptr<Map> m_pMap;

	std::shared_ptr<GamePlayingScene> m_pGamePlaying;


	//キャラクターのグラフィックハンドル
	int m_playerHandle01;
	int m_playerHandle02;

	int m_seHandle001; //ジャンプする音

	int m_jumpCount = 0;

	// ダメージを受けてからのフレーム数
	// 普段はゼロ
	// 当たったときにフレーム数を設定して
	// 以降舞フレーム減らしていく
	int m_damageFrame;

	//ジャンプしているかどうかのフラグを持つ
	//空中にいる場合はture、地面に立っている場合はfalse
	bool m_isJump;
	//右に移動しているかどうかのフラグ
	bool m_isRight;
	//左に移動しているかどうかのフラグ
	bool m_isLeft;
	//操作しているかどうかのフラグ
	bool m_isCommand;

	//ダメージした立つフラグ
	bool m_isDamage = false;

	//プレイヤーの足元中央を基準とした座標
	float m_posX;
	float m_posY;

	//プレイヤーの加速度	1フレーム当たりの移動量
	float m_moveX;
	float m_moveY;

	// 向いてる方向
	Dir m_dir; 

	//キャラがどちらを向いてるかどうかのフラグ
	bool m_isAnimTurn;
	//キャラがジャンプ描画されてるかどうかのフラグ
	bool m_isAnimJump;


	int m_animationFrame; //アニメーションのフレーム
	//アニメーション
	int m_animFrame;//アニメーションのフレーム
	int m_animCount;//アニメーションのカウント

};

