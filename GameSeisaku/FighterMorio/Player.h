#pragma once
#include "MapData.h"
class Map;
class Camera;
class BaseEnemy;
class Player
{
public:
	Player();
	~Player();
	/// <summary>
	/// プレイヤーの初期化
	/// </summary>
	void Init(int mapNumber);
	/// <summary>
	/// プレイヤーの更新
	/// </summary>
	void Update(int mapNumber);
	/// <summary>
	/// 未来のプレイヤー位置とマップの当たり判定を行い、調整したvelocity（移動ベクトル)を返す
	/// </summary>
	VECTOR CheckPlayerHitWithMap(int mapNumber);
	/// <summary>
	/// プレイヤーとマップの当たり判定
	/// </summary>
	/// <param name="isHitWithMapY">横軸の変数</param>
	/// <param name="isHitWithMapX">縦軸の変数</param>
	/// <returns></returns>
	bool IsHitPlayerWithMapChip(int mapNumber, const VECTOR& checkPos, int hChip, int wChip);
	/// <summary>
	/// プレイヤーと敵の当たり判定
	/// </summary>
	bool IsHitPlayerAndEnemy(const VECTOR& checkPos);
	/// <summary>
	/// 頭上がぶつかっているか見る
	/// </summary>
	void CheckIsTopHit(int mapNumber);
	/// <summary>
	/// 地面に接地しているか見る
	/// </summary>
	void CheckIsGround(int mapNumber);
	void CheckIsEnemyTop();
	/// <summary>
	/// プレイヤー描画
	/// </summary>
	void Draw(int mapNumber, Camera* camera);
	VECTOR GetPlayerPos() const { return pos; }
	VECTOR GetPlayerDir() const { return dir; }
private:
	Map* m_pMap;
	Camera* m_pCamera;
	BaseEnemy* m_pBaseEnemy;
	float w, h;					// 幅、高さ
	float fallSpeed;			// プレイヤーの落下速度。ジャンプ時は反転する
	VECTOR pos;					// 座標 横：中心　縦：中心
	VECTOR dir;					// 座標の移動方向
	VECTOR velocity;
	bool isGround;				// プレイヤーが接地中か
	bool isHitTop;				// プレイヤーの頭が天井に当たっているか
	bool isHitEnemy;
	int isEnemyHitDese;
	int mapChip;
	int _isHit;
	int m_PlayerGraph;
	int m_kChipNumY;
	int m_kChipNumX;
	int m_k1ChipNumY;
	int m_k1ChipNumX;
	int m_k2ChipNumY;
	int m_k2ChipNumX;
	// 原型チップデータ
	MapDataFile::ChipData PrototypeChipData[MapDataFile::kChipNumY][MapDataFile::kChipNumX] = {};
	// 原型チップデータ
	MapDataFile::ChipData PrototypeChipData1[MapDataFile::k1ChipNumY][MapDataFile::k1ChipNumX] = {};
	// 原型チップデータ
	MapDataFile::ChipData PrototypeChipData2[MapDataFile::k2ChipNumY][MapDataFile::k2ChipNumX] = {};
};
