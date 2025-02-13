#include "DxLib.h"
#include "game.h"
#include "SceneTest.h"


namespace
{

}

void SceneTest::init()
{
	// カメラの初期化を行う
	// 600*600のグリッドが画面中央あたりに来るように設定
	// カメラ(視点)の位置
	m_cameraPos.x = 0.0f;
	m_cameraPos.y = 200.0f;
	m_cameraPos.z = 720.0f;

	// カメラがどこを向いているか(注視点)
	m_cameraTarget.x = 0.0f;
	m_cameraTarget.y = 200.0f;
	m_cameraTarget.z = 0.0f;

	// カメラの位置と注視点を指定する
	SetCameraPositionAndTarget_UpVecY(m_cameraPos, m_cameraTarget);
}

void SceneTest::end()
{

}

SceneBase* SceneTest::update()
{

	return this;
}

void SceneTest::draw()
{
	// VECTOR構造体
	// 3D座標を表現するのに必要なx,y,zの3つをメンバーとして持つ構造体
	VECTOR start;	// 始点
	VECTOR end;		// 終点

	start.x = -300.0f;
	start.y = 0.0f;
	start.z = 0.0f;

	end.x = 300.0f;
	end.y = 0.0f;
	end.z = 0.0f;
	// 横方向のグリッドをfor文を使って描画する
	// 始点終点のXY座標は変わらない
	// Zのみfor文を使って変化させる
	for (int z = -300; z <= 300; z += 100)
	{
		start.z = z;
		end.z = z;
		DrawLine3D(start, end, 0xff0000);
	}

	// 奥行グリッドを同様に引く
	start.x = 0.0f;
	start.y = 0.0f;
	start.z = -300.0f;

	end.x = 0.0f;
	end.y = 0.0f;
	end.z = 300.0f;

	for (int x = -300; x <= 300; x += 100)
	{
		start.x = x;
		end.x = x;
		DrawLine3D(start, end, 0xffff00);
	}

	DrawString(  0,   0, "3Dの勉強", 0xffffff);	// X,Y座標でどこに表示しているか
//	DrawString(128,   0, "3Dの勉強", 0xffffff);
//	DrawString(  0, 128, "3Dの勉強", 0xffffff);
}

