#pragma once
#include "MapData.h"
class Camera;
class Map
{
public:
	Map();
	~Map();
	/// <summary>
	/// 1-1_�}�b�v��񏉊���
	/// </summary>
	/// <param name="mapdata"></param>
	void Init(int mapNumber);
//	void Update_1();
//	void Update_2();
	void Draw(int mapNumber, Camera* camera);
private:
	int m_kChipWidth;			// �}�b�v�`�b�v�̑傫������
	int m_kChipHeight;			// �}�b�v�`�b�v�̑傫���c��
	int m_kChipNumY;			// �f�o�b�N�p�}�b�v�`�b�v�A�c���̐�
	int m_kChipNumX;			// �f�o�b�N�p�}�b�v�`�b�v�A�����̐�
	int m_k1ChipNumY;			// 1-1�}�b�v�`�b�v�A�c���̐�
	int m_k1ChipNumX;			// 1-1�}�b�v�`�b�v�A�����̐�
	int m_k2ChipNumY;			// 1-2�}�b�v�`�b�v�A�c���̐�
	int m_k2ChipNumX;			// 1-2�}�b�v�`�b�v�A�����̐�
	int m_WallGraph;			// �\���}�b�v�`�b�v
	int m_HardBlockGraph;		// ���Ȃ��}�b�v�`�b�v�̉摜
	int m_SkyBackGroundGraph;	// ��̔w�i�摜
	int m_dokanGraph;				// �y�ǂ̃O���t�B�b�N
	// ���^�`�b�v�f�o�b�N�p�f�[�^
	MapDataFile::ChipData PrototypeChipData[MapDataFile::kChipNumY][MapDataFile::kChipNumX] = {};
	// ���^�`�b�v1-1�f�[�^
	MapDataFile::ChipData PrototypeChipData1[MapDataFile::k1ChipNumY][MapDataFile::k1ChipNumX] = {};
	// ���^�`�b�v1-2�f�[�^
	MapDataFile::ChipData PrototypeChipData2[MapDataFile::k2ChipNumY][MapDataFile::k2ChipNumX] = {};
};