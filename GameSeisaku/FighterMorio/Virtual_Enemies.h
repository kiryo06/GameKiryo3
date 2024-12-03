#pragma once
#include "MapData.h"
class Map;
class Camera;
class Virtual_Enemies
{
public:
	Virtual_Enemies();
	~Virtual_Enemies();
	/// <summary>
	/// �G�̏�����
	/// </summary>
	void Init(int mapNumber);
	/// <summary>
	/// �G�̍X�V
	/// </summary>
	void Update(int mapNumber);
	/// <summary>
	/// �����̓G�ʒu�ƃ}�b�v�̓����蔻����s���A��������velocity�i�ړ��x�N�g��)��Ԃ�
	/// </summary>
	VECTOR CheckVirtual_EnemiesHitWithMap(int mapNumber);
	/// <summary>
	/// �G�ƃ}�b�v�̓����蔻��
	/// </summary>
	/// <param name="isHitWithMapY">�����̕ϐ�</param>
	/// <param name="isHitWithMapX">�c���̕ϐ�</param>
	/// <returns></returns>
	bool IsHitVirtual_EnemiesWithMapChip(int mapNumber, const VECTOR& checkPos, int hChip, int wChip);
	/// <summary>
	/// ���オ�Ԃ����Ă��邩����
	/// </summary>
	void CheckIsTopHit(int mapNumber);
	/// <summary>
	/// �n�ʂɐڒn���Ă��邩����
	/// </summary>
	void CheckIsGround(int mapNumber);
	/// <summary>
	/// �G�̕`��
	/// </summary>
	void Draw(Camera* camera);
	VECTOR GetPlayerPos() { return pos; }
	VECTOR GetPlayerDir() { return dir; }
private:
	float w, h;					// ���A����
	float fallSpeed;				// �G�̗������x�B�W�����v���͔��]����
	VECTOR pos;					// ���W ���F���S�@�c�F���S
	VECTOR dir;					// ���W�̈ړ�����
	VECTOR velocity;
	bool isGround;				// �G���ڒn����
	bool isHitTop;				// �G�̓����V��ɓ������Ă��邩
	bool mapChipY;				// �}�b�v�̏c��
	bool mapChipX;				// �}�b�v�̉���
	int _isHit = 0;
	Map* m_map;
	Camera* m_camera;
	int m_mapkChipNumY;
	int m_mapkChipNumX;
	/*int m_mapkChipNumY_0;
	int m_mapkChipNumX_0;
	int m_mapkChipNumY_1;
	int m_mapkChipNumX_1;*/
	// ���^�`�b�v�f�[�^
	MapDataFile::ChipData PrototypeChipData1[MapDataFile::kChipNumY][MapDataFile::kChipNumX] = {};
	// ���^�`�b�v�f�[�^
	MapDataFile::ChipData PrototypeChipData[MapDataFile::k1ChipNumY][MapDataFile::k1ChipNumX] = {};
};
