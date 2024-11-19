#include "DxLib.h"
#include "Screen.h"
#include "Map.h"
#include "Camera.h"
#include "MapDate.h"

void InitMap(const Map& map, const MapDate& mapdate)
{
	for (int sTage = 0; sTage < Game::kStageNum; sTage++)
	{
		for (int wIndex = 0; wIndex < kChipNumY; wIndex++)
		{
			for (int hIndex = 0; hIndex < kChipNumX; hIndex++)
			{
				MapChip& mapChip = map.mapDateChips[Game::kStageNum][wIndex][hIndex];
				mapChip.w = kChipWidth;
				mapChip.h = kChipHeight;
				mapChip.chipKind = map.mapDateChips[Game::kStageNum][wIndex][hIndex];

				// ポジションの基準を真ん中に
				mapChip.pos = VGet(wIndex * mapChip.w + mapChip.w * 0.5f, hIndex * mapChip.h + mapChip.w * 0.5f, 0);
			}
		}
	}
}

void DrawMap(const Map& map, const MapDate& mapdate, const Camera& camera)
{
	for (int sTage = 0; sTage < Game::kStageNum; sTage++)
	{
		for (int wIndex = 0; wIndex < kChipNumY; wIndex++)
		{
			for (int hIndex = 0; hIndex < kChipNumX; hIndex++)
			{
				// １は当たり判定チップを表しているので１のところだけ描画
				const MapChip& mapChip = map.mapDateChips[Game::kStageNum][wIndex][hIndex];
				if (mapChip.chipKind == 1)
				{
					auto leftTop = static_cast<int>(mapChip.pos.x - mapChip.w * 0.5f);
					auto leftBottom = static_cast<int>(mapChip.pos.y - mapChip.h * 0.5f);
					auto rightTop = static_cast<int>(mapChip.pos.x + mapChip.w * 0.5f);
					auto rightBottom = static_cast<int>(mapChip.pos.y + mapChip.h * 0.5f);
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
}


/*
Map::Map()
{
	for (int i = 0; i < kChipNumY; i++)
	{
		for (int j = 0; j < kChipNumX; j++)
		{
			chipData[i][j] = 0;
		}
	}

	std::vector <std::shared_ptr<BaseMapChip>> temp;
	temp.push_back(std::make_shared<BaseMapChip>(0));
	m_chipData.push_back(temp);
}
*/