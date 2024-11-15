#include <cmath>
#include "DxLib.h"
#include "Camera.h"
#include "Player.h"
#include "Screen.h"

// �J�����͈�
const float CameraScopeRangeW = 400.0f;
const float CameraScopeRangeH = 300.0f;
const float CameraScopeRangeTop = 200.0f;
const float CameraScopeRangeBottom = 320.0f;
const float CameraLerpRate = 0.1f;

VECTOR VLerp(VECTOR start, VECTOR end, float t)
{
	VECTOR ret;
	ret.x = std::lerp(start.x, end.x, t);
	ret.y = std::lerp(start.y, end.y, t);
	ret.z = std::lerp(start.z, end.z, t);
	return ret;
}

void InitCamera(Camera& camera)
{
	camera.pos = VGet(0, 0, 0);
}

void UpdateCamera(Camera& camera, const Player& player)
{
	// �v���C���[�̈ʒu���A�J�����̒���������ȏ㗣�ꂽ��
	// �J�����́u�ڕW�v�|�W�V���������͈͓̔��ɗ��߂�
	VECTOR aimCameraPos = camera.pos;
	if (player.pos.x > camera.pos.x + (CameraScopeRangeW * 0.5f))
	{
		aimCameraPos.x = player.pos.x - (CameraScopeRangeW * 0.5f);
	}
	else if (player.pos.x < camera.pos.x - (CameraScopeRangeW * 0.5f))
	{
		aimCameraPos.x = player.pos.x + (CameraScopeRangeW * 0.5f);
	}
	if (player.pos.y > camera.pos.y + (CameraScopeRangeH * 0.5f))
	{
		aimCameraPos.y = player.pos.y - (CameraScopeRangeH * 0.5f);
	}
	else if (player.pos.y < camera.pos.y - (CameraScopeRangeH * 0.5f))
	{
		aimCameraPos.y = player.pos.y + (CameraScopeRangeH * 0.5f);
	}

	// �ڕW�|�W�V�����ɁALerp���g���ăJ�����|�W�V�������߂Â���
	camera.pos = VLerp(camera.pos, aimCameraPos, CameraLerpRate);

	// �n�ʂ̈���艺�ɃJ�������ړ����Ȃ��悤�Ɍ�ŌŒ�
	if (camera.pos.y > CameraScopeRangeBottom)
	{
		camera.pos.y = CameraScopeRangeBottom;
	}
	// ����������~�߂�
	if (camera.pos.y < CameraScopeRangeTop)
	{
		camera.pos.y = CameraScopeRangeTop;
	}

	/////////////////////////////////////////////////////////////////////////////
	// ��drawOffset�␳
	// �i�J�����𓮂����Ă��銴�o�ő��̕`�敨�̃|�W�V�������������悤�ɂ���v�Z
	/////////////////////////////////////////////////////////////////////////////
	// ���x�N�g����v�Z���g���āA�u�J�����̃|�W�V�����𓮂����v
	// �Ƃ������o��ۂ������̂ŁADraw���ɑ����Ă���camera.pos��������
	// Draw���ɑ����Ă���camera.pos.x/y�͔��]������
	camera.drawOffset.x = camera.pos.x * -1;
	camera.drawOffset.y = camera.pos.y * -1;

	// ���̎��A��ʂ̒����Ƀv���C���[������悤�ɂ���
	// (camera.pos����ʂ̒����ɂȂ�悤�ɂ���)
	camera.drawOffset.x = camera.drawOffset.x + (ScreenWidth * 0.5f);
	camera.drawOffset.y = camera.drawOffset.y + (ScreenHeight * 0.5f);
}