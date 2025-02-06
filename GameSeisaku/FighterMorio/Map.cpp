#include "Map.h"
#include "DxLib.h"
#include "Camera.h"
#include <cassert>

#define BACKCOLOR 0x87cefa

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
	m_SkyBackGroundGraph(0),
	m_dokanGraph(0),
	m_WorldGraph(0),
	m_CastleGraph(0)
{
}

Map::~Map()
{
	DeleteGraph(m_WallGraph);
	DeleteGraph(m_HardBlockGraph);
	DeleteGraph(m_SkyBackGroundGraph);
	DeleteGraph(m_dokanGraph);
	DeleteGraph(m_WorldGraph);
	DeleteGraph(m_CastleGraph);
}

void Map::Init(int mapNumber)
{
	m_WallGraph = LoadGraph("data/image/WorldMap.png");				// 16 * 16
	m_HardBlockGraph = LoadGraph("data/image/HardBlock.png");		// 32 * 32
	m_SkyBackGroundGraph = LoadGraph("data/image/BackGround.png");	// 960 * 1920
	m_dokanGraph = LoadGraph("data/image/dokan.png");
	m_WorldGraph = LoadGraph("data/image/OverWorld.png");
	m_CastleGraph = LoadGraph("data/image/Castle.png");
	switch (mapNumber)
	{
	case 0:
		// �f�o�b�N
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

				// 0�͓����蔻�肪�Ȃ��̂�0����F�ŕ`��
				if (PrototypeChipData[hChip][wChip].chipKind == 0)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, 0x222222, TRUE);
				}
				// �P�͓����蔻��`�b�v�A1��`��
				if (PrototypeChipData[hChip][wChip].chipKind == 1)
				{
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 112, 16, 16, 16, m_WallGraph, TRUE);
				}
				// 2�͓����蔻��`�b�v�A2��`��
				if (PrototypeChipData[hChip][wChip].chipKind == 2)
				{
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 272, 64, 48, 48, m_WallGraph, TRUE);
				}
				// 3�͓����蔻��`�b�v�A3��`��
				if (PrototypeChipData[hChip][wChip].chipKind == 3)
				{
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 272, 144, 16, 16, m_WallGraph, TRUE);
				}
				// 4�͓����蔻��`�b�v�A4��`��
				if (PrototypeChipData[hChip][wChip].chipKind == 4)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0, 0, 32, 32, m_HardBlockGraph, TRUE);
				}
				// 5�͓����蔻��`�b�v�A5��`��
				if (PrototypeChipData[hChip][wChip].chipKind == 5)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0 + 30, 0, 160 - 30, 160, m_dokanGraph, TRUE);	// +��,-�� �͐؂���ʒu��ς��Ă���
				}
				// 6�͓����蔻��`�b�v�A6��`��
				if (PrototypeChipData[hChip][wChip].chipKind == 6)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 160, 0, 160 - 30, 160, m_dokanGraph, TRUE);	// +��,-�� �͐؂���ʒu��ς��Ă���
				}
				// 7�͓����蔻��`�b�v�A7��`��
				if (PrototypeChipData[hChip][wChip].chipKind == 7)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0 + 30, 160 - 20, 160 - 30, 160, m_dokanGraph, TRUE);	// +��,-�� �͐؂���ʒu��ς��Ă���
				}
				// 8�͓����蔻��`�b�v�A8��`��
				if (PrototypeChipData[hChip][wChip].chipKind == 8)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 160, 160 - 20, 160 - 30, 160, m_dokanGraph, TRUE);	// +��,-�� �͐؂���ʒu��ς��Ă���
				}
				// 9�͓����蔻�肪�Ȃ��`�b�v�A9��`��
				if (PrototypeChipData[hChip][wChip].chipKind == 9)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 48, 96, 16, 16, m_WorldGraph, TRUE);
				}
				// 10�͓����蔻�肪�Ȃ��`�b�v�A10��`��
				if (PrototypeChipData[hChip][wChip].chipKind == 10)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 64, 96, 16, 16, m_WorldGraph, TRUE);
				}
				// 11�͓����蔻�肪�Ȃ��`�b�v�A11��`��
				if (PrototypeChipData[hChip][wChip].chipKind == 11)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 80, 96, 16, 16, m_WorldGraph, TRUE);
				}
				// 12�͓����蔻�肪�Ȃ��`�b�v�A12��`��
				if (PrototypeChipData[hChip][wChip].chipKind == 12)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 96, 96, 16, 16, m_WorldGraph, TRUE);
				}
				// 13�͓����蔻�肪�Ȃ��`�b�v�A13��`��
				if (PrototypeChipData[hChip][wChip].chipKind == 13)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 112, 96, 16, 16, m_WorldGraph, TRUE);
				}
				// 14�͓����蔻�肪�Ȃ��`�b�v�A14��`��
				if (PrototypeChipData[hChip][wChip].chipKind == 14)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 64, 80, 16, 16, m_WorldGraph, TRUE);
				}
				// 15�͓����蔻�肪�Ȃ��`�b�v�A15��`��
				if (PrototypeChipData[hChip][wChip].chipKind == 15)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 80, 80, 16, 16, m_WorldGraph, TRUE);
				}
				// 16�͓����蔻�肪�Ȃ��`�b�v�A16��`��
				if (PrototypeChipData[hChip][wChip].chipKind == 16)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 96, 80, 16, 16, m_WorldGraph, TRUE);
				}
				// 17�͓����蔻�肪�Ȃ��`�b�v�A17��`��
				if (PrototypeChipData[hChip][wChip].chipKind == 17)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 80, 64, 16, 16, m_WorldGraph, TRUE);
				}
				// 18�͓����蔻�肪�Ȃ��`�b�v�A18��`��
				if (PrototypeChipData[hChip][wChip].chipKind == 18)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0, 96, 16, 16, m_WorldGraph, TRUE);
				}
				// 19�͓����蔻�肪�Ȃ��`�b�v�A19��`��
				if (PrototypeChipData[hChip][wChip].chipKind == 19)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 16, 96, 16, 16, m_WorldGraph, TRUE);
				}
				// 20�͓����蔻�肪�Ȃ��`�b�v�A20��`��
				if (PrototypeChipData[hChip][wChip].chipKind == 20)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 32, 96, 16, 16, m_WorldGraph, TRUE);
				}
				// 21�͓����蔻�肪�Ȃ��`�b�v�A21��`��
				if (PrototypeChipData[hChip][wChip].chipKind == 21)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0, 64, 16, 16, m_CastleGraph, TRUE);
				}
				// 21�͓����蔻�肪�Ȃ��`�b�v�A21��`��
				if (PrototypeChipData[hChip][wChip].chipKind == 21)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0, 64, 16, 16, m_CastleGraph, TRUE);
				}
				// 22�͓����蔻�肪�Ȃ��`�b�v�A22��`��
				if (PrototypeChipData[hChip][wChip].chipKind == 22)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 16, 64, 16, 16, m_CastleGraph, TRUE);
				}
				// 23�͓����蔻�肪�Ȃ��`�b�v�A23��`��
				if (PrototypeChipData[hChip][wChip].chipKind == 23)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 32, 64, 16, 16, m_CastleGraph, TRUE);
				}
				// 24�͓����蔻�肪�Ȃ��`�b�v�A24��`��
				if (PrototypeChipData[hChip][wChip].chipKind == 24)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 48, 64, 16, 16, m_CastleGraph, TRUE);
				}
				// 25�͓����蔻�肪�Ȃ��`�b�v�A25��`��
				if (PrototypeChipData[hChip][wChip].chipKind == 25)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 64, 64, 16, 16, m_CastleGraph, TRUE);
				}
				// 26�͓����蔻�肪�Ȃ��`�b�v�A26��`��
				if (PrototypeChipData[hChip][wChip].chipKind == 26)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0, 48, 16, 16, m_CastleGraph, TRUE);
				}
				// 27�͓����蔻�肪�Ȃ��`�b�v�A27��`��
				if (PrototypeChipData[hChip][wChip].chipKind == 27)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 16, 48, 16, 16, m_CastleGraph, TRUE);
				}
				// 28�͓����蔻�肪�Ȃ��`�b�v�A28��`��
				if (PrototypeChipData[hChip][wChip].chipKind == 28)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 32, 48, 16, 16, m_CastleGraph, TRUE);
				}
				// 29�͓����蔻�肪�Ȃ��`�b�v�A29��`��
				if (PrototypeChipData[hChip][wChip].chipKind == 29)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 48, 48, 16, 16, m_CastleGraph, TRUE);
				}
				// 30�͓����蔻�肪�Ȃ��`�b�v�A30��`��
				if (PrototypeChipData[hChip][wChip].chipKind == 30)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 64, 48, 16, 16, m_CastleGraph, TRUE);
				}
				// 31�͓����蔻�肪�Ȃ��`�b�v�A31��`��
				if (PrototypeChipData[hChip][wChip].chipKind == 31)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0, 32, 16, 16, m_CastleGraph, TRUE);
				}
				// 32�͓����蔻�肪�Ȃ��`�b�v�A32��`��
				if (PrototypeChipData[hChip][wChip].chipKind == 32)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 16, 32, 16, 16, m_CastleGraph, TRUE);
				}
				// 33�͓����蔻�肪�Ȃ��`�b�v�A33��`��
				if (PrototypeChipData[hChip][wChip].chipKind == 33)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 32, 32, 16, 16, m_CastleGraph, TRUE);
				}
				// 34�͓����蔻�肪�Ȃ��`�b�v�A34��`��
				if (PrototypeChipData[hChip][wChip].chipKind == 34)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 48, 32, 16, 16, m_CastleGraph, TRUE);
				}
				// 35�͓����蔻�肪�Ȃ��`�b�v�A35��`��
				if (PrototypeChipData[hChip][wChip].chipKind == 35)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 64, 32, 16, 16, m_CastleGraph, TRUE);
				}
				// 36�͓����蔻�肪�Ȃ��`�b�v�A36��`��
				if (PrototypeChipData[hChip][wChip].chipKind == 36)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0, 16, 16, 16, m_CastleGraph, TRUE);
				}
				// 37�͓����蔻�肪�Ȃ��`�b�v�A37��`��
				if (PrototypeChipData[hChip][wChip].chipKind == 37)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 16, 16, 16, 16, m_CastleGraph, TRUE);
				}
				// 38�͓����蔻�肪�Ȃ��`�b�v�A38��`��
				if (PrototypeChipData[hChip][wChip].chipKind == 38)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 32, 16, 16, 16, m_CastleGraph, TRUE);
				}
				// 39�͓����蔻�肪�Ȃ��`�b�v�A39��`��
				if (PrototypeChipData[hChip][wChip].chipKind == 39)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 48, 16, 16, 16, m_CastleGraph, TRUE);
				}
				// 40�͓����蔻�肪�Ȃ��`�b�v�A40��`��
				if (PrototypeChipData[hChip][wChip].chipKind == 40)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 64, 16, 16, 16, m_CastleGraph, TRUE);
				}
				// 41�͓����蔻�肪�Ȃ��`�b�v�A41��`��
				if (PrototypeChipData[hChip][wChip].chipKind == 41)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0, 0, 16, 16, m_CastleGraph, TRUE);
				}
				// 42�͓����蔻�肪�Ȃ��`�b�v�A42��`��
				if (PrototypeChipData[hChip][wChip].chipKind == 42)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 16, 0, 16, 16, m_CastleGraph, TRUE);
				}
				// 43�͓����蔻�肪�Ȃ��`�b�v�A43��`��
				if (PrototypeChipData[hChip][wChip].chipKind == 43)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 32, 0, 16, 16, m_CastleGraph, TRUE);
				}
				// 44�͓����蔻�肪�Ȃ��`�b�v�A44��`��
				if (PrototypeChipData[hChip][wChip].chipKind == 44)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 48, 0, 16, 16, m_CastleGraph, TRUE);
				}
				// 45�͓����蔻�肪�Ȃ��`�b�v�A45��`��
				if (PrototypeChipData[hChip][wChip].chipKind == 45)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 64, 0, 16, 16, m_CastleGraph, TRUE);
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
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
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
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0, 0, 32, 32, m_HardBlockGraph, TRUE);
				}
				// 5�͓����蔻��`�b�v�A5��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 5)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0 + 30 , 0, 160 - 30, 160, m_dokanGraph, TRUE);	// +��,-�� �͐؂���ʒu��ς��Ă���
				}
				// 6�͓����蔻��`�b�v�A6��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 6)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 160, 0, 160 - 30, 160, m_dokanGraph, TRUE);	// +��,-�� �͐؂���ʒu��ς��Ă���
				}
				// 7�͓����蔻��`�b�v�A7��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 7)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0 + 30 , 160 - 20, 160 - 30, 160, m_dokanGraph, TRUE);	// +��,-�� �͐؂���ʒu��ς��Ă���
				}
				// 8�͓����蔻��`�b�v�A8��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 8)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 160, 160 - 20, 160 - 30, 160, m_dokanGraph, TRUE);	// +��,-�� �͐؂���ʒu��ς��Ă���
				}
				// 9�͓����蔻�肪�Ȃ��`�b�v�A9��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 9)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 48, 96, 16, 16, m_WorldGraph, TRUE);
				}
				// 10�͓����蔻�肪�Ȃ��`�b�v�A10��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 10)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 64, 96, 16, 16, m_WorldGraph, TRUE);
				}
				// 11�͓����蔻�肪�Ȃ��`�b�v�A11��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 11)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 80, 96, 16, 16, m_WorldGraph, TRUE);
				}
				// 12�͓����蔻�肪�Ȃ��`�b�v�A12��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 12)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 96, 96, 16, 16, m_WorldGraph, TRUE);
				}
				// 13�͓����蔻�肪�Ȃ��`�b�v�A13��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 13)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 112, 96, 16, 16, m_WorldGraph, TRUE);
				}
				// 14�͓����蔻�肪�Ȃ��`�b�v�A14��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 14)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 64, 80, 16, 16, m_WorldGraph, TRUE);
				}
				// 15�͓����蔻�肪�Ȃ��`�b�v�A15��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 15)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 80, 80, 16, 16, m_WorldGraph, TRUE);
				}
				// 16�͓����蔻�肪�Ȃ��`�b�v�A16��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 16)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 96, 80, 16, 16, m_WorldGraph, TRUE);
				}
				// 17�͓����蔻�肪�Ȃ��`�b�v�A17��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 17)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 80, 64, 16, 16, m_WorldGraph, TRUE);
				}
				// 18�͓����蔻�肪�Ȃ��`�b�v�A18��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 18)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0, 96, 16, 16, m_WorldGraph, TRUE);
				}
				// 19�͓����蔻�肪�Ȃ��`�b�v�A19��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 19)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 16, 96, 16, 16, m_WorldGraph, TRUE);
				}
				// 20�͓����蔻�肪�Ȃ��`�b�v�A20��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 20)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 32, 96, 16, 16, m_WorldGraph, TRUE);
				}
				// 21�͓����蔻�肪�Ȃ��`�b�v�A21��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 21)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0, 64, 16, 16, m_CastleGraph, TRUE);
				}
				// 21�͓����蔻�肪�Ȃ��`�b�v�A21��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 21)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0, 64, 16, 16, m_CastleGraph, TRUE);
				}
				// 22�͓����蔻�肪�Ȃ��`�b�v�A22��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 22)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 16, 64, 16, 16, m_CastleGraph, TRUE);
				}
				// 23�͓����蔻�肪�Ȃ��`�b�v�A23��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 23)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 32, 64, 16, 16, m_CastleGraph, TRUE);
				}
				// 24�͓����蔻�肪�Ȃ��`�b�v�A24��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 24)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 48, 64, 16, 16, m_CastleGraph, TRUE);
				}
				// 25�͓����蔻�肪�Ȃ��`�b�v�A25��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 25)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 64, 64, 16, 16, m_CastleGraph, TRUE);
				}
				// 26�͓����蔻�肪�Ȃ��`�b�v�A26��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 26)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0, 48, 16, 16, m_CastleGraph, TRUE);
				}
				// 27�͓����蔻�肪�Ȃ��`�b�v�A27��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 27)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 16, 48, 16, 16, m_CastleGraph, TRUE);
				}
				// 28�͓����蔻�肪�Ȃ��`�b�v�A28��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 28)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 32, 48, 16, 16, m_CastleGraph, TRUE);
				}
				// 29�͓����蔻�肪�Ȃ��`�b�v�A29��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 29)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 48, 48, 16, 16, m_CastleGraph, TRUE);
				}
				// 30�͓����蔻�肪�Ȃ��`�b�v�A30��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 30)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 64, 48, 16, 16, m_CastleGraph, TRUE);
				}
				// 31�͓����蔻�肪�Ȃ��`�b�v�A31��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 31)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0, 32, 16, 16, m_CastleGraph, TRUE);
				}
				// 32�͓����蔻�肪�Ȃ��`�b�v�A32��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 32)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom,16, 32, 16, 16, m_CastleGraph, TRUE);
				}
				// 33�͓����蔻�肪�Ȃ��`�b�v�A33��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 33)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom,32, 32, 16, 16, m_CastleGraph, TRUE);
				}
				// 34�͓����蔻�肪�Ȃ��`�b�v�A34��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 34)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom,48, 32, 16, 16, m_CastleGraph, TRUE);
				}
				// 35�͓����蔻�肪�Ȃ��`�b�v�A35��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 35)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom,64, 32, 16, 16, m_CastleGraph, TRUE);
				}
				// 36�͓����蔻�肪�Ȃ��`�b�v�A36��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 36)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0, 16, 16, 16, m_CastleGraph, TRUE);
				}
				// 37�͓����蔻�肪�Ȃ��`�b�v�A37��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 37)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom,16, 16, 16, 16, m_CastleGraph, TRUE);
				}
				// 38�͓����蔻�肪�Ȃ��`�b�v�A38��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 38)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom,32, 16, 16, 16, m_CastleGraph, TRUE);
				}
				// 39�͓����蔻�肪�Ȃ��`�b�v�A39��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 39)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom,48, 16, 16, 16, m_CastleGraph, TRUE);
				}
				// 40�͓����蔻�肪�Ȃ��`�b�v�A40��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 40)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom,64, 16, 16, 16, m_CastleGraph, TRUE);
				}
				// 41�͓����蔻�肪�Ȃ��`�b�v�A41��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 41)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0, 0, 16, 16, m_CastleGraph, TRUE);
				}
				// 42�͓����蔻�肪�Ȃ��`�b�v�A42��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 42)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom,16, 0, 16, 16, m_CastleGraph, TRUE);
				}
				// 43�͓����蔻�肪�Ȃ��`�b�v�A43��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 43)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom,32, 0, 16, 16, m_CastleGraph, TRUE);
				}
				// 44�͓����蔻�肪�Ȃ��`�b�v�A44��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 44)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom,48, 0, 16, 16, m_CastleGraph, TRUE);
				}
				// 45�͓����蔻�肪�Ȃ��`�b�v�A45��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 45)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom,64, 0, 16, 16, m_CastleGraph, TRUE);
				}
				// 46�͓����蔻�肪�Ȃ��`�b�v�A46��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 46)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 80, 32, 16, 16, m_WorldGraph, TRUE);
				}
				// 47�͓����蔻�肪�Ȃ��`�b�v�A47��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 47)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 96, 32, 16, 16, m_WorldGraph, TRUE);
				}
				// 48�͓����蔻�肪�Ȃ��`�b�v�A48��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 48)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 112, 32, 16, 16, m_WorldGraph, TRUE);
				}
				// 49�͓����蔻�肪�Ȃ��`�b�v�A49��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 49)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 80, 48, 16, 16, m_WorldGraph, TRUE);
				}
				// 50�͓����蔻�肪�Ȃ��`�b�v�A50��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 50)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 96, 48, 16, 16, m_WorldGraph, TRUE);
				}
				// 51�͓����蔻�肪�Ȃ��`�b�v�A51��`��
				if (PrototypeChipData1[hChip][wChip].chipKind == 51)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 112, 48, 16, 16, m_WorldGraph, TRUE);
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
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
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
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0, 0, 32, 32, m_HardBlockGraph, TRUE);
				}
				// 5�͓����蔻��`�b�v�A5��`��
				if (PrototypeChipData2[hChip][wChip].chipKind == 5)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0 + 30, 0, 160 - 30, 160, m_dokanGraph, TRUE);	// +��,-�� �͐؂���ʒu��ς��Ă���
				}
				// 6�͓����蔻��`�b�v�A6��`��
				if (PrototypeChipData2[hChip][wChip].chipKind == 6)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 160, 0, 160 - 30, 160, m_dokanGraph, TRUE);	// +��,-�� �͐؂���ʒu��ς��Ă���
				}
				// 7�͓����蔻��`�b�v�A7��`��
				if (PrototypeChipData2[hChip][wChip].chipKind == 7)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0 + 30, 160 - 20, 160 - 30, 160, m_dokanGraph, TRUE);	// +��,-�� �͐؂���ʒu��ς��Ă���
				}
				// 8�͓����蔻��`�b�v�A8��`��
				if (PrototypeChipData2[hChip][wChip].chipKind == 8)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 160, 160 - 20, 160 - 30, 160, m_dokanGraph, TRUE);	// +��,-�� �͐؂���ʒu��ς��Ă���
				}
				// 9�͓����蔻�肪�Ȃ��`�b�v�A9��`��
				if (PrototypeChipData2[hChip][wChip].chipKind == 9)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 48, 96, 16, 16, m_WorldGraph, TRUE);
				}
				// 10�͓����蔻�肪�Ȃ��`�b�v�A10��`��
				if (PrototypeChipData2[hChip][wChip].chipKind == 10)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 64, 96, 16, 16, m_WorldGraph, TRUE);
				}
				// 11�͓����蔻�肪�Ȃ��`�b�v�A11��`��
				if (PrototypeChipData2[hChip][wChip].chipKind == 11)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 80, 96, 16, 16, m_WorldGraph, TRUE);
				}
				// 12�͓����蔻�肪�Ȃ��`�b�v�A12��`��
				if (PrototypeChipData2[hChip][wChip].chipKind == 12)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 96, 96, 16, 16, m_WorldGraph, TRUE);
				}
				// 13�͓����蔻�肪�Ȃ��`�b�v�A13��`��
				if (PrototypeChipData2[hChip][wChip].chipKind == 13)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 112, 96, 16, 16, m_WorldGraph, TRUE);
				}
				// 14�͓����蔻�肪�Ȃ��`�b�v�A14��`��
				if (PrototypeChipData2[hChip][wChip].chipKind == 14)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 64, 80, 16, 16, m_WorldGraph, TRUE);
				}
				// 15�͓����蔻�肪�Ȃ��`�b�v�A15��`��
				if (PrototypeChipData2[hChip][wChip].chipKind == 15)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 80, 80, 16, 16, m_WorldGraph, TRUE);
				}
				// 16�͓����蔻�肪�Ȃ��`�b�v�A16��`��
				if (PrototypeChipData2[hChip][wChip].chipKind == 16)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 96, 80, 16, 16, m_WorldGraph, TRUE);
				}
				// 17�͓����蔻�肪�Ȃ��`�b�v�A17��`��
				if (PrototypeChipData2[hChip][wChip].chipKind == 17)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 80, 64, 16, 16, m_WorldGraph, TRUE);
				}
				// 18�͓����蔻�肪�Ȃ��`�b�v�A18��`��
				if (PrototypeChipData2[hChip][wChip].chipKind == 18)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0, 96, 16, 16, m_WorldGraph, TRUE);
				}
				// 19�͓����蔻�肪�Ȃ��`�b�v�A19��`��
				if (PrototypeChipData2[hChip][wChip].chipKind == 19)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 16, 96, 16, 16, m_WorldGraph, TRUE);
				}
				// 20�͓����蔻�肪�Ȃ��`�b�v�A20��`��
				if (PrototypeChipData2[hChip][wChip].chipKind == 20)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 32, 96, 16, 16, m_WorldGraph, TRUE);
				}
				// 21�͓����蔻�肪�Ȃ��`�b�v�A21��`��
				if (PrototypeChipData2[hChip][wChip].chipKind == 21)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0, 64, 16, 16, m_CastleGraph, TRUE);
				}
				// 21�͓����蔻�肪�Ȃ��`�b�v�A21��`��
				if (PrototypeChipData2[hChip][wChip].chipKind == 21)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0, 64, 16, 16, m_CastleGraph, TRUE);
				}
				// 22�͓����蔻�肪�Ȃ��`�b�v�A22��`��
				if (PrototypeChipData2[hChip][wChip].chipKind == 22)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 16, 64, 16, 16, m_CastleGraph, TRUE);
				}
				// 23�͓����蔻�肪�Ȃ��`�b�v�A23��`��
				if (PrototypeChipData2[hChip][wChip].chipKind == 23)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 32, 64, 16, 16, m_CastleGraph, TRUE);
				}
				// 24�͓����蔻�肪�Ȃ��`�b�v�A24��`��
				if (PrototypeChipData2[hChip][wChip].chipKind == 24)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 48, 64, 16, 16, m_CastleGraph, TRUE);
				}
				// 25�͓����蔻�肪�Ȃ��`�b�v�A25��`��
				if (PrototypeChipData2[hChip][wChip].chipKind == 25)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 64, 64, 16, 16, m_CastleGraph, TRUE);
				}
				// 26�͓����蔻�肪�Ȃ��`�b�v�A26��`��
				if (PrototypeChipData2[hChip][wChip].chipKind == 26)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0, 48, 16, 16, m_CastleGraph, TRUE);
				}
				// 27�͓����蔻�肪�Ȃ��`�b�v�A27��`��
				if (PrototypeChipData2[hChip][wChip].chipKind == 27)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 16, 48, 16, 16, m_CastleGraph, TRUE);
				}
				// 28�͓����蔻�肪�Ȃ��`�b�v�A28��`��
				if (PrototypeChipData2[hChip][wChip].chipKind == 28)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 32, 48, 16, 16, m_CastleGraph, TRUE);
				}
				// 29�͓����蔻�肪�Ȃ��`�b�v�A29��`��
				if (PrototypeChipData2[hChip][wChip].chipKind == 29)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 48, 48, 16, 16, m_CastleGraph, TRUE);
				}
				// 30�͓����蔻�肪�Ȃ��`�b�v�A30��`��
				if (PrototypeChipData2[hChip][wChip].chipKind == 30)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 64, 48, 16, 16, m_CastleGraph, TRUE);
				}
				// 31�͓����蔻�肪�Ȃ��`�b�v�A31��`��
				if (PrototypeChipData2[hChip][wChip].chipKind == 31)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0, 32, 16, 16, m_CastleGraph, TRUE);
				}
				// 32�͓����蔻�肪�Ȃ��`�b�v�A32��`��
				if (PrototypeChipData2[hChip][wChip].chipKind == 32)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 16, 32, 16, 16, m_CastleGraph, TRUE);
				}
				// 33�͓����蔻�肪�Ȃ��`�b�v�A33��`��
				if (PrototypeChipData2[hChip][wChip].chipKind == 33)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 32, 32, 16, 16, m_CastleGraph, TRUE);
				}
				// 34�͓����蔻�肪�Ȃ��`�b�v�A34��`��
				if (PrototypeChipData2[hChip][wChip].chipKind == 34)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 48, 32, 16, 16, m_CastleGraph, TRUE);
				}
				// 35�͓����蔻�肪�Ȃ��`�b�v�A35��`��
				if (PrototypeChipData2[hChip][wChip].chipKind == 35)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 64, 32, 16, 16, m_CastleGraph, TRUE);
				}
				// 36�͓����蔻�肪�Ȃ��`�b�v�A36��`��
				if (PrototypeChipData2[hChip][wChip].chipKind == 36)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0, 16, 16, 16, m_CastleGraph, TRUE);
				}
				// 37�͓����蔻�肪�Ȃ��`�b�v�A37��`��
				if (PrototypeChipData2[hChip][wChip].chipKind == 37)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 16, 16, 16, 16, m_CastleGraph, TRUE);
				}
				// 38�͓����蔻�肪�Ȃ��`�b�v�A38��`��
				if (PrototypeChipData2[hChip][wChip].chipKind == 38)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 32, 16, 16, 16, m_CastleGraph, TRUE);
				}
				// 39�͓����蔻�肪�Ȃ��`�b�v�A39��`��
				if (PrototypeChipData2[hChip][wChip].chipKind == 39)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 48, 16, 16, 16, m_CastleGraph, TRUE);
				}
				// 40�͓����蔻�肪�Ȃ��`�b�v�A40��`��
				if (PrototypeChipData2[hChip][wChip].chipKind == 40)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 64, 16, 16, 16, m_CastleGraph, TRUE);
				}
				// 41�͓����蔻�肪�Ȃ��`�b�v�A41��`��
				if (PrototypeChipData2[hChip][wChip].chipKind == 41)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 0, 0, 16, 16, m_CastleGraph, TRUE);
				}
				// 42�͓����蔻�肪�Ȃ��`�b�v�A42��`��
				if (PrototypeChipData2[hChip][wChip].chipKind == 42)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 16, 0, 16, 16, m_CastleGraph, TRUE);
				}
				// 43�͓����蔻�肪�Ȃ��`�b�v�A43��`��
				if (PrototypeChipData2[hChip][wChip].chipKind == 43)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 32, 0, 16, 16, m_CastleGraph, TRUE);
				}
				// 44�͓����蔻�肪�Ȃ��`�b�v�A44��`��
				if (PrototypeChipData2[hChip][wChip].chipKind == 44)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 48, 0, 16, 16, m_CastleGraph, TRUE);
				}
				// 45�͓����蔻�肪�Ȃ��`�b�v�A45��`��
				if (PrototypeChipData2[hChip][wChip].chipKind == 45)
				{
					DrawBox(leftTop, leftBottom, rightTop, rightBottom, BACKCOLOR, TRUE);
					DrawRectExtendGraph(leftTop, leftBottom, rightTop, rightBottom, 64, 0, 16, 16, m_CastleGraph, TRUE);
				}
			}
		}
		break;
	}
}
