#pragma once
#include <memory>
#include "Rect.h"

class Player;
class Map;
class TutorialMap;
class ItemBase
{
public:
	ItemBase();
	virtual ~ItemBase() {};

	//メンバー変数にアクセスする
	void SetHandle(int handle) { m_handle = handle; }

	//マップのポインタを設定する
	void SetMap(std::shared_ptr<Map> pMap) { m_pMap = pMap; }
	void SetTutorialMap(std::shared_ptr<TutorialMap> pTutorialMap) { m_pTutorialMap = pTutorialMap; }

	void SetPlayer(std::shared_ptr<Player> pPlayer) { m_pPlayer = pPlayer; }

	void Start(int x, int y) { m_posX = x; m_posY = y; }
	virtual void Update() = 0;
	virtual void Draw() = 0;

	//アイテムが消える処理
	void ItemLost();

	//アイテムの位置情報を取得
	float GetX()const { return m_posX; }
	float GetY()const { return m_posY; }

	//アイテムの半径を取得
	float GetRadius();

	//プレイヤーとの当たり判定フラッグ
	bool GetHitPlayerFlag(std::shared_ptr<Player> pPlayer);

	bool isExist()const { return m_isExist; }

protected:
	//グラフィックハンドル
	int m_handle;
	//アイテムの位置
	float m_posX;
	float m_posY;

	bool m_isExist = false;


	std::shared_ptr<Map> m_pMap;
	std::shared_ptr<TutorialMap> m_pTutorialMap;
	std::shared_ptr<Player>m_pPlayer;

};

