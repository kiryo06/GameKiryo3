#pragma once
#include "MapData.h"
class MapData;
class Map
{public:

private:
	void Init(MapData& mapdata);
	void Update(MapData& mapdata);
	void Draw(MapData& mapdata);
	// 原型チップデータ
	MapDataFile::ChipData PrototypeChipData[MapDataFile::kChipNumY][MapDataFile::kChipNumX] = {};
};