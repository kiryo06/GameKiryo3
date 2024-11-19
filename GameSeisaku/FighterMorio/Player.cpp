/*
//-----------------------------------------------------------------------------
// 2024 Takeru Yui All Rights Reserved.
//-----------------------------------------------------------------------------
#include <math.h>
#include "DxLib.h"
#include "Screen.h"
#include "Camera.h"
#include "Player.h"
#include "Map.h"

/// <summary>
/// �v���C���[�̏�����
/// </summary>
void InitPlayer(Player& player)
{
	// MEMO: float�덷��floor�Ő؂�̂ĂĂ�֌W��A��������Ȃ��ƃY����̂Œ���
	player.w = 30;
	player.h = 60;

	player.pos = VGet(32.0f + player.h * 0.5f, 100, 0);
	player.dir = VGet(0, 0, 0);
	player.fallSpeed = 0.0f;
	player.isGround = false;
	player.isHitTop = false;
}

/// <summary>
/// �v���C���[�̍X�V
/// </summary>
void UpdatePlayer(Player& player, const Map& map)
{
	// ���͏�Ԃ��X�V
	// �p�b�h�P�ƃL�[�{�[�h������͂𓾂�
	auto input = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// �v���C���[�̈ړ�����
	// ���E�̈ړ��������o��
	player.dir = VGet(0, 0, 0);
	if (input & PAD_INPUT_LEFT)
	{
		player.dir = VAdd(player.dir, VGet(-1, 0, 0));
	}
	if (input & PAD_INPUT_RIGHT)
	{
		player.dir = VAdd(player.dir, VGet(1, 0, 0));
	}

	// ���K��
	if (VSquareSize(player.dir) > 0)
	{
		player.dir = VNorm(player.dir);
	}

	// �ړ��ʂ��o��
	auto velocity = VScale(player.dir, Speed);

	// �������x���X�V
	player.fallSpeed += Gravity;

	// HACK: ��ɐݒ蔻������邱�Ƃ�fallSpeed�C���{�ڒn�t���O�X�V
	CheckIsGround(player, map);
	CheckIsTopHit(player, map);

	// �n�ɑ��������Ă���ꍇ�̂݃W�����v�{�^��(�{�^���P or �y�L�[)������
	if (player.isGround && !player.isHitTop && (input & PAD_INPUT_B))
	{
		player.fallSpeed = -JumpPower;	// �W�����v�{�^�����������瑦���ɏ�����̗͂ɑ���
		player.isGround = false;
	}

	// �������x���ړ��ʂɉ�����
	auto fallVelocity = VGet(0, player.fallSpeed, 0);	// �������x�N�g���ɁBy���W�����ω����Ȃ��̂ōŌ�Ƀx�N�g���ɂ���
	velocity = VAdd(velocity, fallVelocity);

	// �����蔻������āA�ǂɂ߂荞�܂Ȃ��悤��velocity�𑀍삷��
	velocity = CheckPlayerHitWithMap(player, map, velocity);

	// �ړ�
	player.pos = VAdd(player.pos, velocity);
}

/// <summary>
/// �����̃v���C���[�ʒu�ƃ}�b�v�̓����蔻����s���A��������velocity�i�ړ��x�N�g��)��Ԃ�
/// </summary>
VECTOR CheckPlayerHitWithMap(Player& player, const Map& map, const VECTOR& velocity)
{
	// �T�C�Y���ŏ�����0�Ȃ瓮����������return
	if (VSize(velocity) == 0)
	{
		return velocity;
	}

	VECTOR ret = velocity;

	// ������Ȃ��Ȃ�܂ŌJ��Ԃ�
	bool loop = true;
	bool isFirstHit = true;	// ����œ���������
	while (loop)
	{
		loop = false;

		// �����̃v���C���[�̃|�W�V�������܂��o��
		VECTOR futurePos = VAdd(player.pos, ret);

		// �S�}�b�v�`�b�v���J��Ԃ�
		for (int wIndex = 0; wIndex < MapWidth; wIndex++)
		{
			bool isHit = false;
			for (int hIndex = 0; hIndex < MapHeight; hIndex++)
			{
				isHit = IsHitPlayerWithMapChip(player, futurePos, map.mapChips[wIndex][hIndex]);

				// ����ɓ��������Ƃ�
				if (isHit && isFirstHit)
				{
					// ���㓖���蔻��Ń|�W�V������velocity�̕␳������Ƃ��A�����_�ȉ��̌덷���Y�܂��
					// �G��1�h�b�g�����炷�A���w�v�Z�����Ȃ��}�b�V�u�����蔻��ɂ͎ז��Ȃ̂ŏ���Ɋۂ߂Ă��܂��A
					// �ȍ~���߂ē����蔻��
					// pos��Velocity���ۂ߂�
					player.pos.x = floorf(player.pos.x);
					player.pos.y = floorf(player.pos.y);
					ret.x = floorf(ret.x);
					ret.y = floorf(ret.y);
					isFirstHit = false;
					loop = true;	// ���[�v�p��
				}

				// �����������_�Ń}�b�v�`�b�v�̃��[�v����ʂ��邪�A������Ȃ��Ȃ�܂ŌJ��Ԃ����[�v�͌p��
				if (isHit && !isFirstHit)
				{
					// HACK: �������Ă����ꍇ��velocity��1�h�b�g���k�߂Ă����A������Ȃ��Ȃ�܂ŌJ��Ԃ�
					// ���̂܂܏k�߂Ă��܂��ƁA�΂߂̃x�N�g���̂Ƃ��i�Ⴆ�ΕǂɌ������ăW�����v�����Ƃ��j�ɃW�����v�̐������k�߂Ă��܂�
					// �����h�����߂ɁA
					// ����������k�߂Ă������ƂŁA�����������
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
					break;
				}
			}
			if (isHit)
			{
				break;
			}
		}
	}

	// MEMO: �������ňړ����ă}�b�v�˂��������ꍇ�͍l�����Ă��Ȃ�
	// MEMO: �������ׂ������ł����炷���߂ɁA�}�b�v�`�b�v�ƃv���C���[�̋����ł�������v�Z���O����Ƃ��A�F�X����̂̓A��

	return ret;
}

/// <summary>
/// �}�b�v�`�b�v�Ɩ����̃v���C���[�|�W�V�����̓����蔻��
/// </summary>
bool IsHitPlayerWithMapChip(const Player& player, const VECTOR& futurePos, const MapChip& mapChip)
{
	// �}�b�v�`�b�v��������Ȃ���ނȂ瑁��return
	if (mapChip.chipKind == 0)
	{
		return false;
	}

	// �������Ă��邩�ǂ������ׂ�
	float futurePosLeft = futurePos.x - player.w * 0.5f;
	float futurePosRight = futurePos.x + player.w * 0.5f;
	float futurePosTop = futurePos.y - player.h * 0.5f;
	float futurePosBottom = futurePos.y + player.h * 0.5f;
	float targetLeft = mapChip.pos.x - mapChip.w * 0.5f;
	float targetRight = mapChip.pos.x + mapChip.w * 0.5f;
	float targetTop = mapChip.pos.y - mapChip.h * 0.5f;
	float targetBottom = mapChip.pos.y + mapChip.h * 0.5f;
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

/// <summary>
/// ���オ�Ԃ����Ă��邩����
/// </summary>
void CheckIsTopHit(Player& player, const Map& map)
{
	// 1�h�b�g��ɂ��炵�ē�����Γ��オ�Ԃ����Ă��� �i�����_�����j
	auto checkPos = VGet(player.pos.x, floorf(player.pos.y) - 1.0f, player.pos.z);
	// �S�}�b�v�`�b�v���J��Ԃ�
	bool isHit = false;
	for (int wIndex = 0; wIndex < MapWidth; wIndex++)
	{
		for (int hIndex = 0; hIndex < MapHeight; hIndex++)
		{
			isHit = IsHitPlayerWithMapChip(player, checkPos, map.mapChips[wIndex][hIndex]);
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
		if (!player.isHitTop)
		{
			player.isHitTop = true;
			player.fallSpeed = 0.0f;

			// ��X�̎G�v�Z�ɋ����̂ŁAy���W�̏����_��������΂�
			player.pos.y = floorf(player.pos.y);
		}
	}
	else
	{
		player.isHitTop = false;
	}
}

/// <summary>
/// �n�ʂɐڒn���Ă��邩����
/// </summary>
void CheckIsGround(Player& player, const Map& map)
{
	// 1�h�b�g���ɂ��炵�ē�����Βn�ʂɑ����Ԃ����Ă��� �i�����_�����j
	auto checkPos = VGet(player.pos.x, floorf(player.pos.y) + 1.0f, player.pos.z);
	// �S�}�b�v�`�b�v���J��Ԃ�
	bool isHit = false;
	for (int wIndex = 0; wIndex < MapWidth; wIndex++)
	{
		for (int hIndex = 0; hIndex < MapHeight; hIndex++)
		{
			isHit = IsHitPlayerWithMapChip(player, checkPos, map.mapChips[wIndex][hIndex]);
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
		player.isGround = true;
		// fallSpeed���[���ɂ��A�}���ȗ�����h��
		player.fallSpeed = 0.0f;

		// ��X�̎G�v�Z�ɋ����̂ŁAy���W�̏����_��������΂�
		player.pos.y = floorf(player.pos.y);	// ���傤�ǒn�ʂɕt���ʒu��
	}
	else
	{
		player.isGround = false;
	}
}

/// <summary>
/// �v���C���[�`��
/// </summary>
void DrawPlayer(const Player& player, const Camera& camera)
{
	// �L�����N�^�̕`��
	auto leftTop = static_cast<int>(player.pos.x - player.w * 0.5f);
	auto leftBottom = static_cast<int>(player.pos.y - player.h * 0.5f);
	auto rightTop = static_cast<int>(player.pos.x + player.w * 0.5f);
	auto rightBottom = static_cast<int>(player.pos.y + player.h * 0.5f);
	DrawBox(
		leftTop + static_cast<int>(camera.drawOffset.x),
		leftBottom + static_cast<int>(camera.drawOffset.y),
		rightTop + static_cast<int>(camera.drawOffset.x),
		rightBottom + static_cast<int>(camera.drawOffset.y),
		GetColor(255, 0, 0), TRUE);
}
*/