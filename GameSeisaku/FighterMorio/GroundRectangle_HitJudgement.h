#pragma once
#include "MapData.h"
class Map;
class Camera;
class GroundRectangle_HitJudgement
{
public:
	GroundRectangle_HitJudgement();
	~GroundRectangle_HitJudgement();
	/// <summary>
	/// ��`�̏�����
	/// </summary>
	void Init(int mapNumber);
	/// <summary>
	/// ��`�ƃ}�b�v�̓����蔻��
	/// </summary>
	/// <param name="isHitWithMapY">�����̕ϐ�</param>
	/// <param name="isHitWithMapX">�c���̕ϐ�</param>
	/// <returns></returns>
	bool IsHitBoxWithMapChip(int mapNumber, const VECTOR& checkPos, int hChip, int wChip);
	/// <summary>
	/// ���オ�Ԃ����Ă��邩����
	/// </summary>
	void CheckIsTopHit(int mapNumber);
	/// <summary>
	/// �n�ʂɐڒn���Ă��邩����
	/// </summary>
	void CheckIsGround(int mapNumber);
	/// <summary>
	/// ���̕ǂɐڒn���Ă��邩����
	/// </summary>
	void CheckIsLeft(int mapNumber);
	/// <summary>
	/// �E�̕ǂɐڒn���Ă��邩����
	/// </summary>
	void CheckIsRight(int mapNumber);
	/// <summary>
	/// ��`�`��
	/// </summary>
	void Draw(int mapNumber, Camera* camera);
	VECTOR GetPlayerPos() { return pos; }
	VECTOR GetPlayerDir() { return dir; }
private:
	float w, h;					// ���A����
	float fallSpeed;			// �v���C���[�̗������x�B�W�����v���͔��]����
	float workSpeed;			// �ړ����x
	VECTOR pos;					// ���W ���F���S�@�c�F���S
	VECTOR dir;					// ���W�̈ړ�����
	VECTOR velocity;			// ���x�̌v�Z��
	bool isGround;				// �v���C���[���ڒn����
	bool isHitTop;				// �v���C���[�̓����V��ɓ������Ă��邩
	bool isLeft;				// �G�����ɓ���������
	bool isRight;				// �G���E�ɓ���������
	int mapChip;				// �}�b�v�̔���
	int HitBox;					// �������Ă��邩�ǂ���
	int m_kChipNumY;			// �}�b�v�̑傫�������f�o�b�N
	int m_kChipNumX;			// �}�b�v�̑傫���c���f�o�b�N
	int m_k1ChipNumY;			// �}�b�v�̑傫������1-1
	int m_k1ChipNumX;			// �}�b�v�̑傫���c��1-1
	int m_k2ChipNumY;			// �}�b�v�̑傫������1-2
	int m_k2ChipNumX;			// �}�b�v�̑傫���c��1-2
	Map* m_map;
	Camera* m_camera;
	MapDataFile::ChipData PrototypeChipData0[MapDataFile::kChipNumY][MapDataFile::kChipNumX] = {};			// �f�o�b�N���^�`�b�v�f�[�^
	MapDataFile::ChipData PrototypeChipData1[MapDataFile::k1ChipNumY][MapDataFile::k1ChipNumX] = {};		// 1-1���^�`�b�v�f�[�^
	MapDataFile::ChipData PrototypeChipData2[MapDataFile::k2ChipNumY][MapDataFile::k2ChipNumX] = {};		// 1-2���^�`�b�v�f�[�^
};