#pragma once
#include "MapData.h"
struct Camera;
class Map
{public:
	/// <summary>
	/// マップ情報初期化
	/// </summary>
	/// <param name="mapdata"></param>
	void Init();
	/// <summary>
	/// 
	/// </summary>
	/// <param name="mapdata"></param>
	void Update();
	/// <summary>
	/// マップ描画
	/// </summary>
	/// <param name="mapdata"></param>
	void Draw(Camera& camera);
private:
	//int chipDataNUM[MapDataFile::kChipNumY][MapDataFile::kChipNumX] = {};
	// 原型チップデータ
	MapDataFile::ChipData PrototypeChipData[MapDataFile::kChipNumY][MapDataFile::kChipNumX] = {};
};