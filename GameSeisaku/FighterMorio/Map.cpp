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
		}
	}
}

void Map::Update()
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
					GetColor(255, 255, 255), TRUE);
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
