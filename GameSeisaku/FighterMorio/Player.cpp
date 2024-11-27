#include "Player.h"
#include <cmath>
#include "DxLib.h"
#include "Map.h"
#include "Camera.h"
#include "Pad.h"

//#include <memory>
//#include "Rect.h"

namespace
{
	const float Gravity = 0.3f;		// �L�����Ɋ|����d�͉����x
	const float JumpPower = 9.0f;	// �L�����̃W�����v��
	const float Speed = 5.0f;		// �L�����̈ړ��X�s�[�h
}
Player::Player():
	w(30),
	h(60),
	fallSpeed(0.0f),
	pos(VGet(32.0f + h * 0.5f, 100, 0)),
	dir(VGet(0, 0, 0)),
	velocity(VGet(0, 0, 0)),
	ret(VGet(0, 0, 0)),
	futurePos(VGet(0, 0, 0)),
	checkPos(VGet(0, 0, 0)),
	isGround(false),
	isHitTop(false),
	isHit(false),
	isHitWithMapY(0),
	isHitWithMapX(0)
{
}

Player::~Player()
{
}

void Player::Init()
{
	for (int hChip = 0; hChip < MapDataFile::kChipNumY; hChip++)
	{
		for (int wChip = 0; wChip < MapDataFile::kChipNumX; wChip++)
		{
			isHitWithMapY = hChip;
			isHitWithMapX = wChip;
			PrototypeChipData[isHitWithMapY][isHitWithMapX].chipKind = MapDataFile::mapChipData[hChip][wChip];
			PrototypeChipData[isHitWithMapY][isHitWithMapX].w = MapDataFile::kChipWidth;
			PrototypeChipData[isHitWithMapY][isHitWithMapX].h = MapDataFile::kChipHeight;
			PrototypeChipData[isHitWithMapY][isHitWithMapX].pos.x = wChip * MapDataFile::kChipWidth;
			PrototypeChipData[isHitWithMapY][isHitWithMapX].pos.y = hChip * MapDataFile::kChipHeight;
		}
	}
}

void Player::Update()
{
	// ���͏�Ԃ��X�V
	Pad::Update();
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
	CheckIsTopHit();
	CheckIsGround();

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
	velocity = CheckPlayerHitWithMap();

	// �ړ�
	pos = VAdd(pos, velocity);
}

VECTOR Player::CheckPlayerHitWithMap()
{
	// �T�C�Y���ŏ�����0�Ȃ瓮����������return
	if (VSize(velocity) == 0)
	{
		return velocity;
	}

	ret = velocity;

	// ������Ȃ��Ȃ�܂ŌJ��Ԃ�
	bool loop = true;
	bool isFirstHit = true;	// ����œ���������
	while (loop)
	{
		loop = false;

		// �����̃v���C���[�̃|�W�V�������܂��o��
		futurePos = VAdd(pos, ret);

		for (int hChip = 0; hChip < MapDataFile::kChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < MapDataFile::kChipNumX; wChip++)
			{
				isHitWithMapY = hChip;
				isHitWithMapX = wChip;
				isHit = IsHitPlayerWithMapChip(isHitWithMapY, isHitWithMapX);
				// ����ɓ��������Ƃ�
				if (isHit && isFirstHit)
				{
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
						loop = false;
						break;
					}
					loop = true;
					break;
				}
				if (isHit)
				{
					break;
				}
				//// ������Ȃ��Ȃ�܂ŌJ��Ԃ�(���[�v�͌p��)
				//if (isHit && !isFirstHit)
				//{
				//	float absX = fabsf(ret.x);	// velocity��x�����̐�Βl
				//	float absY = fabsf(ret.y);	// velocity��y�����̐�Βl
				//
				//	// x�������k�ߐ؂��Ă��Ȃ����x�������k�߂�
				//	bool shrinkX = (absX != 0.0f);	// x�������k�߂邩�ǂ���
				//
				//	if (shrinkX)
				//	{
				//		if (ret.x > 0.0f)
				//		{
				//			ret.x -= 1.0f;
				//		}
				//		else
				//		{
				//			ret.x += 1.0f;
				//		}
				//
				//		// �k�ߐ؂��������
				//		if (fabs(ret.x) < 1.0f)
				//		{
				//			ret.x = 0.0f;
				//		}
				//		loop = true;
				//	}
				//	else
				//	{
				//		if (ret.y > 0.0f)
				//		{
				//			ret.y -= 1.0f;
				//		}
				//		else
				//		{
				//			ret.y += 1.0f;
				//		}
				//
				//		// �k�ߐ؂��������
				//		if (fabs(ret.y) < 1.0f)
				//		{
				//			ret.y = 0.0f;
				//		}
				//		loop = true;
				//	}
				//	// �ǂ�������ߐ؂����Ƃ���loop����
				//	if (ret.x == 0.0f && ret.y == 0.0f)
				//	{
				//		loop = false;
				//		break;
				//	}
				//
				//	break;
				//}
				//if (isHit)
				//{
				//	break;
				//}
			}
		}
	}

	// MEMO: �������ňړ����ă}�b�v�˂��������ꍇ�͍l�����Ă��Ȃ�
	// MEMO: �������ׂ������ł����炷���߂ɁA�}�b�v�`�b�v�ƃv���C���[�̋����ł�������v�Z���O����Ƃ��A�F�X����̂̓A��

	return ret;
}

bool Player::IsHitPlayerWithMapChip(int isHitWithMapY, int isHitWithMapX)
{
	const auto& chip = PrototypeChipData[isHitWithMapY][isHitWithMapX];
	// �}�b�v�`�b�v��������Ȃ���ނȂ瑁��return
	if (chip.chipKind == 0)
	{
		DrawString(40, 40, "�������Ă��Ȃ�", 0xffffff, true);
		return false;
	}

	auto width = std::abs(futurePos.x - chip.pos.x);
	auto height = std::abs(futurePos.y - chip.pos.y);

	auto checkWidth = w * 0.5f + chip.w * 0.5f;
	auto checkHeight = h * 0.5f + chip.h * 0.5f;


	if (width < checkWidth && height < checkHeight)
	{
		DrawString(40, 40, "�������Ă���", 0xffffff, true);
		return true;
	}
	DrawString(40, 40, "�������Ă��Ȃ�", 0xffffff, true);
	return false;


	//// �������Ă��邩�ǂ������ׂ�
	//float futurePosLeft = futurePos.x - w * 0.5f;
	//float futurePosRight = futurePos.x + w * 0.5f;
	//float futurePosTop = futurePos.y - h * 0.5f;
	//float futurePosBottom = futurePos.y + h * 0.5f;
	//float targetLeft = PrototypeChipData[isHitWithMapY][isHitWithMapX].pos.x - PrototypeChipData[isHitWithMapY][isHitWithMapX].w * 0.5f;
	//float targetRight = PrototypeChipData[isHitWithMapY][isHitWithMapX].pos.x + PrototypeChipData[isHitWithMapY][isHitWithMapX].w * 0.5f;
	//float targetTop = PrototypeChipData[isHitWithMapY][isHitWithMapX].pos.y - PrototypeChipData[isHitWithMapY][isHitWithMapX].h * 0.5f;
	//float targetBottom = PrototypeChipData[isHitWithMapY][isHitWithMapX].pos.y + PrototypeChipData[isHitWithMapY][isHitWithMapX].h * 0.5f;
	//// ��`���m�̓����蔻��
	//if (((targetLeft <= futurePosLeft && futurePosLeft < targetRight) ||
	//	(targetLeft > futurePosLeft && targetLeft < futurePosRight)) &&
	//	((targetTop <= futurePosTop && futurePosTop < targetBottom) ||
	//		(targetTop > futurePosTop && targetTop < futurePosBottom)))
	//{
	//	DrawString(40, 40, "�������Ă���", 0xffffff, true);
	//	return true;
	//}
	//return false;
}

void Player::CheckIsTopHit()
{
	// 1�h�b�g��ɂ��炵�ē�����Γ��オ�Ԃ����Ă��� �i�����_�����j
	checkPos = VGet(pos.x, floorf(pos.y) - 1.0f, pos.z);
	// �S�}�b�v�`�b�v���J��Ԃ�
	bool isHit = false;
	for (int hChip = 0; hChip < MapDataFile::kChipNumY; hChip++)
	{
		for (int wChip = 0; wChip < MapDataFile::kChipNumX; wChip++)
		{
			isHit = IsHitPlayerWithMapChip(isHitWithMapY, isHitWithMapX);
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
}

void Player::CheckIsGround()
{
	// 1�h�b�g���ɂ��炵�ē�����Βn�ʂɑ����Ԃ����Ă��� �i�����_�����j
	checkPos = VGet(pos.x, floorf(pos.y) + 1.0f, pos.z);
	// �S�}�b�v�`�b�v���J��Ԃ�
	bool isHit = false;
	for (int hChip = 0; hChip < MapDataFile::kChipNumY; hChip++)
	{
		for (int wChip = 0; wChip < MapDataFile::kChipNumX; wChip++)
		{
			isHit = IsHitPlayerWithMapChip(isHitWithMapY, isHitWithMapX);
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
}