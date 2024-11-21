#pragma once
#include "MapData.h"
struct Camera;
class Map
{public:
	void Init();
	/// <summary>
	/// 1-1_�}�b�v��񏉊���
	/// </summary>
	/// <param name="mapdata"></param>
	void InitOne();
	/// <summary>
	/// 1-2_�}�b�v��񏉊���
	/// </summary>
	/// <param name="mapdata"></param>
	void InitTwo();
//	void Update_1();
//	void Update_2();
	void Draw(Camera& camera);
	/// <summary>
	/// 1-1_�}�b�v�`��
	/// </summary>
	/// <param name="mapdata"></param>
	void DrawOne(Camera& camera);
	/// <summary>
	/// 1-2_�}�b�v�`��
	/// </summary>
	/// <param name="mapdata"></param>
	void DrawTwo(Camera& camera);
private:
	// ���^�`�b�v�f�[�^
	MapDataFile::ChipData PrototypeChipData[MapDataFile::kChipNumY][MapDataFile::kChipNumX] = {};
	// 1-1���^�`�b�v�f�[�^
	MapDataFile::ChipData PrototypeChipDataOne[MapDataFile::kOneChipNumY][MapDataFile::kOneChipNumX] = {};
};