#pragma once
#include "MapData.h"
class Map;
class Camera;
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
	void Update();
	/// <summary>
	/// 未来のプレイヤー位置とマップの当たり判定を行い、調整したvelocity（移動ベクトル)を返す
	/// </summary>
	VECTOR CheckPlayerHitWithMap();
	/// <summary>
	/// プレイヤーとマップの当たり判定
	/// </summary>
	/// <param name="isHitWithMapY">横軸の変数</param>
	/// <param name="isHitWithMapX">縦軸の変数</param>
	/// <returns></returns>
	bool IsHitPlayerWithMapChip(const VECTOR& checkPos, int hChip, int wChip);
	/// <summary>
	/// 頭上がぶつかっているか見る
	/// </summary>
	void CheckIsTopHit();
	/// <summary>
	/// 地面に接地しているか見る
	/// </summary>
	void CheckIsGround();
	/// <summary>
	/// プレイヤー描画
	/// </summary>
	void Draw(Camera* camera);
	VECTOR GetPlayerPos() { return pos; }
	VECTOR GetPlayerDir() { return dir; }
private:
	float w, h;					// 幅、高さ
	float fallSpeed;				// プレイヤーの落下速度。ジャンプ時は反転する
	VECTOR pos;					// 座標 横：中心　縦：中心
	VECTOR dir;					// 座標の移動方向
	VECTOR velocity;
	bool isGround;				// プレイヤーが接地中か
	bool isHitTop;				// プレイヤーの頭が天井に当たっているか
	Map* m_map;
	Camera* m_camera;

	// 原型チップデータ
	MapDataFile::ChipData PrototypeChipData[MapDataFile::kChipNumY][MapDataFile::kChipNumX] = {};
};
