#pragma once
#include "MapData.h"
class Map;
class Camera;
class BaseEnemy;
class Player
{
public:
	Player();
	~Player();
	/// <summary>
	/// �v���C���[�̏�����
	/// </summary>
	void Init(int mapNumber);
	/// <summary>
	/// �v���C���[�̍X�V
	/// </summary>
	void Update(int mapNumber);
	/// <summary>
	/// �����̃v���C���[�ʒu�ƃ}�b�v�̓����蔻����s���A��������velocity�i�ړ��x�N�g��)��Ԃ�
	/// </summary>
	VECTOR CheckPlayerHitWithMap(int mapNumber);
	/// <summary>
	/// �v���C���[�ƃ}�b�v�̓����蔻��
	/// </summary>
	/// <param name="isHitWithMapY">�����̕ϐ�</param>
	/// <param name="isHitWithMapX">�c���̕ϐ�</param>
	/// <returns></returns>
	bool IsHitPlayerWithMapChip(int mapNumber, const VECTOR& checkPos, int hChip, int wChip);
	/// <summary>
	/// �v���C���[�ƓG�̓����蔻��
	/// </summary>
	bool IsHitPlayerAndEnemy(const VECTOR& checkPos);
	/// <summary>
	/// ���オ�Ԃ����Ă��邩����
	/// </summary>
	void CheckIsTopHit(int mapNumber);
	/// <summary>
	/// �n�ʂɐڒn���Ă��邩����
	/// </summary>
	void CheckIsGround(int mapNumber);
	void CheckIsEnemyTop();
	/// <summary>
	/// �v���C���[�`��
	/// </summary>
	void Draw(int mapNumber, Camera* camera);
	VECTOR GetPlayerPos() const { return pos; }
	VECTOR GetPlayerDir() const { return dir; }
private:
	Map* m_pMap;
	Camera* m_pCamera;
	BaseEnemy* m_pBaseEnemy;
	float w, h;					// ���A����
	float fallSpeed;			// �v���C���[�̗������x�B�W�����v���͔��]����
	VECTOR pos;					// ���W ���F���S�@�c�F���S
	VECTOR dir;					// ���W�̈ړ�����
	VECTOR velocity;
	bool isGround;				// �v���C���[���ڒn����
	bool isHitTop;				// �v���C���[�̓����V��ɓ������Ă��邩
	bool isHitEnemy;
	int isEnemyHitDese;
	int mapChip;
	int _isHit;
	int m_PlayerGraph;
	int m_kChipNumY;
	int m_kChipNumX;
	int m_k1ChipNumY;
	int m_k1ChipNumX;
	int m_k2ChipNumY;
	int m_k2ChipNumX;
	// ���^�`�b�v�f�[�^
	MapDataFile::ChipData PrototypeChipData[MapDataFile::kChipNumY][MapDataFile::kChipNumX] = {};
	// ���^�`�b�v�f�[�^
	MapDataFile::ChipData PrototypeChipData1[MapDataFile::k1ChipNumY][MapDataFile::k1ChipNumX] = {};
	// ���^�`�b�v�f�[�^
	MapDataFile::ChipData PrototypeChipData2[MapDataFile::k2ChipNumY][MapDataFile::k2ChipNumX] = {};
};
