#pragma once
#include <memory>
#include "Rect.h"

/// <summary>
/// エネミーの基底クラス
/// </summary>
class Map;
class TutorialMap;
class Player;
class EnemyBase
{
public:

	EnemyBase(); //コンストラクタ
	virtual ~EnemyBase() {};//デストラクタ

	//メンバー変数にアクセスする
	void SetHandle(int handle) { m_handle = handle; }

	//マップのポインタを設定する
	void SetMap(std::shared_ptr<Map> pMap) { m_pMap = pMap; }
	//void SetTutorialMap(std::shared_ptr<TutorialMap> pTutorialMap) { m_pTutorialMap = pTutorialMap; }
	void SetPlayer(std::shared_ptr<Player> pPlayer) { m_pPlayer = pPlayer; }

	//
	void Start(float x, float y) { m_posX = x; m_posY = y; };
	virtual void Update() = 0;
	virtual void Draw() = 0;

	//敵の位置情報を取得
	float GetX()const { return m_posX; }
	float GetY()const { return m_posY; }

	float GetRadius();

	float GetLeft();
	float GetRight();
	float GetTop();
	float GetBottom();

	bool GetHitPlayerFlag(std::shared_ptr<Player> pPlayer);

	//現在の敵の矩形情報
	Rect getRect();

	bool IsCol(Rect rect, Rect& enemyRect);

protected:
	//Mapで決定したスクロール量を取得するためにMapクラスの情報が必要
	std::shared_ptr<Map> m_pMap;
	std::shared_ptr<TutorialMap> m_pTutorialMap;
	std::shared_ptr<Player>m_pPlayer;

	//グラフィックハンドル
	int m_handle;

	Rect m_colRect;

	float m_posX;
	float m_posY;
};

