#pragma once
#include <memory>
#include "Rect.h"
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
	/// �}�b�v�`�b�v�Ɩ����̃v���C���[�|�W�V�����̓����蔻��
	/// </summary>
	bool IsHitPlayerWithMapChip();
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
private:
	const float Gravity = 0.3f;		// �L�����Ɋ|����d�͉����x
	const float JumpPower = 9.0f;	// �L�����̃W�����v��
	const float Speed = 5.0f;		// �L�����̈ړ��X�s�[�h
	VECTOR pos;					// ���W ���F���S�@�c�F���S
	VECTOR dir;					// ���W ()
	float w, h;					// ���A����
	float fallSpeed;				// �v���C���[�̗������x�B�W�����v���͔��]����
	bool isGround;				// �v���C���[���ڒn����
	bool isHitTop;				// �v���C���[�̓����V��ɓ������Ă��邩
	Map* m_map;
	Camera* m_camera;
};

const float Gravity = 0.3f;                         // �L�����Ɋ|����d�͉����x
const float JumpPower = 9.0f;                         // �L�����̃W�����v��
const float Speed = 5.0f;                         // �L�����̈ړ��X�s�[�h

struct Player
{
	VECTOR	pos;		// ���W HACK: �v���C���[�̍��W�̒��S�́A���F���S�@�c�F���S�B�`���v�Z��ς�����S���ς��̂Œ���
	VECTOR	dir;		// ���W
	float	w, h;		// ���A����
	float	fallSpeed;	// �v���C���[�̗������x�B�W�����v���͔��]����
	bool	isGround;	// �v���C���[���ڒn����
	bool	isHitTop;	// �v���C���[�̓����V��ɓ������Ă��邩
};
struct Map;
struct MapChip;
struct Camera;
void InitPlayer(Player& player);
void UpdatePlayer(Player& player, const Map& map);
VECTOR CheckPlayerHitWithMap(Player& player, const Map& map, const VECTOR& velocity);
bool IsHitPlayerWithMapChip(const Player& player, const VECTOR& futurePos, const MapChip& mapChip);
void CheckIsTopHit(Player& player, const Map& map);
void CheckIsGround(Player& player, const Map& map);
void DrawPlayer(const Player& player, const Camera& camera);