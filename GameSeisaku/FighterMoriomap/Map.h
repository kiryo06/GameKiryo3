#pragma once
#include "Game.h"
class MapDate;
struct Camera;
/// <summary>
/// マップチップ構造体
/// </summary>
struct MapChip
{
	VECTOR pos;	// 座標
	float w, h;	// 幅、高さ
	int chipKind;
};
struct Map
{
	MapDateChips mapDateChips[Game::kStageNum][kChipNumY];
};
void InitMap(const Map& map, const MapDate& mapdate);
void DrawMap(const Map& map, const MapDate& mapdate, const Camera& camera);