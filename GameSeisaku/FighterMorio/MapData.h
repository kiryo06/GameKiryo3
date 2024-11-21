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
	const int kChipWidth = 32;
	const int kChipHeight = 32;
	// 1-1�}�b�v�̍L��
	const int kMapX = Game::kScreenWidth * 5;
	const int kMapY = Game::kScreenHeight * 1.2f;
	// 1-1�}�b�v�`�b�v��
	const int kChipNumX = kMapX / kChipWidth;
	const int kChipNumY = kMapY / kChipHeight;
	// �ʒu���Ŏg������?
	const int kMapWidth = kChipWidth * kChipNumX;
	const int kMapHeight = kChipHeight * kChipNumY;
	// 1-1�}�b�v�̏��
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


	// �}�b�v�`�b�v�̏��
	const int kOneChipWidth = 32;
	const int kOneChipHeight = 32;
	// 1-1�}�b�v�̍L��
	const int kOneMapX = Game::kScreenWidth * 5;
	const int kOneMapY = Game::kScreenHeight * 1.2;
	// 1-1�}�b�v�`�b�v��
	const int kOneChipNumX = kOneMapX / kOneChipWidth;
	const int kOneChipNumY = kOneMapY / kOneChipHeight;
	// �ʒu���Ŏg������?
	const int kOneMapWidth = kOneChipWidth * kOneChipNumX;
	const int kOneMapHeight = kOneChipHeight * kOneChipNumY;
	// 1-1�}�b�v�̏��
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