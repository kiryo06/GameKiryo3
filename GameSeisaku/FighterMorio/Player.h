#pragma once
#include "MapData.h"
#include <list>

class Map;
class Camera;
class Kuribou;
class SystemEngineer;
class Player
{
public:
	Player();
	~Player();
	/// <summary>
	/// �v���C���[�̏�����
	/// </summary>
	/// <param name="mapNumber">�}�b�v�ԍ�</param>
	void Init(int mapNumber, SystemEngineer* pSE);
	/// <summary>
	/// �v���C���[�̍X�V
	/// </summary>
	/// <param name="Kuribou">�G�L�����N�^�[�̃��X�g</param>
	/// <param name="mapNumber">�}�b�v�ԍ�</param>
	void Update(Camera* camera, std::list<Kuribou*>& Kuribou, int mapNumber);
	/// <summary>
	/// ���݂̃v���C���[�ʒu�ƃ}�b�v�̏Փ˔�����s���A�C�����ꂽvelocity�i�ړ��x�N�g���j��Ԃ�
	/// </summary>
	/// <param name="mapNumber">�}�b�v�ԍ�</param>
	/// <returns>�C�����ꂽ�ړ��x�N�g��</returns>
	VECTOR CheckPlayerHitWithMap(int mapNumber);
	/// <summary>
	/// �v���C���[�ƃ}�b�v�̏Փ˔���
	/// </summary>
	/// <param name="mapNumber">�}�b�v�ԍ�</param>
	/// <param name="checkPos">�`�F�b�N����ʒu</param>
	/// <param name="hChip">�}�b�v�`�b�v�̍���</param>
	/// <param name="wChip">�}�b�v�`�b�v�̕�</param>
	/// <returns>�Փ˂��Ă��邩�ǂ���</returns>
	bool IsHitPlayerWithMapChip(int mapNumber, const VECTOR& checkPos, int hChip, int wChip);
	/// <summary>
	/// �v���C���[�ƓG�̏Փ˔���
	/// </summary>
	/// <param name="Kuribou">�G�L�����N�^�[</param>
	/// <param name="checkPos">�`�F�b�N����ʒu</param>
	/// <returns>�Փ˂��Ă��邩�ǂ���</returns>
	bool IsHitPlayerAndEnemy(Kuribou* Kuribou, const VECTOR& checkPos);
	/// <summary>
	/// �v���C���[�ƓG�̑��ʏՓ˔���
	/// </summary>
	/// <param name="Kuribou">�G�L�����N�^�[</param>
	/// <param name="checkPos">�`�F�b�N����ʒu</param>
	/// <returns>���ʏՓ˂��Ă��邩�ǂ���</returns>
	bool IsHitPlayerAndEnemySide(Kuribou* Kuribou, const VECTOR& checkPos);
	/// <summary>
	/// ����ɏ�Q�������邩�m�F
	/// </summary>
	/// <param name="mapNumber">�}�b�v�ԍ�</param>
	void CheckIsTopHit(int mapNumber);
	/// <summary>
	/// �n�ʂɑ������Ă��邩�m�F
	/// </summary>
	/// <param name="mapNumber">�}�b�v�ԍ�</param>
	void CheckIsGround(int mapNumber);
	/// <summary>
	/// �G�̍����ɏՓ˂��Ă��邩�m�F
	/// </summary>
	/// <param name="Kuribou">�G�L�����N�^�[</param>
	bool CheckIsEnemyTopHit(Kuribou* Kuribou);
	/// <summary>
	/// �G�̉E���ɏՓ˂��Ă��邩�m�F
	/// </summary>
	/// <param name="Kuribou">�G�L�����N�^�[</param>
	bool ChickIsEnemyLeftHit(Kuribou* Kuribou);
	/// <summary>
	/// �v���C���[�`��
	/// </summary>
	/// <param name="mapNumber">�}�b�v�ԍ�</param>
	/// <param name="camera">�J�����I�u�W�F�N�g</param>
	bool ChickIsEnemyRightHit(Kuribou* Kuribou);
	/// <summary>
	/// �v���C���[�`��
	/// </summary>
	/// <param name="mapNumber">�}�b�v�ԍ�</param>
	/// <param name="camera">�J�����I�u�W�F�N�g</param>
	void Draw(int mapNumber, Camera* camera);
	//  bool IsHitMapChipKind(auto chip, const VECTOR& checkPos);
	/// <summary>
	/// �v���C���[�̈ʒu���擾
	/// </summary>
	/// <returns>�v���C���[�̈ʒu</returns>
	VECTOR GetPlayerPos() const { return pos; }
	/// <summary>
	/// �v���C���[�̕������擾
	/// </summary>
	/// <returns>�v���C���[�̕���</returns>
	VECTOR GetPlayerDir() const { return dir; }
	/// <summary>
	/// �v���C���[���G�ɏՓ˂������ǂ�����ݒ�
	/// </summary>
	/// <param name="isdeath">�Փ˂������ǂ����̃t���O</param>
	/// <returns>�ݒ肳�ꂽ�t���O</returns>
	int GetPlayerDeath() const { return playerDeath; }
	bool GetDeath() const { return isDeath; }
	bool GetClear() const { return isClear; }
private:
	Map* m_pMap;
	Camera* m_pCamera;
	SystemEngineer* m_pSystemEngineer;
	float w, h;					// �v���C���[�̕��ƍ���
	float fallSpeed;			// �������x
	VECTOR pos;                 // �v���C���[�̈ʒu
	VECTOR dir;					// �����x�N�g��
	VECTOR velocity;            // �ړ��x�N�g��
	bool isGround;              // �n�ʂɑ������Ă��邩�ǂ���
	bool isHitTop;              // ����ɏ�Q�������邩�ǂ���
	int playerDeath;			// �v���C���[�����񂾉�
	bool isDeath;				// �v���C���[�����񂾂��ǂ���
	bool isClear;				// �v���C���[���N���A�������ǂ���
	bool GameoverJump;
	int m_FrameCounter;
	/*bool m_;*/
	int mapChip;                // �}�b�v�`�b�v
	int _isHit;                 // �Փ˃t���O
	int m_PlayerGraph;			// �v���C���[�O���t�B�b�N
	int m_Graph_;
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
