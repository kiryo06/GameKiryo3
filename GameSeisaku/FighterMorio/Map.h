#pragma once

class MapDate;
//-----------------------------------------//
// 定数
//-----------------------------------------//
const int MapChipSize = 32;                           // 一つのチップのサイズ
const int MapWidth = 640 / MapChipSize + (10);    // マップの横幅
const int MapHeight = 480 / MapChipSize;   // マップの縦幅

/// <summary>
/// マップチップ構造体
/// </summary>
struct MapChip
{
	VECTOR pos;	// 座標
	float w, h;	// 幅、高さ
	int chipKind;
};
MapDate::kStage
/// <summary>
/// マップ構造体
/// </summary>
struct Map
{
	MapChip mapChips[MapWidth][MapHeight];
};

//-----------------------------------------//s
// プロトタイプ宣言
//-----------------------------------------//
struct Camera;
void InitMap(Map& map);
void DrawMap(const Map& map, const Camera& camera);
