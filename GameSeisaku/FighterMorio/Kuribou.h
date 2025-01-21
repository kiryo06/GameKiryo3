#pragma once
#include "MapData.h"
	class Map;
class Camera;
class Player;
class Kuribou
{
public:
	Kuribou();
	~Kuribou();
	/// <summary>
	/// �G�̏�����
	/// </summary>
	void Init(int mapNumber);
	/// <summary>
	/// �G�̍X�V
	/// </summary>
	void Update(int mapNumber, Player* player);
	/// <summary>
	/// �����̓G�ʒu�ƃ}�b�v�̓����蔻����s���A��������velocity�i�ړ��x�N�g��)��Ԃ�
	/// </summary>
	VECTOR CheckKuribouHitWithMap(int mapNumber);
	/// <summary>
	/// �G�ƃ}�b�v�̓����蔻��
	/// </summary>
	/// <param name="isHitWithMapY">�����̕ϐ�</param>
	/// <param name="isHitWithMapX">�c���̕ϐ�</param>
	/// <returns></returns>
	bool IsHitKuribouWithMapChip(int mapNumber, const VECTOR& checkPos, int hChip, int wChip);
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
	/// �v���C���[�ɂ��U�����󂯂����̏���
	/// </summary>
	void OnDamage();
	/// <summary>
	/// �G�`��
	/// </summary>
	void Draw(Camera* camera);
	VECTOR GetKuribouPos() const { return pos; }
	VECTOR GetKuribouDir() const { return dir; }
	float GetW() const { return w; }
	float GetH() const { return h; }
	void SetDese(bool isdese) { isDese = isdese; }
	bool IsDese()const { return isDese; }
private:
	float w, h;					// ���A����
	float fallSpeed;			// �G�̗������x�B�W�����v���͔��]����
	float workSpeed;			// ���E�ړ����x
	VECTOR pos;					// ���W ���F���S�@�c�F���S
	VECTOR dir;					// ���W�̈ړ�����
	VECTOR velocity;			// ���x�̌v�Z��
	int DamageFlag;				// �_���[�W���󂯂��Ƃ�
	int Life;					// �G��HP
	bool isGround;				// �G�̑����n�ʂɂ��Ă��邩�ǂ���
	bool isHitTop;				// �G�̓����V��ɓ������Ă��邩
	bool isLeft;				// �G�����ɓ���������
	bool isRight;				// �G���E�ɓ���������
	bool isDese;
	int EnemyDese;
	int m_EnemyGraph;			// �N���{�E������
	int mapChip;
	int m_kChipNumY;			// �}�b�v�̑傫�������f�o�b�N
	int m_kChipNumX;			// �}�b�v�̑傫���c���f�o�b�N
	int m_k1ChipNumY;			// �}�b�v�̑傫������1-1
	int m_k1ChipNumX;			// �}�b�v�̑傫���c��1-1
	int m_k2ChipNumY;			// �}�b�v�̑傫������1-2
	int m_k2ChipNumX;			// �}�b�v�̑傫������1-2
	Map* m_pMap;
	Camera* m_pCamera;
	Player* m_pPlayer;
	// ���^�`�b�v�f�[�^1-1�p
	MapDataFile::ChipData PrototypeChipData[MapDataFile::kChipNumY][MapDataFile::kChipNumX] = {};
	// ���^�`�b�v�f�[�^1-2�p
	MapDataFile::ChipData PrototypeChipData1[MapDataFile::k1ChipNumY][MapDataFile::k1ChipNumX] = {};
	// ���^�`�b�v�f�[�^
	MapDataFile::ChipData PrototypeChipData2[MapDataFile::k2ChipNumY][MapDataFile::k2ChipNumX] = {};
};

