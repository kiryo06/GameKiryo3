#include <cmath>
#include "DxLib.h"
#include "Camera.h"
//#include "Player.h"
#include "Screen.h"
#define PLAYER 100

// カメラ範囲
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

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::Init()
{
	pos = VGet(0, 0, 0);
}

void Camera::Update()
{
	// プレイヤーの位置が、カメラの中央から一定以上離れたら
	// カメラの「目標」ポジションをその範囲内に留める
	VECTOR aimCameraPos = pos;
	if (/*player.pos.x*/PLAYER > pos.x + (CameraScopeRangeW * 0.5f))
	{
		aimCameraPos.x = /*player.pos.x*/PLAYER - (CameraScopeRangeW * 0.5f);
	}
	else if (/*player.pos.x*/PLAYER < pos.x - (CameraScopeRangeW * 0.5f))
	{
		aimCameraPos.x = /*player.pos.x*/PLAYER + (CameraScopeRangeW * 0.5f);
	}
	if (/*player.pos.y*/PLAYER > pos.y + (CameraScopeRangeH * 0.5f))
	{
		aimCameraPos.y = /*player.pos.y*/PLAYER - (CameraScopeRangeH * 0.5f);
	}
	else if (/*player.pos.y*/PLAYER < pos.y - (CameraScopeRangeH * 0.5f))
	{
		aimCameraPos.y = /*player.pos.y*/PLAYER + (CameraScopeRangeH * 0.5f);
	}

	// 目標ポジションに、Lerpを使ってカメラポジションを近づける
	pos = VLerp(pos, aimCameraPos, CameraLerpRate);

	// 地面の一定より下にカメラが移動しないように後で固定
	if (pos.y > CameraScopeRangeBottom)
	{
		pos.y = CameraScopeRangeBottom;
	}
	// 空も同じく止める
	if (pos.y < CameraScopeRangeTop)
	{
		pos.y = CameraScopeRangeTop;
	}

	// Draw側に足しているcamera.pos.x/yは反転させる
	drawOffset.x = pos.x * -1;
	drawOffset.y = pos.y * -1;

	// その時、画面の中央にプレイヤーが来るようにする
	// (camera.posが画面の中央になるようにする)
	drawOffset.x = drawOffset.x + (ScreenWidth * 0.5f);
	drawOffset.y = drawOffset.y + (ScreenHeight * 0.5f);
}
