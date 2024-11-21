#include "Map.h"
#include "DxLib.h"
#include "MapData.h"
#include "Camera.h"

void Map::Init()
{
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
}

void Map::InitOne()
{
	// マップデータ読み込み
	for (int hChip = 0; hChip < MapDataFile::kOneChipNumY; hChip++)
	{
		for (int wChip = 0; wChip < MapDataFile::kOneChipNumX; wChip++)
		{
			PrototypeChipDataOne[hChip][wChip].chipKind = MapDataFile::mapChipDataOne[hChip][wChip];
			PrototypeChipDataOne[hChip][wChip].w = MapDataFile::kOneChipWidth;
			PrototypeChipDataOne[hChip][wChip].h = MapDataFile::kOneChipHeight;
			PrototypeChipDataOne[hChip][wChip].pos.x = wChip * MapDataFile::kOneChipWidth;
			PrototypeChipDataOne[hChip][wChip].pos.y = hChip * MapDataFile::kOneChipHeight;
		}
	}
}

void Map::InitTwo()
{
}

void Map::Draw(Camera& camera)
{
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
					leftTop + static_cast<int>(camera.drawOffset.x),
					leftBottom + static_cast<int>(camera.drawOffset.y),
					rightTop + static_cast<int>(camera.drawOffset.x),
					rightBottom + static_cast<int>(camera.drawOffset.y),
					0xaaaaaa/*GetColor(255, 255, 255)*/, TRUE);
			}

		}
	}
}

void Map::DrawOne(Camera& camera)
{
	for (int hChip = 0; hChip < MapDataFile::kOneChipNumY; hChip++)
	{
		for (int wChip = 0; wChip < MapDataFile::kOneChipNumX; wChip++)
		{
			// １は当たり判定チップを表しているので１のところだけ描画
			if (PrototypeChipDataOne[hChip][wChip].chipKind == 1)
			{
				auto leftTop = static_cast<int>(PrototypeChipDataOne[hChip][wChip].pos.x - PrototypeChipDataOne[hChip][wChip].w * 0.5f);
				auto leftBottom = static_cast<int>(PrototypeChipDataOne[hChip][wChip].pos.y - PrototypeChipDataOne[hChip][wChip].h * 0.5f);
				auto rightTop = static_cast<int>(PrototypeChipDataOne[hChip][wChip].pos.x + PrototypeChipDataOne[hChip][wChip].w * 0.5f);
				auto rightBottom = static_cast<int>(PrototypeChipDataOne[hChip][wChip].pos.y + PrototypeChipDataOne[hChip][wChip].h * 0.5f);

				DrawBox(
					leftTop + static_cast<int>(camera.drawOffset.x),
					leftBottom + static_cast<int>(camera.drawOffset.y),
					rightTop + static_cast<int>(camera.drawOffset.x),
					rightBottom + static_cast<int>(camera.drawOffset.y),
					0xaaaaaa/*GetColor(255, 255, 255)*/, TRUE);
			}

		}
	}
}

void Map::DrawTwo(Camera& camera)
{
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
