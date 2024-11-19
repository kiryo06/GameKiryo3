#include "Map.h"
#include "DxLib.h"
#include "MapData.h"

void Map::Init(MapData& mapdata)
{
	for (int wChip = 0; wChip < MapDataFile::kChipNumY; wChip++)
	{
		for (int hChip = 0; hChip < MapDataFile::kChipNumX; hChip++)
		{
			PrototypeChipData[wChip][hChip] = MapDataFile::mapChipData[MapDataFile::kChipNumY][MapDataFile::kChipNumX];

		}
	}
}

void Map::Update(MapData& mapdata)
{
}

void Map::Draw(MapData& mapdata)
{
	for (int wChip = 0; wChip < MapDataFile::kChipNumY; wChip++)
	{
		for (int wChip = 0; wChip < MapDataFile::kChipNumX; wChip++)
		{

		}
	}
}
