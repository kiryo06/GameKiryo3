#include "Player.h"
#include <cmath>
#include "DxLib.h"
#include "Map.h"
#include "Camera.h"

namespace
{
	const float Gravity = 0.3f;		// �L�����Ɋ|����d�͉����x
	const float JumpPower = 9.0f;	// �L�����̃W�����v��
	const float Speed = 5.0f;		// �L�����̈ړ��X�s�[�h
}
Player::Player():
	m_camera(),
	m_map(),
	w(30),
	h(30),
	fallSpeed(0.0f),
	pos(VGet(32.0f + h * 0.5f, -1000, 0)),
	dir(VGet(0, 0, 0)),
	velocity(VGet(0, 0, 0)),
	isGround(false),
	isHitTop(false),
	mapChipY(),
	mapChipX()
{
}

Player::~Player()
{
}

void Player::Init(int mapNumber)
{
	// ���f�o�b�N�p		�}�b�v�f�[�^�̓ǂݍ���
	/*
	for (int hChip = 0; hChip < MapDataFile::kChipNumY; hChip++)
	{
		for (int wChip = 0; wChip < MapDataFile::kChipNumX; wChip++)
		{
			PrototypeChipData[hChip][wChip].chipKind = MapDataFile::mapChipData[hChip][wChip];
			PrototypeChipData[hChip][wChip].w = MapDataFile::kChipWidth;
			PrototypeChipData[hChip][wChip].h = MapDataFile::kChipHeight;
			PrototypeChipData[hChip][wChip].pos.x = wChip * MapDataFile::kChipWidth;
			PrototypeChipData[hChip][wChip].pos.y = hChip * MapDataFile::kChipHeight;
		}
	}//*/
	//*
	switch (mapNumber)
	{
	case 0:
		// �f�o�b�N
		for (int hChip = 0; hChip < MapDataFile::kChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < MapDataFile::kChipNumX; wChip++)
			{
				PrototypeChipData[hChip][wChip].chipKind = MapDataFile::mapChipData[hChip][wChip];
				PrototypeChipData[hChip][wChip].w = MapDataFile::kChipWidth;
				PrototypeChipData[hChip][wChip].h = MapDataFile::kChipHeight;
				PrototypeChipData[hChip][wChip].pos.x = wChip * MapDataFile::kChipWidth;
				PrototypeChipData[hChip][wChip].pos.y = hChip * MapDataFile::kChipHeight;
			}
		}
		break;
	case 1:
		// 1-1
		for (int hChip = 0; hChip < MapDataFile::k1ChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < MapDataFile::k1ChipNumX; wChip++)
			{
				PrototypeChipData1[hChip][wChip].chipKind = MapDataFile::mapChipData1[hChip][wChip];
				PrototypeChipData1[hChip][wChip].w = MapDataFile::kChipWidth;
				PrototypeChipData1[hChip][wChip].h = MapDataFile::kChipHeight;
				PrototypeChipData1[hChip][wChip].pos.x = wChip * MapDataFile::kChipWidth;
				PrototypeChipData1[hChip][wChip].pos.y = hChip * MapDataFile::kChipHeight;
			}
		}
		break;
	}
	//*/
}

void Player::Update(int mapNumber)
{
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

	// �ړ��ʂ��o��
	velocity = VScale(dir, Speed);

	// �������x���X�V
	fallSpeed += Gravity;

	// HACK: ��ɐݒ蔻������邱�Ƃ�fallSpeed�C���{�ڒn�t���O�X�V
	CheckIsGround(mapNumber);
	CheckIsTopHit(mapNumber);

	// �n�ɑ��������Ă���ꍇ�̂݃W�����v�{�^��(�{�^���P or �y�L�[)������
	if (isGround && !isHitTop && input & PAD_INPUT_B)
	{
		fallSpeed = -JumpPower;	// �W�����v�{�^�����������瑦���ɏ�����̗͂ɑ���
		isGround = false;
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

	// ���f�o�b�N�p
	/*
	while (loop)
	{
		loop = false;

		// �����̃v���C���[�̃|�W�V�������܂��o��
		VECTOR futurePos = VAdd(pos, ret);

		_isHit = 0;

		//�S�}�b�v�`�b�v���J��Ԃ�
		for (int hChip = 0; hChip < MapDataFile::kChipNumY; hChip++)
		{
			bool isHit = false;
			for (int wChip = 0; wChip < MapDataFile::kChipNumX; wChip++)
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
							ret.y = 0.0f;
						}
						loop = true;
					}
					// �ǂ�������ߐ؂����Ƃ���loop����
					if (ret.x == 0.0f && ret.y == 0.0f)
					{
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
	//*/
	//*
	switch (mapNumber)
	{
	case 0:
		while (loop)
		{
			loop = false;

			// �����̃v���C���[�̃|�W�V�������܂��o��
			VECTOR futurePos = VAdd(pos, ret);

			_isHit = 0;

			//�S�}�b�v�`�b�v���J��Ԃ�
			for (int hChip = 0; hChip < MapDataFile::kChipNumY; hChip++)
			{
				bool isHit = false;
				for (int wChip = 0; wChip < MapDataFile::kChipNumX; wChip++)
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
								ret.y = 0.0f;
							}
							loop = true;
						}
						// �ǂ�������ߐ؂����Ƃ���loop����
						if (ret.x == 0.0f && ret.y == 0.0f)
						{
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
		break;
	case 1:
		// 1-1
		while (loop)
		{
			loop = false;

			// �����̃v���C���[�̃|�W�V�������܂��o��
			VECTOR futurePos = VAdd(pos, ret);

			_isHit = 0;

			//�S�}�b�v�`�b�v���J��Ԃ�
			for (int hChip = 0; hChip < MapDataFile::k1ChipNumY; hChip++)
			{
				bool isHit = false;
				for (int wChip = 0; wChip < MapDataFile::k1ChipNumX; wChip++)
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
								ret.y = 0.0f;
							}
							loop = true;
						}
						// �ǂ�������ߐ؂����Ƃ���loop����
						if (ret.x == 0.0f && ret.y == 0.0f)
						{
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
		break;
	}
	//*/
}

bool Player::IsHitPlayerWithMapChip(int mapNumber, const VECTOR& checkPos, int hChip, int wChip)
{
	// ���f�o�b�N�p
	/*
	const auto& chip = PrototypeChipData[hChip][wChip];

	// �}�b�v�`�b�v��������Ȃ���ނȂ瑁��return
	if (chip.chipKind == 0)
	{
		return false;
	}

	// �������Ă��邩�ǂ������ׂ�
	float futurePosLeft = checkPos.x - w * 0.5f;
	float futurePosRight = checkPos.x + w * 0.5f;
	float futurePosTop = checkPos.y - h * 0.5f;
	float futurePosBottom = checkPos.y + h * 0.5f;
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
	//*/

	//*
	switch (mapNumber)
	{
	case 0:
		// �f�o�b�N
		const auto & chip = PrototypeChipData[hChip][wChip];

		// �}�b�v�`�b�v��������Ȃ���ނȂ瑁��return
		if (chip.chipKind == 0)
		{
			return false;
		}

		// �������Ă��邩�ǂ������ׂ�
		float futurePosLeft = checkPos.x - w * 0.5f;
		float futurePosRight = checkPos.x + w * 0.5f;
		float futurePosTop = checkPos.y - h * 0.5f;
		float futurePosBottom = checkPos.y + h * 0.5f;
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
		break;
	case 1:
		// 1-1
		const auto & chip = PrototypeChipData1[hChip][wChip];

		// �}�b�v�`�b�v��������Ȃ���ނȂ瑁��return
		if (chip.chipKind == 0)
		{
			return false;
		}

		// �������Ă��邩�ǂ������ׂ�
		float futurePosLeft = checkPos.x - w * 0.5f;
		float futurePosRight = checkPos.x + w * 0.5f;
		float futurePosTop = checkPos.y - h * 0.5f;
		float futurePosBottom = checkPos.y + h * 0.5f;
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
		break;
	}
	//*/
}

void Player::CheckIsTopHit(int mapNumber)
{
	// 1�h�b�g��ɂ��炵�ē�����Γ��オ�Ԃ����Ă��� �i�����_�����j
	VECTOR checkPos = VGet(pos.x, floorf(pos.y) - 1.0f, pos.z);
	// �S�}�b�v�`�b�v���J��Ԃ�
	bool isHit = false;
	// ���f�o�b�N�p
	/*
	for (int hChip = 0; hChip < MapDataFile::kChipNumY; hChip++)
	{
		for (int wChip = 0; wChip < MapDataFile::kChipNumX; wChip++)
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
	//*/
	//*
	switch (mapNumber)
	{
	case 0:
		// �f�o�b�N
		for (int hChip = 0; hChip < MapDataFile::kChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < MapDataFile::kChipNumX; wChip++)
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
		break;
	case 1:
		// 1-1
		for (int hChip = 0; hChip < MapDataFile::k1ChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < MapDataFile::k1ChipNumX; wChip++)
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
		break;
	}
	//*/
}

void Player::CheckIsGround(int mapNumber)
{
	// 1�h�b�g���ɂ��炵�ē�����Βn�ʂɑ����Ԃ����Ă��� �i�����_�����j
	VECTOR checkPos = VGet(pos.x, floorf(pos.y) + 1.0f, pos.z);
	// �S�}�b�v�`�b�v���J��Ԃ�
	bool isHit = false;

	// ���f�o�b�N�p
	/*
	for (int hChip = 0; hChip < MapDataFile::kChipNumY; hChip++)
	{
		for (int wChip = 0; wChip < MapDataFile::kChipNumX; wChip++)
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
	//*/
	//*
	switch (mapNumber)
	{
	case 0:
		// �f�o�b�N
		for (int hChip = 0; hChip < MapDataFile::kChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < MapDataFile::kChipNumX; wChip++)
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
		break;
	case 1:
		// 1-1
		for (int hChip = 0; hChip < MapDataFile::k1ChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < MapDataFile::k1ChipNumX; wChip++)
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
		break;
	}
	//*/
}


void Player::Draw(Camera*camera)
{
	// �L�����N�^�̕`��
	auto leftTop = static_cast<int>(pos.x - w * 0.5f);
	auto leftBottom = static_cast<int>(pos.y - h * 0.5f);
	auto rightTop = static_cast<int>(pos.x + w * 0.5f);
	auto rightBottom = static_cast<int>(pos.y + h * 0.5f);
	DrawBox(
		leftTop + static_cast<int>(camera->GetCameraDrawOffset().x),
		leftBottom + static_cast<int>(camera->GetCameraDrawOffset().y),
		rightTop + static_cast<int>(camera->GetCameraDrawOffset().x),
		rightBottom + static_cast<int>(camera->GetCameraDrawOffset().y),
		GetColor(255, 0, 0), TRUE);

#ifdef _DEBUG
	DrawFormatString(16, 16, 0xffffff, " PlayerPosX : %f", pos.x, true);
	DrawFormatString(16, 32, 0xffffff, " PlayerPosY : %f", pos.y, true);
	DrawFormatString(16, 48, 0xffffff, " CameraPosX : %f", camera->GetCameraDrawOffset().x, true);
	DrawFormatString(16, 64, 0xffffff, " CameraPosY : %f", camera->GetCameraDrawOffset().y, true);
	DrawFormatString(16, 80, 0xffffff, " PlayerIsHit : %d", _isHit, true);
#endif // _DEBUG

}