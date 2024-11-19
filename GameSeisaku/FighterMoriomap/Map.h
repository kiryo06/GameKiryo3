#pragma once
#include "Game.h"
class MapDate;
struct Camera;
/// <summary>
/// �}�b�v�`�b�v�\����
/// </summary>
struct MapChip
{
	VECTOR pos;	// ���W
	float w, h;	// ���A����
	int chipKind;
};
struct Map
{
	MapDateChips mapDateChips[Game::kStageNum][kChipNumY];
};
void InitMap(const Map& map, const MapDate& mapdate);
void DrawMap(const Map& map, const MapDate& mapdate, const Camera& camera);