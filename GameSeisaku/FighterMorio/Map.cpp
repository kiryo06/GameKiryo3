/*
#include "Map.h"
// �v���C���[
//#include "Player.h"
//#include "PlayerLight.h"

// �M�~�b�N
//#include "Wall.h"
//#include "InColorFloor.h"
//#include "OutColorFloor.h"
//#include "DirWall.h"
//#include "GoalPoint.h"

// �G�t�F�N�g
//#include "EfectColor.h"

// �T�E���h
//#include "Sound.h"

// BG
//#include "GameBg.h"

// �t�@�C���f�[�^
//#include "FileQuickTime.h"

// �v���C���[�J���[��Bg
//#include "pColorBg.h"

//#include <cassert>

Map::Map()
{
	for (int i = 0; i < kChipNumY; i++)
	{
		for (int j = 0; j < kChipNumX; j++)
		{
			chipData[i][j] = 0;
		}
	}

//	std::vector <std::shared_ptr<BaseMapChip>> temp;
//	temp.push_back(std::make_shared<BaseMapChip>(0));
//	m_chipData.push_back(temp);

}

Map::~Map()
{
}

void Map::Init(int mapNum)
{
}

void Map::Update()
{
}

void Map::Draw()
{
}
*/


#include "DxLib.h"
#include "Screen.h"
#include "Map.h"
#include "Camera.h"

/// <summary>
/// �}�b�v�f�[�^ TODO: �O���f�[�^��
/// </summary>
const int MapData[MapHeight][MapWidth] =
{
	0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
	1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
	1,0,0,1,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
	1,0,0,1,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,1,0,1,
	1,0,0,1,1, 1,1,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,1,0,1,

	1,0,0,0,0, 0,0,0,1,1, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,1,0,1,
	1,0,0,0,0, 0,0,0,0,0, 0,0,1,1,0, 0,0,1,1,0, 0,0,1,1,0, 0,0,1,0,1,
	1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,1,0,1,
	1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
	1,0,0,0,0, 0,0,1,1,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 1,0,0,0,1,

	1,0,0,0,0, 1,1,1,1,1, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1, 1,0,0,0,1,
	1,0,0,0,0, 1,1,1,1,1, 0,0,0,0,0, 0,0,0,1,1, 0,0,0,1,1, 1,0,0,0,1,
	1,0,0,0,0, 0,0,0,0,0, 0,0,0,1,1, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
	1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
	1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1,
};

/// <summary>
/// �}�b�v��񏉊���
/// </summary>
void InitMap(Map& map)
{
	// �}�b�v�f�[�^�ǂݍ���
	for (int wIndex = 0; wIndex < MapWidth; wIndex++)
	{
		for (int hIndex = 0; hIndex < MapHeight; hIndex++)
		{
			MapChip& mapChip = map.mapChips[wIndex][hIndex];
			mapChip.w = MapChipSize;
			mapChip.h = MapChipSize;
			mapChip.chipKind = MapData[hIndex][wIndex];

			// �|�W�V�����̊��^�񒆂�
			mapChip.pos = VGet(wIndex * mapChip.w + mapChip.w * 0.5f, hIndex * mapChip.h + mapChip.w * 0.5f, 0);
		}
	}
}

/// <summary>
/// �}�b�v�`��
/// </summary>
void DrawMap(const Map& map, const Camera& camera)
{
	for (int wIndex = 0; wIndex < MapWidth; wIndex++)
	{
		for (int hIndex = 0; hIndex < MapHeight; hIndex++)
		{
			// �P�͓����蔻��`�b�v��\���Ă���̂łP�̂Ƃ��낾���`��
			const MapChip& mapChip = map.mapChips[wIndex][hIndex];
			if (mapChip.chipKind == 1)
			{
				auto leftTop = static_cast<int>(mapChip.pos.x - mapChip.w * 0.5f);
				auto leftBottom = static_cast<int>(mapChip.pos.y - mapChip.h * 0.5f);
				auto rightTop = static_cast<int>(mapChip.pos.x + mapChip.w * 0.5f);
				auto rightBottom = static_cast<int>(mapChip.pos.y + mapChip.h * 0.5f);
				DrawBox(
					leftTop + static_cast<int>(camera.drawOffset.x),
					leftBottom + static_cast<int>(camera.drawOffset.y),
					rightTop + static_cast<int>(camera.drawOffset.x),
					rightBottom + static_cast<int>(camera.drawOffset.y),
					GetColor(255, 255, 255), TRUE);
			}
		}
	}
}