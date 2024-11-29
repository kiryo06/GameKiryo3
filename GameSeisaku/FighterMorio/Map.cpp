#include "Map.h"
#include "DxLib.h"
#include "Camera.h"
#include <cassert>

Map::Map()
{
}

Map::~Map()
{
}

void Map::Init(int mapNumber)
{
	switch (mapNumber)
	{
	case 0:
		// デバック
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
		// 1-1
		for (int hChip = 0; hChip < MapDataFile::k1ChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < MapDataFile::k1ChipNumX; wChip++)
			{
				PrototypeChipData1[hChip][wChip].chipKind = MapDataFile::mapChipData1[hChip][wChip];
				PrototypeChipData1[hChip][wChip].w = MapDataFile::kChipWidth;
				PrototypeChipData1[hChip][wChip].h = MapDataFile::kChipHeight;
				PrototypeChipData1[hChip][wChip].pos.x = wChip * MapDataFile::kChipWidth;
				PrototypeChipData1[hChip][wChip].pos.y = hChip * MapDataFile::kChipHeight;
			}
		}
		break;
	}
}


void Map::Draw(int mapNumber, Camera* camera)
{
	switch (mapNumber)
	{
	case 0:
		// デバック
		for (int hChip = 0; hChip < MapDataFile::kChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < MapDataFile::kChipNumX; wChip++)
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
						0xaaaaaa, TRUE);
				}
			}
		}
		break;
	case 1:
		// 1-1
		for (int hChip = 0; hChip < MapDataFile::k1ChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < MapDataFile::k1ChipNumX; wChip++)
			{
				// １は当たり判定チップを表しているので１のところだけ描画
				if (PrototypeChipData1[hChip][wChip].chipKind == 1)
				{
					auto leftTop = static_cast<int>(PrototypeChipData1[hChip][wChip].pos.x - PrototypeChipData1[hChip][wChip].w * 0.5f);
					auto leftBottom = static_cast<int>(PrototypeChipData1[hChip][wChip].pos.y - PrototypeChipData1[hChip][wChip].h * 0.5f);
					auto rightTop = static_cast<int>(PrototypeChipData1[hChip][wChip].pos.x + PrototypeChipData1[hChip][wChip].w * 0.5f);
					auto rightBottom = static_cast<int>(PrototypeChipData1[hChip][wChip].pos.y + PrototypeChipData1[hChip][wChip].h * 0.5f);

					DrawBox(
						leftTop + static_cast<int>(camera->GetCameraDrawOffset().x),
						leftBottom + static_cast<int>(camera->GetCameraDrawOffset().y),
						rightTop + static_cast<int>(camera->GetCameraDrawOffset().x),
						rightBottom + static_cast<int>(camera->GetCameraDrawOffset().y),
						0xaaaaaa, TRUE);
				}
			}
		}
		break;
	case 2:
		// 1-2

		break;
	}

	//for (int hChip = 0; hChip < MapDataFile::kChipNumY; hChip++)
	//{
	//	for (int wChip = 0; wChip < MapDataFile::kChipNumX; wChip++)
	//	{
	//		// １は当たり判定チップを表しているので１のところだけ描画
	//		if (PrototypeChipData[hChip][wChip].chipKind == 1)
	//		{
	//			auto leftTop = static_cast<int>(PrototypeChipData[hChip][wChip].pos.x - PrototypeChipData[hChip][wChip].w * 0.5f);
	//			auto leftBottom = static_cast<int>(PrototypeChipData[hChip][wChip].pos.y - PrototypeChipData[hChip][wChip].h * 0.5f);
	//			auto rightTop = static_cast<int>(PrototypeChipData[hChip][wChip].pos.x + PrototypeChipData[hChip][wChip].w * 0.5f);
	//			auto rightBottom = static_cast<int>(PrototypeChipData[hChip][wChip].pos.y + PrototypeChipData[hChip][wChip].h * 0.5f);

	//			DrawBox(
	//				leftTop + static_cast<int>(camera->GetCameraDrawOffset().x),
	//				leftBottom + static_cast<int>(camera->GetCameraDrawOffset().y),
	//				rightTop + static_cast<int>(camera->GetCameraDrawOffset().x),
	//				rightBottom + static_cast<int>(camera->GetCameraDrawOffset().y),
	//				0xaaaaaa, TRUE);
	//		}

	//	}
	//}
}
