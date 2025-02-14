#include "ScenePolygon.h"

ScenePolygon::ScenePolygon()
{
}

void ScenePolygon::init()
{
	SetUseZBuffer3D(true);		// Zバッファを使用する
	SetWriteZBuffer3D(true);	// Zバッファへの書き込みを行う

	SetUseBackCulling(true);	// ポリゴンの裏面を表示しない

	// カメラの設定
	
	// カメラの位置と注視点を指定する
	SetCameraPositionAndTarget_UpVecY(VGet(-200,200,720), VGet(0,0,0));

	// カメラの視野角を設定する
	SetupCamera_Perspective(DX_PI_F / 3);	// 60度

	// カメラのnear, farを設定する
	SetCameraNearFar(10.0f, 1800.0f);
}

void ScenePolygon::end()
{
}

SceneBase* ScenePolygon::update()
{
	return this;
}

void ScenePolygon::draw()
{
	// X軸の線	赤
	DrawLine3D(VGet(-100, 0, 0), VGet(100, 0, 0), 0xff0000);
	// Y軸の線	黄
	DrawLine3D(VGet(0, -100, 0), VGet(0, 100, 0), 0xffff00);
	// Z軸の線	緑
	DrawLine3D(VGet(0, 0, -100), VGet(0, 0, 100), 0x00ff00);


	DrawString(0, 0, "ScenePolygon", 0xffffff);
}
