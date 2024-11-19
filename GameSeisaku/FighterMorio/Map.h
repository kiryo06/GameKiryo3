#pragma once
#include "MapData.h"
struct Camera;
class Map
{public:
	/// <summary>
	/// �}�b�v��񏉊���
	/// </summary>
	/// <param name="mapdata"></param>
	void Init();
	/// <summary>
	/// 
	/// </summary>
	/// <param name="mapdata"></param>
	void Update();
	/// <summary>
	/// �}�b�v�`��
	/// </summary>
	/// <param name="mapdata"></param>
	void Draw(Camera& camera);
private:
	//int chipDataNUM[MapDataFile::kChipNumY][MapDataFile::kChipNumX] = {};
	// ���^�`�b�v�f�[�^
	MapDataFile::ChipData PrototypeChipData[MapDataFile::kChipNumY][MapDataFile::kChipNumX] = {};
};