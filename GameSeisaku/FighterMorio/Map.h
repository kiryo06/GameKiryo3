#pragma once
#include "MapData.h"
struct Camera;
class Map
{public:
	void Init();
	/// <summary>
	/// 1-1_マップ情報初期化
	/// </summary>
	/// <param name="mapdata"></param>
	void InitOne();
	/// <summary>
	/// 1-2_マップ情報初期化
	/// </summary>
	/// <param name="mapdata"></param>
	void InitTwo();
//	void Update_1();
//	void Update_2();
	void Draw(Camera& camera);
	/// <summary>
	/// 1-1_マップ描画
	/// </summary>
	/// <param name="mapdata"></param>
	void DrawOne(Camera& camera);
	/// <summary>
	/// 1-2_マップ描画
	/// </summary>
	/// <param name="mapdata"></param>
	void DrawTwo(Camera& camera);
private:
	// 原型チップデータ
	MapDataFile::ChipData PrototypeChipData[MapDataFile::kChipNumY][MapDataFile::kChipNumX] = {};
	// 1-1原型チップデータ
	MapDataFile::ChipData PrototypeChipDataOne[MapDataFile::kOneChipNumY][MapDataFile::kOneChipNumX] = {};
};