#pragma once
#include <memory>

class Player;
class Map;
class TutorialMap;
class Goal
{
public:
	Goal();
	virtual ~Goal();

	void Init();
	void Update();
	void Draw();

	//マップのポインタを設定する
	void SetMap(std::shared_ptr<Map> pMap) { m_pMap = pMap; }
	void SetTutorialMap(std::shared_ptr<TutorialMap> pTutorialMap) { m_pTutorialMap = pTutorialMap; }

	void SetPlayer(std::shared_ptr<Player> pPlayer) { m_pPlayer = pPlayer; }

	//メンバー変数にアクセスする
	void SetHandle(int handle) { m_handle = handle; }

	//アイテムの位置情報を取得
	float GetX()const { return m_posX; }
	float GetY()const { return m_posY; }

	//アイテムの半径を取得
	float GetRadius();

	//プレイヤーとの当たり判定フラッグ
	bool GetHitPlayerFlag(std::shared_ptr<Player> pPlayer);

private:
	//グラフィックハンドル
	int m_handle;
	//アイテムの位置
	float m_posX;
	float m_posY;

	std::shared_ptr<Map> m_pMap;
	std::shared_ptr<TutorialMap> m_pTutorialMap;
	std::shared_ptr<Player>m_pPlayer;

	int m_animFrame = 0;

};

