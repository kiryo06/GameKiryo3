#pragma once

class MapDate;
//-----------------------------------------//
// �萔
//-----------------------------------------//
const int MapChipSize = 32;                           // ��̃`�b�v�̃T�C�Y
const int MapWidth = 640 / MapChipSize + (10);    // �}�b�v�̉���
const int MapHeight = 480 / MapChipSize;   // �}�b�v�̏c��

/// <summary>
/// �}�b�v�`�b�v�\����
/// </summary>
struct MapChip
{
	VECTOR pos;	// ���W
	float w, h;	// ���A����
	int chipKind;
};
MapDate::kStage
/// <summary>
/// �}�b�v�\����
/// </summary>
struct Map
{
	MapChip mapChips[MapWidth][MapHeight];
};

//-----------------------------------------//s
// �v���g�^�C�v�錾
//-----------------------------------------//
struct Camera;
void InitMap(Map& map);
void DrawMap(const Map& map, const Camera& camera);
