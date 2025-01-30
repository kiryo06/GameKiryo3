#include "Camera.h"
#include <cmath>
#include "DxLib.h"
#include "Player.h"
#include "Screen.h"
#include "game.h"
namespace
{
	// �J�����͈�
	const float CameraScopeRangeRight = 500.0f;
	const float CameraScopeRangeLeft = -10.0f;
	const float CameraScopeRangeH = 300.0f;
	const float CameraScopeRangeTop = 320.0f;
	const float CameraScopeRangeBottom = 1000.0f;
	const float CameraLerpRate = 0.9f;
}

VECTOR VLerp(VECTOR start, VECTOR end, float t)
{
	VECTOR ret;
	ret.x = std::lerp(start.x, end.x, t);
	ret.y = std::lerp(start.y, end.y, t);
	ret.z = std::lerp(start.z, end.z, t);
	return ret;
}

Camera::Camera():
	pos(VGet(0, 0, 0)),
	drawOffset(VGet(0, 0, 0)),
	isLeftHit(false)
{
}

Camera::~Camera()
{
}

void Camera::Init()
{
}

void Camera::Update(Player* player)
{
	VECTOR aimCameraPos = CalculateAimCameraPos(player->GetPlayerPos());
	// �ڕW�|�W�V�����ɁALerp���g���ăJ�����|�W�V�������߂Â���
	pos = VLerp(pos, aimCameraPos, CameraLerpRate);
	ClampCameraPos();
	UpdateDrawOffset();
}

VECTOR Camera::CalculateAimCameraPos(const VECTOR& playerPos)
{
	// �v���C���[�̈ʒu���A�J�����̒���������ȏ㗣�ꂽ��
	// �J�����́u�ڕW�v�|�W�V���������͈͓̔��ɗ��߂�
	VECTOR aimCameraPos = pos;
	if (playerPos.x > pos.x + (CameraScopeRangeRight * 1.0f))
	{
		aimCameraPos.x = playerPos.x - (CameraScopeRangeRight * 1.0f);
		isLeftHit = true;
	}
	else if (playerPos.x < pos.x - (CameraScopeRangeLeft * 5.0f))
	{
		aimCameraPos.x = playerPos.x + (CameraScopeRangeLeft * 5.0f);
	}
	if (playerPos.y > pos.y + (CameraScopeRangeH * 0.5f))
	{
		aimCameraPos.y = playerPos.y - (CameraScopeRangeH * 0.5f);
	}
	else if (playerPos.y < pos.y - (CameraScopeRangeH * 0.5f))
	{
		aimCameraPos.y = playerPos.y + (CameraScopeRangeH * 0.5f);
	}
	return aimCameraPos;
}

void Camera::ClampCameraPos()
{
	// �n�ʂ̈���艺�ɃJ�������ړ����Ȃ��悤�Ɍ�ŌŒ�
	if (pos.y > CameraScopeRangeBottom)
	{
		pos.y = CameraScopeRangeBottom;
	}
	// ����������~�߂�
	if (pos.y < CameraScopeRangeTop)
	{
		pos.y = CameraScopeRangeTop;
	}
}

void Camera::UpdateDrawOffset()
{
	drawOffset.x = pos.x * -1 + (ScreenWidth * 0.01f);
	drawOffset.y = pos.y * -1 + (ScreenHeight * 0.55f);
}