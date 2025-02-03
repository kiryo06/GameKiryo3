#include "Player.h"
#include <cmath>
#include "DxLib.h"
#include "Map.h"
#include "Camera.h"
#include "Kuribou.h"
#include "SystemEngineer.h"
#include "Pad.h"

namespace
{
	const float Gravity = 0.5f;		// �L�����Ɋ|����d�͉����x
	const float JumpPower = 11.75f;	// �L�����̃W�����v��
	const float Speed = 4.5f;		// �L�����̈ړ��X�s�[�h
	const float RunSpeed = 6.5f;		// �L�����̃_�b�V�����ړ��X�s�[�h
	const int	Width = 32;
}

Player::Player() :
	m_pMap(),
	m_pCamera(),
	//m_pKuribou(new Kuribou),
	m_pSystemEngineer(new SystemEngineer),
	w(32),
	h(32),
	fallSpeed(0.0f),
	pos(VGet(40.0f + h * 0.5f, 992, 0)),
	dir(VGet(0, 0, 0)),
	velocity(VGet(0, 0, 0)),
	isGround(false),
	isHitTop(false),
	playerDeath(0),
	isDeath(false),
	isClear(false),
	mapChip(0),
	_isHit(0),
	m_PlayerGraph(0),
	m_kChipNumY(MapDataFile::kChipNumY),
	m_kChipNumX(MapDataFile::kChipNumX),
	m_k1ChipNumY(MapDataFile::k1ChipNumY),
	m_k1ChipNumX(MapDataFile::k1ChipNumX),
	m_k2ChipNumY(MapDataFile::k2ChipNumY),
	m_k2ChipNumX(MapDataFile::k2ChipNumX)
{
}

Player::~Player()
{
	DeleteGraph(m_PlayerGraph);
	delete m_pSystemManager;
}

void Player::Init(int mapNumber, SystemEngineer* pSE)
{
	m_PlayerGraph = LoadGraph("data/image/player(kari).png");
	mapChip = mapNumber;
	m_pSystemEngineer = pSE;
	if (mapChip == 0)
	{
		for (int hChip = 0; hChip < m_kChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < m_kChipNumX; wChip++)
			{
				PrototypeChipData[hChip][wChip].chipKind = MapDataFile::mapChipData[hChip][wChip];
				PrototypeChipData[hChip][wChip].w = MapDataFile::kChipWidth;
				PrototypeChipData[hChip][wChip].h = MapDataFile::kChipHeight;
				PrototypeChipData[hChip][wChip].pos.x = wChip * MapDataFile::kChipWidth;
				PrototypeChipData[hChip][wChip].pos.y = hChip * MapDataFile::kChipHeight;
			}
		}
	}

	if (mapChip == 1)
	{
		for (int hChip = 0; hChip < m_k1ChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < m_k1ChipNumX; wChip++)
			{
				PrototypeChipData1[hChip][wChip].chipKind = MapDataFile::mapChipData1[hChip][wChip];
				PrototypeChipData1[hChip][wChip].w = MapDataFile::kChipWidth;
				PrototypeChipData1[hChip][wChip].h = MapDataFile::kChipHeight;
				PrototypeChipData1[hChip][wChip].pos.x = wChip * MapDataFile::kChipWidth;
				PrototypeChipData1[hChip][wChip].pos.y = hChip * MapDataFile::kChipHeight;
			}
		}
	}

	if (mapChip == 2)
	{
		for (int hChip = 0; hChip < m_k2ChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < m_k2ChipNumX; wChip++)
			{
				PrototypeChipData2[hChip][wChip].chipKind = MapDataFile::mapChipData2[hChip][wChip];
				PrototypeChipData2[hChip][wChip].w = MapDataFile::kChipWidth;
				PrototypeChipData2[hChip][wChip].h = MapDataFile::kChipHeight;
				PrototypeChipData2[hChip][wChip].pos.x = wChip * MapDataFile::kChipWidth;
				PrototypeChipData2[hChip][wChip].pos.y = hChip * MapDataFile::kChipHeight;
			}
		}
	}
}

void Player::Update(Camera* camera, std::list<Kuribou*>& Kuribou, int mapNumber)
{
	if(isDeath)return;
	// ���͏�Ԃ��X�V
	auto input = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	// �v���C���[�̈ړ�����
	dir = VGet(0, 0, 0);
	if (input & PAD_INPUT_LEFT)
	{
		dir = VAdd(dir, VGet(-1, 0, 0));
	}
	if (input & PAD_INPUT_RIGHT)
	{
		dir = VAdd(dir, VGet(1, 0, 0));
	}

	// ���K��
	if (VSquareSize(dir) > 0)
	{
		dir = VNorm(dir);
	}

	// �����Ă��邩�ǂ���
	if (input & PAD_INPUT_A)
	{
		// �����Ă���ꍇ�ړ��ʂ��o��
		velocity = VScale(dir, RunSpeed);
	}
	else
	{
		// �ʏ펞�ړ��ʂ��o��
		velocity = VScale(dir, Speed);
	}
#ifdef _DEBUG
	if (input & PAD_INPUT_C)
	{
		fallSpeed = -JumpPower + 4;
		isGround = false;
	}
#endif // _DEBUG

	// �������x���X�V
	fallSpeed += Gravity;

	// ��ɐݒ蔻�������
	CheckIsGround(mapNumber);
	CheckIsTopHit(mapNumber);
	// ��ʏ�ɂ���G�̐������J��Ԃ��Ē��ׂ�
	for (auto& item : Kuribou)
	{
		if (!item->IsEnemyDeath())
		{
			if (CheckIsEnemyTopHit(item))
			{
				fallSpeed = -JumpPower + 4;	// �W�����v����
				item->SetEnemyDeath(true);
				m_pSystemEngineer->SetScore(true);
				break;
			}
			else
			{
				if ((ChickIsEnemyLeftHit(item)) || (ChickIsEnemyRightHit(item)))
				{
					playerDeath += 1;
					isDeath = true;
					break;
				}
			}
		}
	}
	// �n�ɑ��������Ă���ꍇ�̂݃W�����v�{�^��������
	if (isGround && !isHitTop && Pad::IsTrigger(input & PAD_INPUT_B))
	{
		fallSpeed = -JumpPower;	// �W�����v�{�^�����������瑦���ɏ�����̗͂ɑ���
		isGround = false;
	}
	// �v���C���[�̎��ʍ���
	if (pos.y > 1500)
	{
		isDeath = true;
		playerDeath += 1;
	}
	//976, 656
	if (pos.x >= 6320)
	{
		isClear = true;
	}

	// �������x���ړ��ʂɉ�����
	auto fallVelocity = VGet(0, fallSpeed, 0);	// �������x�N�g���ɁBy���W�����ω����Ȃ��̂ōŌ�Ƀx�N�g���ɂ���
	velocity = VAdd(velocity, fallVelocity);

	// �����蔻������āA�ǂɂ߂荞�܂Ȃ��悤��velocity�𑀍삷��
	velocity = CheckPlayerHitWithMap(mapNumber);

	// �ړ�
	pos = VAdd(pos, velocity);
}


VECTOR Player::CheckPlayerHitWithMap(int mapNumber)
{
	// ���x���ŏ�����0�Ȃ瓮����������return
	if (VSize(velocity) == 0)
	{
		return velocity;
	}

	VECTOR ret = velocity;

	// ������Ȃ��Ȃ�܂ŌJ��Ԃ�
	bool loop = true;
	bool isFirstHit = true;	// ����œ���������


	if (mapChip == 0)
	{
		while (loop)
		{
			loop = false;

			// �����̃v���C���[�̃|�W�V�������܂��o��
			VECTOR futurePos = VAdd(pos, ret);
			_isHit = 0;

			//�S�}�b�v�`�b�v���J��Ԃ�
			for (int hChip = 0; hChip < m_kChipNumY; hChip++)
			{
				bool isHit = false;
				for (int wChip = 0; wChip < m_kChipNumX; wChip++)
				{
					bool isHit = IsHitPlayerWithMapChip(mapNumber, futurePos, hChip, wChip);

					// ����ɓ��������Ƃ�
					if (isHit && isFirstHit)
					{
						// ���㓖���蔻��Ń|�W�V������velocity�̕␳������Ƃ��A�����_�ȉ��̌덷���Y�܂��
						// �G��1�h�b�g�����炷�A���w�v�Z�����Ȃ��}�b�V�u�����蔻��ɂ͎ז��Ȃ̂ŏ���Ɋۂ߂Ă��܂��A
						// �ȍ~���߂ē����蔻��
						// pos��Velocity���ۂ߂�
						pos.x = floorf(pos.x);
						pos.y = floorf(pos.y);
						ret.x = floorf(ret.x);
						ret.y = floorf(ret.y);
						isFirstHit = false;
						loop = true;	// ���[�v�p��
					}

					// ������Ȃ��Ȃ�܂ŌJ��Ԃ�(���[�v�͌p��)
					if (isHit && !isFirstHit)
					{
						float absX = fabsf(ret.x);	// velocity��x�����̐�Βl
						float absY = fabsf(ret.y);	// velocity��y�����̐�Βl

						// x�������k�ߐ؂��Ă��Ȃ����x�������k�߂�
						bool shrinkX = (absX != 0.0f);	// x�������k�߂邩�ǂ���

						if (shrinkX)
						{
							if (ret.x > 0.0f)
							{
								ret.x -= 1.0f;
							}
							else
							{
								ret.x += 1.0f;
							}

							// �k�ߐ؂��������
							if (fabs(ret.x) < 1.0f)
							{
								ret.x = 0.0f;
							}
							loop = true;
						}
						else
						{
							if (ret.y > 0.0f)
							{
								ret.y -= 1.0f;
							}
							else
							{
								ret.y += 1.0f;
							}

							// �k�ߐ؂��������
							if (fabs(ret.y) < 1.0f)
							{
								_isHit = 3;
								ret.y = 0.0f;
							}
							loop = true;
						}
						// �ǂ�������ߐ؂����Ƃ���loop����
						if (ret.x == 0.0f && ret.y == 0.0f)
						{
							_isHit = 2;
							loop = false;
							break;
						}

						break;
					}
					if (isHit)
					{
						_isHit = 1;//Debug�p
						break;
					}
				}
			}
		}
		return ret;
	}
	if (mapChip == 1)
	{
		while (loop)
		{
			loop = false;

			// �����̃v���C���[�̃|�W�V�������܂��o��
			VECTOR futurePos = VAdd(pos, ret);

			_isHit = 0;

			//�S�}�b�v�`�b�v���J��Ԃ�
			for (int hChip = 0; hChip < m_k1ChipNumY; hChip++)
			{
				bool isHit = false;
				for (int wChip = 0; wChip < m_k1ChipNumX; wChip++)
				{
					bool isHit = IsHitPlayerWithMapChip(mapNumber, futurePos, hChip, wChip);

					// ����ɓ��������Ƃ�
					if (isHit && isFirstHit)
					{
						// ���㓖���蔻��Ń|�W�V������velocity�̕␳������Ƃ��A�����_�ȉ��̌덷���Y�܂��
						// �G��1�h�b�g�����炷�A���w�v�Z�����Ȃ��}�b�V�u�����蔻��ɂ͎ז��Ȃ̂ŏ���Ɋۂ߂Ă��܂��A
						// �ȍ~���߂ē����蔻��
						// pos��Velocity���ۂ߂�
						pos.x = floorf(pos.x);
						pos.y = floorf(pos.y);
						ret.x = floorf(ret.x);
						ret.y = floorf(ret.y);
						isFirstHit = false;
						loop = true;	// ���[�v�p��
					}

					// ������Ȃ��Ȃ�܂ŌJ��Ԃ�(���[�v�͌p��)
					if (isHit && !isFirstHit)
					{
						float absX = fabsf(ret.x);	// velocity��x�����̐�Βl
						float absY = fabsf(ret.y);	// velocity��y�����̐�Βl

						// x�������k�ߐ؂��Ă��Ȃ����x�������k�߂�
						bool shrinkX = (absX != 0.0f);	// x�������k�߂邩�ǂ���

						if (shrinkX)
						{
							if (ret.x > 0.0f)
							{
								ret.x -= 1.0f;
							}
							else
							{
								ret.x += 1.0f;
							}

							// �k�ߐ؂��������
							if (fabs(ret.x) < 1.0f)
							{
								ret.x = 0.0f;
							}
							loop = true;
						}
						else
						{
							if (ret.y > 0.0f)
							{
								ret.y -= 1.0f;
							}
							else
							{
								ret.y += 1.0f;
							}

							// �k�ߐ؂��������
							if (fabs(ret.y) < 1.0f)
							{
								_isHit = 3;
								ret.y = 0.0f;
							}
							loop = true;
						}
						// �ǂ�������ߐ؂����Ƃ���loop����
						if (ret.x == 0.0f && ret.y == 0.0f)
						{
							_isHit = 2;
							loop = false;
							break;
						}

						break;
					}
					if (isHit)
					{
						_isHit = 1;//Debug�p
						break;
					}
				}
			}
		}
		return ret;
	}
	if (mapChip == 2)
	{
		while (loop)
		{
			loop = false;

			// �����̃v���C���[�̃|�W�V�������܂��o��
			VECTOR futurePos = VAdd(pos, ret);

			_isHit = 0;

			//�S�}�b�v�`�b�v���J��Ԃ�
			for (int hChip = 0; hChip < m_k2ChipNumY; hChip++)
			{
				bool isHit = false;
				for (int wChip = 0; wChip < m_k2ChipNumX; wChip++)
				{

					bool isHit = IsHitPlayerWithMapChip(mapNumber, futurePos, hChip, wChip);

					// ����ɓ��������Ƃ�
					if (isHit && isFirstHit)
					{
						// ���㓖���蔻��Ń|�W�V������velocity�̕␳������Ƃ��A�����_�ȉ��̌덷���Y�܂��
						// �G��1�h�b�g�����炷�A���w�v�Z�����Ȃ��}�b�V�u�����蔻��ɂ͎ז��Ȃ̂ŏ���Ɋۂ߂Ă��܂��A
						// �ȍ~���߂ē����蔻��
						// pos��Velocity���ۂ߂�
						pos.x = floorf(pos.x);
						pos.y = floorf(pos.y);
						ret.x = floorf(ret.x);
						ret.y = floorf(ret.y);
						isFirstHit = false;
						loop = true;	// ���[�v�p��
					}

					// ������Ȃ��Ȃ�܂ŌJ��Ԃ�(���[�v�͌p��)
					if (isHit && !isFirstHit)
					{
						float absX = fabsf(ret.x);	// velocity��x�����̐�Βl
						float absY = fabsf(ret.y);	// velocity��y�����̐�Βl

						// x�������k�ߐ؂��Ă��Ȃ����x�������k�߂�
						bool shrinkX = (absX != 0.0f);	// x�������k�߂邩�ǂ���

						if (shrinkX)
						{
							if (ret.x > 0.0f)
							{
								ret.x -= 1.0f;
							}
							else
							{
								ret.x += 1.0f;
							}

							// �k�ߐ؂��������
							if (fabs(ret.x) < 1.0f)
							{
								ret.x = 0.0f;
							}
							loop = true;
						}
						else
						{
							if (ret.y > 0.0f)
							{
								ret.y -= 1.0f;
							}
							else
							{
								ret.y += 1.0f;
							}

							// �k�ߐ؂��������
							if (fabs(ret.y) < 1.0f)
							{
								_isHit = 3;
								ret.y = 0.0f;
							}
							loop = true;
						}
						// �ǂ�������ߐ؂����Ƃ���loop����
						if (ret.x == 0.0f && ret.y == 0.0f)
						{
							_isHit = 2;
							loop = false;
							break;
						}

						break;
					}
					if (isHit)
					{
						_isHit = 1;//Debug�p
						break;
					}
				}
			}
		}
		return ret;
	}
}

bool Player::IsHitPlayerWithMapChip(int mapNumber, const VECTOR& checkPos, int hChip, int wChip)
{
	// �������Ă��邩�ǂ������ׂ�
	float futurePosLeft = checkPos.x - w * 0.5f;
	float futurePosRight = checkPos.x + w * 0.5f;
	float futurePosTop = checkPos.y - h * 0.5f;
	float futurePosBottom = checkPos.y + h * 0.5f;
	if (mapChip == 0)
	{
		// ���f�o�b�N�p
		const auto& chip = PrototypeChipData[hChip][wChip];
		// �}�b�v�`�b�v��������Ȃ���ނȂ瑁��return
		if ((chip.chipKind == 0) ||
			(chip.chipKind >= 9) &&
			(chip.chipKind <= 45))
		{
			return false;
		}
		// �������Ă��邩�ǂ������ׂ�
		float targetLeft = chip.pos.x - chip.w * 0.5f;
		float targetRight = chip.pos.x + chip.w * 0.5f;
		float targetTop = chip.pos.y - chip.h * 0.5f;
		float targetBottom = chip.pos.y + chip.h * 0.5f;
		// ��`���m�̓����蔻��
		if (((targetLeft <= futurePosLeft && futurePosLeft < targetRight) ||
			(targetLeft > futurePosLeft && targetLeft < futurePosRight)) &&
			((targetTop <= futurePosTop && futurePosTop < targetBottom) ||
				(targetTop > futurePosTop && targetTop < futurePosBottom)))
		{
			return true;
		}
		return false;
	}
	if (mapChip == 1)
	{
		// ���f�o�b�N�p
		const auto& chip = PrototypeChipData1[hChip][wChip];
		// �}�b�v�`�b�v��������Ȃ���ނȂ瑁��return
		if ((chip.chipKind == 0) ||
			(chip.chipKind >= 9) &&
			(chip.chipKind <= 45))
		{
			return false;
		}
		// �������Ă��邩�ǂ������ׂ�
		float targetLeft = chip.pos.x - chip.w * 0.5f;
		float targetRight = chip.pos.x + chip.w * 0.5f;
		float targetTop = chip.pos.y - chip.h * 0.5f;
		float targetBottom = chip.pos.y + chip.h * 0.5f;
		// ��`���m�̓����蔻��
		if (((targetLeft <= futurePosLeft && futurePosLeft < targetRight) ||
			(targetLeft > futurePosLeft && targetLeft < futurePosRight)) &&
			((targetTop <= futurePosTop && futurePosTop < targetBottom) ||
				(targetTop > futurePosTop && targetTop < futurePosBottom)))
		{
			return true;
		}
		return false;
	}
	if (mapChip == 2)
	{
		// ���f�o�b�N�p
		const auto& chip = PrototypeChipData2[hChip][wChip];
		// �}�b�v�`�b�v��������Ȃ���ނȂ瑁��return
		if ((chip.chipKind == 0) ||
			(chip.chipKind >= 9) &&
			(chip.chipKind <= 45))
		{
			return false;
		}
		// �������Ă��邩�ǂ������ׂ�
		float targetLeft = chip.pos.x - chip.w * 0.5f;
		float targetRight = chip.pos.x + chip.w * 0.5f;
		float targetTop = chip.pos.y - chip.h * 0.5f;
		float targetBottom = chip.pos.y + chip.h * 0.5f;
		// ��`���m�̓����蔻��
		if (((targetLeft <= futurePosLeft && futurePosLeft < targetRight) ||
			(targetLeft > futurePosLeft && targetLeft < futurePosRight)) &&
			((targetTop <= futurePosTop && futurePosTop < targetBottom) ||
				(targetTop > futurePosTop && targetTop < futurePosBottom)))
		{
			return true;
		}
		return false;
	}
}

bool Player::IsHitPlayerAndEnemy(Kuribou* Kuribou,const VECTOR& checkPos)
{

	// �������Ă��邩�ǂ������ׂ�
	float PosLeft = checkPos.x - w * 0.5f;
	float PosRight = checkPos.x + w * 0.5f;
	float PosTop = checkPos.y - h * 0.5f;
	float PosBottom = checkPos.y + h * 0.5f;

	VECTOR Enemypos;
	int EnemyW;
	int EnemyH;
	Enemypos.x = static_cast<int>(Kuribou->GetKuribouPos().x);
	Enemypos.y = static_cast<int>(Kuribou->GetKuribouPos().y);
	EnemyW = static_cast<float>(Kuribou->GetW());
	EnemyH = static_cast<float>(Kuribou->GetH());
	float KuribouLeft = Enemypos.x - EnemyW * 0.5f;
	float KuribouRight = Enemypos.x + EnemyW * 0.5f;
	float KuribouTop = Enemypos.y - EnemyH * 0.5f;
	float KuribouBottom = Enemypos.y + EnemyH * 0.5f;

	if (((KuribouLeft <= PosLeft && PosLeft < KuribouRight) ||
		(KuribouLeft > PosLeft && KuribouLeft < PosRight)) &&
			(KuribouTop > PosTop && KuribouTop < PosBottom))
	{
		return true;
	}
	return false;
}

bool Player::IsHitPlayerAndEnemySide(Kuribou* Kuribou, const VECTOR& checkPos)
{
	// �������Ă��邩�ǂ������ׂ�
	float PosLeft = checkPos.x - w * 0.5f;
	float PosRight = checkPos.x + w * 0.5f;
	float PosTop = checkPos.y - h * 0.5f;
	float PosBottom = checkPos.y + h * 0.5f;

	VECTOR Enemypos;
	int EnemyW;
	int EnemyH;
	Enemypos.x = static_cast<int>(Kuribou->GetKuribouPos().x);
	Enemypos.y = static_cast<int>(Kuribou->GetKuribouPos().y);
	EnemyW = static_cast<float>(Kuribou->GetW());
	EnemyH = static_cast<float>(Kuribou->GetH());
	float KuribouLeft = Enemypos.x - EnemyW * 0.5f;
	float KuribouRight = Enemypos.x + EnemyW * 0.5f;
	float KuribouTop = Enemypos.y - EnemyH * 0.5f;
	float KuribouBottom = Enemypos.y + EnemyH * 0.5f;

	if (((KuribouLeft > PosLeft && KuribouLeft < PosRight) ||
		(KuribouRight < PosRight && KuribouRight > PosLeft)) &&
		((KuribouTop <= PosTop && PosTop < KuribouBottom) ||
			(KuribouTop > PosTop && KuribouTop < PosBottom)))
	{
		return true;
	}

	return false;
}

void Player::CheckIsTopHit(int mapNumber)
{
	// 1�h�b�g��ɂ��炵�ē�����Γ��オ�Ԃ����Ă��� �i�����_�����j
	VECTOR checkPos = VGet(pos.x, floorf(pos.y) - 1.0f, pos.z);
	// �S�}�b�v�`�b�v���J��Ԃ�
	bool isHit = false;

	if (mapChip == 0)
	{
		for (int hChip = 0; hChip < m_kChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < m_kChipNumX; wChip++)
			{
				isHit = IsHitPlayerWithMapChip(mapNumber, checkPos, hChip, wChip);
				if (isHit)
				{
					break;
				}
			}
			if (isHit)
			{
				break;
			}
		}
		if (isHit)
		{
			// �ȑO�Ԃ����Ă��Ȃ��̂ɂԂ���Ȃ�fallSpeed���[���ɂ��A����������悤��
			if (!isHitTop)
			{
				isHitTop = true;
				fallSpeed = 0.0f;

				// ��X�̎G�v�Z�ɋ����̂ŁAy���W�̏����_��������΂�
				pos.y = floorf(pos.y);
			}
		}
		else
		{
			isHitTop = false;
		}
	}

	if (mapChip == 1)
	{
		for (int hChip = 0; hChip < m_k1ChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < m_k1ChipNumX; wChip++)
			{
				isHit = IsHitPlayerWithMapChip(mapNumber, checkPos, hChip, wChip);
				if (isHit)
				{
					break;
				}
			}
			if (isHit)
			{
				break;
			}
		}
		if (isHit)
		{
			// �ȑO�Ԃ����Ă��Ȃ��̂ɂԂ���Ȃ�fallSpeed���[���ɂ��A����������悤��
			if (!isHitTop)
			{
				isHitTop = true;
				fallSpeed = 0.0f;

				// ��X�̎G�v�Z�ɋ����̂ŁAy���W�̏����_��������΂�
				pos.y = floorf(pos.y);
			}
		}
		else
		{
			isHitTop = false;
		}
	}

	if (mapChip == 2)
	{
		for (int hChip = 0; hChip < m_k2ChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < m_k2ChipNumX; wChip++)
			{
				isHit = IsHitPlayerWithMapChip(mapNumber, checkPos, hChip, wChip);
				if (isHit)
				{
					break;
				}
			}
			if (isHit)
			{
				break;
			}
		}
		if (isHit)
		{
			// �ȑO�Ԃ����Ă��Ȃ��̂ɂԂ���Ȃ�fallSpeed���[���ɂ��A����������悤��
			if (!isHitTop)
			{
				isHitTop = true;
				fallSpeed = 0.0f;

				// ��X�̎G�v�Z�ɋ����̂ŁAy���W�̏����_��������΂�
				pos.y = floorf(pos.y);
			}
		}
		else
		{
			isHitTop = false;
		}
	}
}

void Player::CheckIsGround(int mapNumber)
{
	// 1�h�b�g���ɂ��炵�ē�����Βn�ʂɑ����Ԃ����Ă��� �i�����_�����j
	VECTOR checkPos = VGet(pos.x, floorf(pos.y) + 1.0f, pos.z);
	// �S�}�b�v�`�b�v���J��Ԃ�
	bool isHit = false;

	if (mapChip == 0)
	{
		for (int hChip = 0; hChip < m_kChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < m_kChipNumX; wChip++)
			{
				isHit = IsHitPlayerWithMapChip(mapNumber, checkPos, hChip, wChip);
				if (isHit)
				{
					break;
				}
			}
			if (isHit)
			{
				break;
			}
		}
		if (isHit)
		{
			isGround = true;
			// fallSpeed���[���ɂ��A�}���ȗ�����h��
			fallSpeed = 0.0f;

			// ��X�̎G�v�Z�ɋ����̂ŁAy���W�̏����_��������΂�
			pos.y = floorf(pos.y);	// ���傤�ǒn�ʂɕt���ʒu��
		}
		else
		{
			isGround = false;
		}
	}

	if (mapChip == 1)
	{
		for (int hChip = 0; hChip < m_k1ChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < m_k1ChipNumX; wChip++)
			{
				isHit = IsHitPlayerWithMapChip(mapNumber, checkPos, hChip, wChip);
				if (isHit)
				{
					break;
				}
			}
			if (isHit)
			{
				break;
			}
		}
		if (isHit)
		{
			isGround = true;
			// fallSpeed���[���ɂ��A�}���ȗ�����h��
			fallSpeed = 0.0f;

			// ��X�̎G�v�Z�ɋ����̂ŁAy���W�̏����_��������΂�
			pos.y = floorf(pos.y);	// ���傤�ǒn�ʂɕt���ʒu��
		}
		else
		{
			isGround = false;
		}
	}

	if (mapChip == 2)
	{
		for (int hChip = 0; hChip < m_k2ChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < m_k2ChipNumX; wChip++)
			{
				isHit = IsHitPlayerWithMapChip(mapNumber, checkPos, hChip, wChip);
				if (isHit)
				{
					break;
				}
			}
			if (isHit)
			{
				break;
			}
		}
		if (isHit)
		{
			isGround = true;
			// fallSpeed���[���ɂ��A�}���ȗ�����h��
			fallSpeed = 0.0f;

			// ��X�̎G�v�Z�ɋ����̂ŁAy���W�̏����_��������΂�
			pos.y = floorf(pos.y);	// ���傤�ǒn�ʂɕt���ʒu��
		}
		else
		{
			isGround = false;
		}
	}
}

bool Player::CheckIsEnemyTopHit(Kuribou* Kuribou)
{
	// 1�h�b�g���ɂ��炵�ē�����ΓG�ɑ����Ԃ����Ă��� �i�����_�����j
	VECTOR checkPos = VGet(pos.x, floorf(pos.y) + 1.0f, pos.z);
	// �S�}�b�v�`�b�v���J��Ԃ�
	bool isHit = false;

	
	isHit = IsHitPlayerAndEnemy(Kuribou, checkPos);
	if (isHit)
	{
		// fallSpeed���[���ɂ��A�}���ȗ�����h��
		fallSpeed = 0.0f;

		// ��X�̎G�v�Z�ɋ����̂ŁAy���W�̏����_��������΂�
		pos.y = floorf(pos.y);	// ���傤�ǒn�ʂɕt���ʒu��
		return true;
	}
	else
	{
		return false;
	}
}

bool Player::ChickIsEnemyLeftHit(Kuribou* Kuribou)
{
	// 1�h�b�g�E�ɂ��炵�ē�����ΓG�ɂԂ����Ă���
	VECTOR checkPos = VGet(floorf(pos.x) + 1.0f, pos.y, pos.z);
	// �S�}�b�v�`�b�v���J��Ԃ�
	bool isHit = false;
	isHit = IsHitPlayerAndEnemySide(Kuribou, checkPos);
	if (isHit)
	{
		// ��X�̎G�v�Z�ɋ����̂ŁAy���W�̏����_��������΂�
		pos.x = floorf(pos.x);	// ���傤�ǒn�ʂɕt���ʒu��
		return true;
	}
	else
	{
		return false;
	}
}

bool Player::ChickIsEnemyRightHit(Kuribou* Kuribou)
{
	// 1�h�b�g���ɂ��炵�ē�����ΓG�ɂԂ����Ă���
	VECTOR checkPos = VGet(floorf(pos.x) - 1.0f, pos.y, pos.z);
	// �S�}�b�v�`�b�v���J��Ԃ�
	bool isHit = false;
	isHit = IsHitPlayerAndEnemySide(Kuribou, checkPos);
	if (isHit)
	{
		// ��X�̎G�v�Z�ɋ����̂ŁAy���W�̏����_��������΂�
		pos.x = floorf(pos.x);	// ���傤�ǒn�ʂɕt���ʒu��
		return true;
	}
	else
	{
		return false;
	}
}


void Player::Draw(int mapNumber,Camera* camera)
{
	// �L�����N�^�̕`��
	auto leftTop = static_cast<int>(pos.x - w * 0.5f);
	auto leftBottom = static_cast<int>(pos.y - h * 0.5f);
	auto rightTop = static_cast<int>(pos.x + w * 0.5f);
	auto rightBottom = static_cast<int>(pos.y + h * 0.5f);
	DrawRectExtendGraph(
		leftTop + static_cast<int>(camera->GetCameraDrawOffset().x),
		leftBottom + static_cast<int>(camera->GetCameraDrawOffset().y),
		rightTop + static_cast<int>(camera->GetCameraDrawOffset().x),
		rightBottom + static_cast<int>(camera->GetCameraDrawOffset().y),
		0, 0, 540, 641,
		m_PlayerGraph, TRUE);
	DrawLine(
		6336 + static_cast<int>(camera->GetCameraDrawOffset().x),
		976 + static_cast<int>(camera->GetCameraDrawOffset().y),
		6336 + static_cast<int>(camera->GetCameraDrawOffset().x),
		656 + static_cast<int>(camera->GetCameraDrawOffset().y), 0xff0000); // (50, 50) ���� (200, 200) �܂ŐԂ�����`��
#ifdef _DEBUG
	DrawBox(
		leftTop + static_cast<int>(camera->GetCameraDrawOffset().x),
		leftBottom + static_cast<int>(camera->GetCameraDrawOffset().y),
		rightTop + static_cast<int>(camera->GetCameraDrawOffset().x),
		rightBottom + static_cast<int>(camera->GetCameraDrawOffset().y),
		0xff0000, FALSE);
	DrawBox(
		static_cast<int>(pos.x) + static_cast<int>(camera->GetCameraDrawOffset().x),
		static_cast<int>(pos.y - h * 1) + static_cast<int>(camera->GetCameraDrawOffset().y),
		static_cast<int>(pos.x) + static_cast<int>(camera->GetCameraDrawOffset().x),
		rightBottom + static_cast<int>(camera->GetCameraDrawOffset().y),
		0xff0000, FALSE);
#endif // _DEBUG
}



//x = 6336
//y =976, 656