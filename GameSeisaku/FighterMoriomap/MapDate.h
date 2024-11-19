#pragma once
#include "Game.h"
#include <iostream>

// �}�b�v�`�b�v�̏��
const int kChipWidth = 32;
const int kChipHeight = 32;
//�c���̃`�b�v�̐�
//�X�N���[��������̂ŉ�ʃT�C�Y���L��
const int kChipNumX = 480;
const int kChipNumY = 30;
//�`�b�v�̃T�C�Y�A������}�b�v�̍L�����v�Z
const int kMapWidth = kChipWidth * kChipNumX;
const int kMapHeight = kChipWidth * kChipNumY;

/// <summary>
/// �}�b�v�`�b�v�\����
/// </summary>
struct MapDateChips
{
	VECTOR pos;	// ���W
	float w, h;	// ���A����
	int chipKind;
};
/// <summary>
/// �}�b�v�\����
/// </summary>
struct MapDate
{
	MapDateChips mapDateChips[Game::kStageNum][kChipNumY][kChipNumX];
};
struct Camera;
void InitMapDate(MapDate& mapdate);
void DrawMapDate(const MapDate& map, const Camera& camera);