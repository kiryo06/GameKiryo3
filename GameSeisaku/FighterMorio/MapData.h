#pragma once
#include "Game.h"
#include "DxLib.h"
namespace MapDataFile
{
	struct ChipData
	{
		VECTOR pos;	// ���W
		float w, h;	// ���A����
		int chipKind;
	};
	// �}�b�v�`�b�v�̏��
	const int kChipWidth = 128;
	const int kChipHeight = 64;
	//�c���̃`�b�v�̐�
//�X�N���[��������̂ŉ�ʃT�C�Y���L��
	const int kChipNumX = Game::kScreenWidth / kChipWidth;
	const int kChipNumY = Game::kScreenHeight / kChipHeight;
	//�`�b�v�̃T�C�Y�A������}�b�v�̍L�����v�Z
	const int kMapWidth = kChipWidth * kChipNumX;
	const int kMapHeight = kChipWidth * kChipNumY;

	const int mapChipData[kChipNumY][kChipNumX] =
	{
		{ 2,2,2,2,2,2,2,2,2,2 },
		{ 2,1,2,2,2,2,2,2,2,2 },
		{ 2,2,2,2,2,2,2,2,2,2 },
		{ 2,1,2,2,2,2,2,2,2,2 },
		{ 2,2,2,2,2,2,2,2,2,2 },
		{ 2,1,2,2,2,2,2,2,2,2 },
		{ 2,2,2,2,2,2,2,2,2,2 },
		{ 2,1,2,2,2,2,2,2,2,2 },
		{ 2,2,2,2,2,2,2,2,2,2 },
		{ 2,1,2,2,2,2,2,2,2,2 }
	};
}