#pragma once
#include "Game.h"
#include "DxLib.h"
namespace MapDataFile
{
	struct ChipData
	{
		VECTOR pos;	// 座標
		float w, h;	// 幅、高さ
		int chipKind;
	};
	// マップチップの情報
	const int kChipWidth = 32;
	const int kChipHeight = 32;
	// 1-1マップの広さ
	const int kMapX = Game::kScreenWidth * 5;
	const int kMapY = Game::kScreenHeight * 1.2f;
	// 1-1マップチップ数
	const int kChipNumX = kMapX / kChipWidth;
	const int kChipNumY = kMapY / kChipHeight;
	// 位置情報で使うかも?
	const int kMapWidth = kChipWidth * kChipNumX;
	const int kMapHeight = kChipHeight * kChipNumY;
	// 1-1マップの情報
	const int mapChipData[kChipNumY][kChipNumX] =
	{
		{ 1,0,0,0,0,0,0,0,0,0 },
		{ 0,1,0,0,0,0,0,0,0,0 },
		{ 0,0,1,0,0,0,0,0,0,0 },
		{ 0,0,0,1,0,0,0,0,0,0 },
		{ 0,0,0,0,1,0,0,0,0,0 },
		{ 0,0,0,0,0,1,0,0,0,0 },
		{ 0,0,0,0,0,0,1,0,0,0 },
		{ 0,0,0,0,0,0,0,1,0,0 },
		{ 0,0,0,0,0,0,0,0,1,0 },
		{ 0,0,0,0,0,0,0,0,1,0 },
		{ 0,0,0,0,0,0,0,0,1,0 },
		{ 0,0,0,0,0,0,0,0,1,0 },
		{ 0,0,0,0,0,0,0,0,1,0 },
		{ 0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0 },
		{ 0,1,0,0,0,0,0,0,0,0 },
		{ 0,0,1,0,0,0,0,0,0,0 },
		{ 0,0,0,1,0,0,0,0,0,0 },
		{ 0,0,0,0,1,0,0,0,0,0 },
		{ 0,0,0,0,0,1,0,0,0,0 },
		{ 0,0,0,0,0,0,1,0,0,0 },
		{ 0,0,0,0,0,0,0,1,0,0 },
		{ 0,0,0,0,0,0,0,0,1,0 },
		{ 1,1,1,1,1,1,1,1,1,1 }
	};


	// マップチップの情報
	const int kOneChipWidth = 32;
	const int kOneChipHeight = 32;
	// 1-1マップの広さ
	const int kOneMapX = Game::kScreenWidth * 5;
	const int kOneMapY = Game::kScreenHeight * 1.2;
	// 1-1マップチップ数
	const int kOneChipNumX = kOneMapX / kOneChipWidth;
	const int kOneChipNumY = kOneMapY / kOneChipHeight;
	// 位置情報で使うかも?
	const int kOneMapWidth = kOneChipWidth * kOneChipNumX;
	const int kOneMapHeight = kOneChipHeight * kOneChipNumY;
	// 1-1マップの情報
	const int mapChipDataOne[kOneChipNumY][kOneChipNumX] =
	{
		{ 1,0,0,0,0,0,0,0,0,0 },
		{ 0,1,0,0,0,0,0,0,0,0 },
		{ 0,0,1,0,0,0,0,0,0,0 },
		{ 0,0,0,1,0,0,0,0,0,0 },
		{ 0,0,0,0,1,0,0,0,0,0 },
		{ 0,0,0,0,0,1,0,0,0,0 },
		{ 0,0,0,0,0,0,1,0,0,0 },
		{ 0,0,0,0,0,0,0,1,0,0 },
		{ 0,0,0,0,0,0,0,0,1,0 },
		{ 0,0,0,0,0,0,0,0,1,0 },
		{ 0,0,0,0,0,0,0,0,1,0 },
		{ 0,0,0,0,0,0,0,0,1,0 },
		{ 0,0,0,0,0,0,0,0,1,0 },
		{ 0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0 },
		{ 0,1,0,0,0,0,0,0,0,0 },
		{ 0,0,1,0,0,0,0,0,0,0 },
		{ 0,0,0,1,0,0,0,0,0,0 },
		{ 0,0,0,0,1,0,0,0,0,0 },
		{ 0,0,0,0,0,1,0,0,0,0 },
		{ 0,0,0,0,0,0,1,0,0,0 },
		{ 0,0,0,0,0,0,0,1,0,0 },
		{ 0,0,0,0,0,0,0,0,1,0 },
		{ 1,1,1,1,1,1,1,1,1,1 }
	};
}