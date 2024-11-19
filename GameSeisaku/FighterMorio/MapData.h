#pragma once
#include "Game.h"
namespace MapDataFile
{
	struct ChipData
	{
		VECTOR pos;	// 座標
		int chipKind;
	};
	// マップチップの情報
	const int kChipWidth = 128;
	const int kChipHeight = 64;
	//縦横のチップの数
//スクロールさせるので画面サイズより広く
	const int kChipNumX = Game::kScreenWidth / kChipWidth;
	const int kChipNumY = Game::kScreenHeight / kChipHeight;
	//チップのサイズ、数からマップの広さを計算
	const int kMapWidth = kChipWidth * kChipNumX;
	const int kMapHeight = kChipWidth * kChipNumY;

	const int mapChipData[kChipNumY][kChipNumX] =
	{
		{ 1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1 }
	};
}