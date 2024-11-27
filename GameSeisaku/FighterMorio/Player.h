#pragma once
#include "MapData.h"
class Map;
class Camera;
class Player
{
public:
	Player();
	~Player();
	/// <summary>
	/// �v���C���[�̏�����
	/// </summary>
	void Init();
	/// <summary>
	/// �v���C���[�̍X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �����̃v���C���[�ʒu�ƃ}�b�v�̓����蔻����s���A��������velocity�i�ړ��x�N�g��)��Ԃ�
	/// </summary>
	VECTOR CheckPlayerHitWithMap();
	/// <summary>
	/// �v���C���[�ƃ}�b�v�̓����蔻��
	/// </summary>
	/// <param name="isHitWithMapY">�����̕ϐ�</param>
	/// <param name="isHitWithMapX">�c���̕ϐ�</param>
	/// <returns></returns>
	bool IsHitPlayerWithMapChip(int isHitWithMapY, int isHitWithMapX);
	/// <summary>
	/// ���オ�Ԃ����Ă��邩����
	/// </summary>
	void CheckIsTopHit();
	/// <summary>
	/// �n�ʂɐڒn���Ă��邩����
	/// </summary>
	void CheckIsGround();
	/// <summary>
	/// �v���C���[�`��
	/// </summary>
	void Draw(Camera* camera);
	VECTOR GetPlayerPos() { return pos; }
	VECTOR GetPlayerDir() { return dir; }
private:
	float w, h;					// ���A����
	float fallSpeed;				// �v���C���[�̗������x�B�W�����v���͔��]����
	int isHitWithMapY, isHitWithMapX;
	VECTOR pos;					// ���W ���F���S�@�c�F���S
	VECTOR dir;					// ���W�̈ړ�����
	VECTOR velocity;
	VECTOR ret;
	VECTOR futurePos;
	VECTOR checkPos;
	bool isGround;				// �v���C���[���ڒn����
	bool isHitTop;				// �v���C���[�̓����V��ɓ������Ă��邩
	bool isHit;
	Map* m_map;
	Camera* m_camera;

	// ���^�`�b�v�f�[�^
	MapDataFile::ChipData PrototypeChipData[MapDataFile::kChipNumY][MapDataFile::kChipNumX] = {};
};
