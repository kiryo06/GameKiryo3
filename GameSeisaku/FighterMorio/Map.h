#pragma once
#include "MapData.h"
class Camera;
class Map
{
public:
	/// <summary>
	/// 1-1_マップ情報初期化
	/// </summary>
	/// <param name="mapdata"></param>
	void Init(int mapNumber);
//	void Update_1();
//	void Update_2();
	void Draw(int mapNumber, Camera* camera);
private:
	// 原型チップデータ
	MapDataFile::ChipData PrototypeChipData[MapDataFile::kChipNumY][MapDataFile::kChipNumX] = {};
	// 1-1原型チップデータ
	MapDataFile::ChipData PrototypeChipDataOne[MapDataFile::kOneChipNumY][MapDataFile::kOneChipNumX] = {};
};