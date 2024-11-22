#pragma once
#include "MapData.h"
class Camera;
class Map
{
public:
	/// <summary>
	/// 1-1_�}�b�v��񏉊���
	/// </summary>
	/// <param name="mapdata"></param>
	void Init(int mapNumber);
//	void Update_1();
//	void Update_2();
	void Draw(int mapNumber, Camera* camera);
private:
	// ���^�`�b�v�f�[�^
	MapDataFile::ChipData PrototypeChipData[MapDataFile::kChipNumY][MapDataFile::kChipNumX] = {};
	// 1-1���^�`�b�v�f�[�^
	MapDataFile::ChipData PrototypeChipDataOne[MapDataFile::kOneChipNumY][MapDataFile::kOneChipNumX] = {};
};