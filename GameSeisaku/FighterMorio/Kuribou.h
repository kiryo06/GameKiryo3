#pragma once
#include "MapData.h"
	class Map;
class Camera;
class Player;
class Kuribou
{
public:
	Kuribou();
	~Kuribou();
	/// <summary>
	/// 敵の初期化
	/// </summary>
	void Init(int mapNumber);
	/// <summary>
	/// 敵の更新
	/// </summary>
	void Update(int mapNumber, Player* player);
	/// <summary>
	/// 未来の敵位置とマップの当たり判定を行い、調整したvelocity（移動ベクトル)を返す
	/// </summary>
	VECTOR CheckKuribouHitWithMap(int mapNumber);
	/// <summary>
	/// 敵とマップの当たり判定
	/// </summary>
	/// <param name="isHitWithMapY">横軸の変数</param>
	/// <param name="isHitWithMapX">縦軸の変数</param>
	/// <returns></returns>
	bool IsHitKuribouWithMapChip(int mapNumber, const VECTOR& checkPos, int hChip, int wChip);
	/// <summary>
	/// 頭上がぶつかっているか見る
	/// </summary>
	void CheckIsTopHit(int mapNumber);
	/// <summary>
	/// 地面に接地しているか見る
	/// </summary>
	void CheckIsGround(int mapNumber);
	/// <summary>
	/// 左の壁に接地しているか見る
	/// </summary>
	void CheckIsLeft(int mapNumber);
	/// <summary>
	/// 右の壁に接地しているか見る
	/// </summary>
	void CheckIsRight(int mapNumber);
	/// <summary>
	/// プレイヤーによる攻撃を受けた時の処理
	/// </summary>
	void OnDamage();
	/// <summary>
	/// 敵描画
	/// </summary>
	void Draw(Camera* camera);
	VECTOR GetKuribouPos() const { return pos; }
	VECTOR GetKuribouDir() const { return dir; }
	float GetW() const { return w; }
	float GetH() const { return h; }
	void SetDese(bool isdese) { isDese = isdese; }
	bool IsDese()const { return isDese; }
private:
	float w, h;					// 幅、高さ
	float fallSpeed;			// 敵の落下速度。ジャンプ時は反転する
	float workSpeed;			// 左右移動速度
	VECTOR pos;					// 座標 横：中心　縦：中心
	VECTOR dir;					// 座標の移動方向
	VECTOR velocity;			// 速度の計算等
	int DamageFlag;				// ダメージを受けたとき
	int Life;					// 敵のHP
	bool isGround;				// 敵の足が地面についているかどうか
	bool isHitTop;				// 敵の頭が天井に当たっているか
	bool isLeft;				// 敵が左に当たったか
	bool isRight;				// 敵が右に当たったか
	bool isDese;
	int EnemyDese;
	int m_EnemyGraph;			// クリボウ仮実装
	int mapChip;
	int m_kChipNumY;			// マップの大きさ横軸デバック
	int m_kChipNumX;			// マップの大きさ縦軸デバック
	int m_k1ChipNumY;			// マップの大きさ横軸1-1
	int m_k1ChipNumX;			// マップの大きさ縦軸1-1
	int m_k2ChipNumY;			// マップの大きさ横軸1-2
	int m_k2ChipNumX;			// マップの大きさ横軸1-2
	Map* m_pMap;
	Camera* m_pCamera;
	Player* m_pPlayer;
	// 原型チップデータ1-1用
	MapDataFile::ChipData PrototypeChipData[MapDataFile::kChipNumY][MapDataFile::kChipNumX] = {};
	// 原型チップデータ1-2用
	MapDataFile::ChipData PrototypeChipData1[MapDataFile::k1ChipNumY][MapDataFile::k1ChipNumX] = {};
	// 原型チップデータ
	MapDataFile::ChipData PrototypeChipData2[MapDataFile::k2ChipNumY][MapDataFile::k2ChipNumX] = {};
};

