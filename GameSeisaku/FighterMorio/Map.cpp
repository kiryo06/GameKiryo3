#include "Map.h"
#include "DxLib.h"
#include "MapData.h"
#include "Camera.h"
#include <cassert>

void Map::Init(int mapNumber)
{
	switch (mapNumber)
	{
	case 0:
		// マップデータ読み込み
		for (int hChip = 0; hChip < MapDataFile::kChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < MapDataFile::kChipNumX; wChip++)
			{
				PrototypeChipData[hChip][wChip].chipKind = MapDataFile::mapChipData[hChip][wChip];
				PrototypeChipData[hChip][wChip].w = MapDataFile::kChipWidth;
				PrototypeChipData[hChip][wChip].h = MapDataFile::kChipHeight;
				PrototypeChipData[hChip][wChip].pos.x = wChip * MapDataFile::kChipWidth;
				PrototypeChipData[hChip][wChip].pos.y = hChip * MapDataFile::kChipHeight;
			}
		}
		break;
	case 1:
		// マップデータ読み込み
		for (int hChip = 0; hChip < MapDataFile::k1ChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < MapDataFile::k1ChipNumX; wChip++)
			{
				PrototypeChipData[hChip][wChip].chipKind = MapDataFile::mapChipData1[hChip][wChip];
				PrototypeChipData[hChip][wChip].w = MapDataFile::kChipWidth;
				PrototypeChipData[hChip][wChip].h = MapDataFile::kChipHeight;
				PrototypeChipData[hChip][wChip].pos.x = wChip * MapDataFile::kChipWidth;
				PrototypeChipData[hChip][wChip].pos.y = hChip * MapDataFile::kChipHeight;
			}
		}
		break;
	case 2:
		break;
	}
}


void Map::Draw(int mapNumber, Camera* camera)
{
	int MapChipNumY = 0;
	int MapChipNumX = 0;
	switch (mapNumber)
	{
	case 0:
		MapChipNumY = MapDataFile::kChipNumY;
		MapChipNumX = MapDataFile::kChipNumX;
		break;
	case 1:
		MapChipNumY = MapDataFile::k1ChipNumY;
		MapChipNumX = MapDataFile::k1ChipNumX;
		break;
	case 2:
	default:
		assert(false);
		return;
	}
	for (int hChip = 0; hChip < MapChipNumY; hChip++)
	{
		for (int wChip = 0; wChip < MapChipNumX; wChip++)
		{
			// １は当たり判定チップを表しているので１のところだけ描画
			if (PrototypeChipData[hChip][wChip].chipKind == 1)
			{
				auto leftTop = static_cast<int>(PrototypeChipData[hChip][wChip].pos.x - PrototypeChipData[hChip][wChip].w * 0.5f);
				auto leftBottom = static_cast<int>(PrototypeChipData[hChip][wChip].pos.y - PrototypeChipData[hChip][wChip].h * 0.5f);
				auto rightTop = static_cast<int>(PrototypeChipData[hChip][wChip].pos.x + PrototypeChipData[hChip][wChip].w * 0.5f);
				auto rightBottom = static_cast<int>(PrototypeChipData[hChip][wChip].pos.y + PrototypeChipData[hChip][wChip].h * 0.5f);

				DrawBox(
					leftTop + static_cast<int>(camera->GetCameraDrawOffset().x),
					leftBottom + static_cast<int>(camera->GetCameraDrawOffset().y),
					rightTop + static_cast<int>(camera->GetCameraDrawOffset().x),
					rightBottom + static_cast<int>(camera->GetCameraDrawOffset().y),
					0xaaaaaa/*GetColor(255, 255, 255)*/, TRUE);
			}

		}
	}
}
/*for (int hChip = 0; hChip < MapDataFile::kChipNumY; hChip++)
	{
		for (int wChip = 0; wChip < MapDataFile::kChipNumX; wChip++)
		{
			chipDataNUM[hChip][wChip] = MapDataFile::mapChipData[hChip][wChip];


		}
	}
	if (PrototypeChipData[wChip][hChip] == 1)
	{
		PrototypeChipData[wChip][hChip] =
	}*/
