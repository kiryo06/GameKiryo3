#pragma once
#include "Game.h"
#include <iostream>

// マップチップの情報
const int kChipWidth = 32;
const int kChipHeight = 32;
//縦横のチップの数
//スクロールさせるので画面サイズより広く
const int kChipNumX = 480;
const int kChipNumY = 30;
//チップのサイズ、数からマップの広さを計算
const int kMapWidth = kChipWidth * kChipNumX;
const int kMapHeight = kChipWidth * kChipNumY;

/// <summary>
/// マップチップ構造体
/// </summary>
struct MapDateChips
{
	VECTOR pos;	// 座標
	float w, h;	// 幅、高さ
	int chipKind;
};
/// <summary>
/// マップ構造体
/// </summary>
struct MapDate
{
	MapDateChips mapDateChips[Game::kStageNum][kChipNumY][kChipNumX];
};
struct Camera;
void InitMapDate(MapDate& mapdate);
void DrawMapDate(const MapDate& map, const Camera& camera);