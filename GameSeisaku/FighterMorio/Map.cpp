#include "Map.h"
#include "DxLib.h"
#include "Camera.h"
#include <cassert>

Map::Map():
	m_kChipWidth(MapDataFile::kChipWidth),
	m_kChipHeight(MapDataFile::kChipHeight),
	m_kChipNumY(MapDataFile::kChipNumY),
	m_kChipNumX(MapDataFile::kChipNumX),
	m_k1ChipNumY(MapDataFile::k1ChipNumY),
	m_k1ChipNumX(MapDataFile::k1ChipNumX),
	m_k2ChipNumY(MapDataFile::k2ChipNumY),
	m_k2ChipNumX(MapDataFile::k2ChipNumX),
	m_WallGraph(0),
	m_HardBlockGraph(0),
	m_SkyBackGroundGraph(0)
{
}

Map::~Map()
{
	DeleteGraph(m_WallGraph);
	DeleteGraph(m_HardBlockGraph);
	DeleteGraph(m_SkyBackGroundGraph);
}

void Map::Init(int mapNumber)
{
	switch (mapNumber)
	{
	case 0:
		// �f�o�b�N
		m_WallGraph = LoadGraph("data/image/WorldMap.png");				// 16 * 16
		m_HardBlockGraph = LoadGraph("data/image/HardBlock.png");		// 32 * 32
		m_SkyBackGroundGraph = LoadGraph("data/image/BackGround.png");	// 960 * 1920
		for (int hChip = 0; hChip < m_kChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < m_kChipNumX; wChip++)
			{
				PrototypeChipData[hChip][wChip].chipKind = MapDataFile::mapChipData[hChip][wChip];
				PrototypeChipData[hChip][wChip].w = m_kChipWidth;
				PrototypeChipData[hChip][wChip].h = m_kChipHeight;
				PrototypeChipData[hChip][wChip].pos.x = wChip * m_kChipWidth;
				PrototypeChipData[hChip][wChip].pos.y = hChip * m_kChipHeight;
			}
		}
		break;
	case 1:
		// 1-1
		m_WallGraph = LoadGraph("data/image/WorldMap.png");				// 16 * 16
		m_HardBlockGraph = LoadGraph("data/image/HardBlock.png");		// 32 * 32
		m_SkyBackGroundGraph = LoadGraph("data/image/BackGround.png");	// 960 * 1920
		for (int hChip = 0; hChip < m_k1ChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < m_k1ChipNumX; wChip++)
			{
				PrototypeChipData1[hChip][wChip].chipKind = MapDataFile::mapChipData1[hChip][wChip];
				PrototypeChipData1[hChip][wChip].w = m_kChipWidth;
				PrototypeChipData1[hChip][wChip].h = m_kChipHeight;
				PrototypeChipData1[hChip][wChip].pos.x = wChip * m_kChipWidth;
				PrototypeChipData1[hChip][wChip].pos.y = hChip * m_kChipHeight;
			}
		}
		break;
	case 2:
		// 1-2
		m_WallGraph = LoadGraph("data/image/WorldMap.png");				// 16 * 16
		m_HardBlockGraph = LoadGraph("data/image/HardBlock.png");		// 32 * 32
		m_SkyBackGroundGraph = LoadGraph("data/image/BackGround.png");	// 960 * 1920
		for (int hChip = 0; hChip < m_k2ChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < m_k2ChipNumX; wChip++)
			{
				PrototypeChipData2[hChip][wChip].chipKind = MapDataFile::mapChipData2[hChip][wChip];
				PrototypeChipData2[hChip][wChip].w = m_kChipWidth;
				PrototypeChipData2[hChip][wChip].h = m_kChipHeight;
				PrototypeChipData2[hChip][wChip].pos.x = wChip * m_kChipWidth;
				PrototypeChipData2[hChip][wChip].pos.y = hChip * m_kChipHeight;
			}
		}
		break;
	}
}


void Map::Draw(int mapNumber, Camera* camera)
{
	switch (mapNumber)
	{
	case 0:
		// �f�o�b�N
		for (int hChip = 0; hChip < MapDataFile::kChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < MapDataFile::kChipNumX; wChip++)
			{
				auto leftTop = static_cast<int>(PrototypeChipData[hChip][wChip].pos.x - PrototypeChipData[hChip][wChip].w * 0.5f);			// ����̍��W��n��
				auto leftBottom = static_cast<int>(PrototypeChipData[hChip][wChip].pos.y - PrototypeChipData[hChip][wChip].h * 0.5f);		// �����̍��W��n��
				auto rightTop = static_cast<int>(PrototypeChipData[hChip][wChip].pos.x + PrototypeChipData[hChip][wChip].w * 0.5f);			// �E��̍��W��n��
				auto rightBottom = static_cast<int>(PrototypeChipData[hChip][wChip].pos.y + PrototypeChipData[hChip][wChip].h * 0.5f);		// �E���̍��W��n��


				leftTop += static_cast<int>(camera->GetCameraDrawOffset().x);			// ����̍��W�̕␳
				leftBottom += static_cast<int>(camera->GetCameraDrawOffset().y);		// �����̍��W�̕␳
				rightTop += static_cast<int>(camera->GetCameraDrawOffset().x);			// �E��̍��W�̕␳
				rightBottom += static_cast<int>(camera->GetCameraDrawOffset().y);		// �E���̍��W�̕␳

				// �P�͓����蔻��`�b�v��\���Ă���̂łP�̂Ƃ��낾���`��
				if (PrototypeChipData[hChip][wChip].chipKind == 1)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, 0xaaaaaa, TRUE);
				}
			}
		}
		break;
	case 1:
		// 1-1

		/*DrawRectExtendGraph(0, 0, Game::kScreenWidth, Game::kScreenHeight,0, 0, 3840, 1920, m_SkyBackGroundGraph, TRUE);*/

		for (int hChip = 0; hChip < MapDataFile::k1ChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < MapDataFile::k1ChipNumX; wChip++)
			{
				auto leftTop = static_cast<int>(PrototypeChipData1[hChip][wChip].pos.x - PrototypeChipData1[hChip][wChip].w * 0.5f);			// ����̍��W��n��
				auto leftBottom = static_cast<int>(PrototypeChipData1[hChip][wChip].pos.y - PrototypeChipData1[hChip][wChip].h * 0.5f);			// �����̍��W��n��
				auto rightTop = static_cast<int>(PrototypeChipData1[hChip][wChip].pos.x + PrototypeChipData1[hChip][wChip].w * 0.5f);			// �E��̍��W��n��
				auto rightBottom = static_cast<int>(PrototypeChipData1[hChip][wChip].pos.y + PrototypeChipData1[hChip][wChip].h * 0.5f);		// �E���̍��W��n��

				leftTop += static_cast<int>(camera->GetCameraDrawOffset().x);			// ����̍��W�̕␳
				leftBottom += static_cast<int>(camera->GetCameraDrawOffset().y);		// �����̍��W�̕␳
				rightTop += static_cast<int>(camera->GetCameraDrawOffset().x);			// �E��̍��W�̕␳
				rightBottom += static_cast<int>(camera->GetCameraDrawOffset().y);		// �E���̍��W�̕␳


				// 0�͓����蔻�肪�Ȃ��̂�0����F�ŕ`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 0)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, 0x87cefa, TRUE);
				}
				// -�P�͓����蔻��`�b�v�A-1��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == -1)
				{
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 112, 1, 16, 16, m_WallGraph, TRUE);
				}
				// �P�͓����蔻��`�b�v�A1��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 1)
				{
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 112, 16, 16, 16, m_WallGraph, TRUE);
				}
				// 2�͓����蔻��`�b�v�A2��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 2)
				{
					DrawRectExtendGraph(leftTop,leftBottom,rightTop,rightBottom,272, 64, 48, 48, m_WallGraph, TRUE);
				}
				// 3�͓����蔻��`�b�v�A3��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 3)
				{
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 272, 144, 16, 16, m_WallGraph, TRUE);
				}
				// 4�͓����蔻��`�b�v�A4��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 4)
				{
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0, 0, 32, 32, m_HardBlockGraph, FALSE);
				}
				// 5�͓����蔻��`�b�v�A5��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 5)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, 0x00aa00, TRUE);
				}
			}
		}
		break;
	case 2:
		// 1-2

		/*DrawRectExtendGraph(0, 0, Game::kScreenWidth, Game::kScreenHeight,0, 0, 3840, 1920, m_SkyBackGroundGraph, TRUE);*/

		for (int hChip = 0; hChip < MapDataFile::k2ChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < MapDataFile::k2ChipNumX; wChip++)
			{
				auto leftTop = static_cast<int>(PrototypeChipData2[hChip][wChip].pos.x - PrototypeChipData2[hChip][wChip].w * 0.5f);			// ����̍��W��n��
				auto leftBottom = static_cast<int>(PrototypeChipData2[hChip][wChip].pos.y - PrototypeChipData2[hChip][wChip].h * 0.5f);			// �����̍��W��n��
				auto rightTop = static_cast<int>(PrototypeChipData2[hChip][wChip].pos.x + PrototypeChipData2[hChip][wChip].w * 0.5f);			// �E��̍��W��n��
				auto rightBottom = static_cast<int>(PrototypeChipData2[hChip][wChip].pos.y + PrototypeChipData2[hChip][wChip].h * 0.5f);		// �E���̍��W��n��

				leftTop += static_cast<int>(camera->GetCameraDrawOffset().x);			// ����̍��W�̕␳
				leftBottom += static_cast<int>(camera->GetCameraDrawOffset().y);		// �����̍��W�̕␳
				rightTop += static_cast<int>(camera->GetCameraDrawOffset().x);			// �E��̍��W�̕␳
				rightBottom += static_cast<int>(camera->GetCameraDrawOffset().y);		// �E���̍��W�̕␳


				// 0�͓����蔻�肪�Ȃ��̂�0����F�ŕ`��
				if (PrototypeChipData2[hChip][wChip].chipKind == 0)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, 0x87cefa, TRUE);
				}
				// -�P�͓����蔻��`�b�v�A-1��`��
				if (PrototypeChipData2[hChip][wChip].chipKind == -1)
				{
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 112, 1, 16, 16, m_WallGraph, TRUE);
				}
				// �P�͓����蔻��`�b�v�A1��`��
				if (PrototypeChipData2[hChip][wChip].chipKind == 1)
				{
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 112, 16, 16, 16, m_WallGraph, TRUE);
				}
				// 2�͓����蔻��`�b�v�A2��`��
				if (PrototypeChipData2[hChip][wChip].chipKind == 2)
				{
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 272, 64, 48, 48, m_WallGraph, TRUE);
				}
				// 3�͓����蔻��`�b�v�A3��`��
				if (PrototypeChipData2[hChip][wChip].chipKind == 3)
				{
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 272, 144, 16, 16, m_WallGraph, TRUE);
				}
				// 4�͓����蔻��`�b�v�A4��`��
				if (PrototypeChipData2[hChip][wChip].chipKind == 4)
				{
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0, 0, 32, 32, m_HardBlockGraph, FALSE);
				}
				// 5�͓����蔻��`�b�v�A5��`��
				if (PrototypeChipData2[hChip][wChip].chipKind == 5)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, 0x00aa00, TRUE);
				}
			}
		}
		break;
	}
}
