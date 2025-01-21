#include "Camera.h"
#include <cmath>
#include "DxLib.h"
#include "Player.h"
#include "Screen.h"
#include "game.h"
namespace
{
	// �J�����͈�
	const float CameraScopeRangeRight = 250.0f;
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

	/*if (t < 0.0f) return a;
	if (t > 1.0f) return b;
	VECTOR temp;
	temp = VSub(b, a);
	temp.x *= t;
	temp.y *= t;
	return temp;*/

}

Camera::Camera():
	pos(VGet(0, 0, 0)),
	drawOffset(VGet(0, 0, 0))
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
	// �v���C���[�̈ʒu���A�J�����̒���������ȏ㗣�ꂽ��
	// �J�����́u�ڕW�v�|�W�V���������͈͓̔��ɗ��߂�
	VECTOR aimCameraPos = pos;
	VECTOR playerPos = player->GetPlayerPos();
	if (playerPos.x > pos.x + (CameraScopeRangeRight * 1.0f))
	{
		aimCameraPos.x = playerPos.x - (CameraScopeRangeRight * 1.0f);
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

	// �ڕW�|�W�V�����ɁALerp���g���ăJ�����|�W�V�������߂Â���
	pos = VLerp(pos, aimCameraPos, CameraLerpRate);

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

	// Draw���ɑ����Ă���camera.pos.x/y�͔��]������
	drawOffset.x = pos.x * -1;
	drawOffset.y = pos.y * -1;

	// ���̎��A��ʂ̒����Ƀv���C���[������悤�ɂ���
	drawOffset.x = drawOffset.x + (ScreenWidth * 0.01f);
	drawOffset.y = drawOffset.y + (ScreenHeight * 0.55f);
}
