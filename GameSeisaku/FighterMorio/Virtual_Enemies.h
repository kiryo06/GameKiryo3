#pragma once
#include "MapData.h"
class Map;
class Camera;
class Virtual_Enemies
{
public:
	Virtual_Enemies();
	~Virtual_Enemies();
	/// <summary>
	/// 敵の初期化
	/// </summary>
	void Init(int mapNumber);
	/// <summary>
	/// 敵の更新
	/// </summary>
	void Update(int mapNumber);
	/// <summary>
	/// 未来の敵位置とマップの当たり判定を行い、調整したvelocity（移動ベクトル)を返す
	/// </summary>
	VECTOR CheckVirtual_EnemiesHitWithMap(int mapNumber);
	/// <summary>
	/// 敵とマップの当たり判定
	/// </summary>
	/// <param name="isHitWithMapY">横軸の変数</param>
	/// <param name="isHitWithMapX">縦軸の変数</param>
	/// <returns></returns>
	bool IsHitVirtual_EnemiesWithMapChip(int mapNumber, const VECTOR& checkPos, int hChip, int wChip);
	/// <summary>
	/// 頭上がぶつかっているか見る
	/// </summary>
	void CheckIsTopHit(int mapNumber);
	/// <summary>
	/// 地面に接地しているか見る
	/// </summary>
	void CheckIsGround(int mapNumber);
	/// <summary>
	/// 敵の描画
	/// </summary>
	void Draw(Camera* camera);
	VECTOR GetPlayerPos() { return pos; }
	VECTOR GetPlayerDir() { return dir; }
private:
	float w, h;					// 幅、高さ
	float fallSpeed;				// 敵の落下速度。ジャンプ時は反転する
	VECTOR pos;					// 座標 横：中心　縦：中心
	VECTOR dir;					// 座標の移動方向
	VECTOR velocity;
	bool isGround;				// 敵が接地中か
	bool isHitTop;				// 敵の頭が天井に当たっているか
	bool mapChipY;				// マップの縦軸
	bool mapChipX;				// マップの横軸
	int _isHit = 0;
	Map* m_map;
	Camera* m_camera;
	int m_mapkChipNumY;
	int m_mapkChipNumX;
	/*int m_mapkChipNumY_0;
	int m_mapkChipNumX_0;
	int m_mapkChipNumY_1;
	int m_mapkChipNumX_1;*/
	// 原型チップデータ
	MapDataFile::ChipData PrototypeChipData1[MapDataFile::kChipNumY][MapDataFile::kChipNumX] = {};
	// 原型チップデータ
	MapDataFile::ChipData PrototypeChipData[MapDataFile::k1ChipNumY][MapDataFile::k1ChipNumX] = {};
};
