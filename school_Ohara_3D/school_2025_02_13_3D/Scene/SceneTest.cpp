#include "DxLib.h"
#include "game.h"
#include "SceneTest.h"
#include <cmath>
#include "Pad.h"


namespace
{
}

SceneTest::SceneTest():
	m_viewAngle(0.0f),
	m_cameraMoveAngle(0.0f)
{
}

void SceneTest::init()
{
	SetUseZBuffer3D(true);		// Zバッファを使用する
	SetWriteZBuffer3D(true);	// Zバッファへの書き込みを行う
	SetUseBackCulling(true);	// ポリゴンの裏面を表示しない

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



	// カメラの視野角を設定する
	m_viewAngle = DX_PI_F / 3.0f;	// 60度
	SetupCamera_Perspective(m_viewAngle);



	// カメラのnear, farを設定する
	// 画面に表示される距離の範囲を設定する
	// カメラからnear以上離れていて、farより近くにあるものが
	// ゲーム内に表示される
	// farはあまり大きすぎる数字を設定しないように気を付ける(表示バグにつながる)
	SetCameraNearFar(10.0f, 1800.0f);
}

void SceneTest::end()
{

}

SceneBase* SceneTest::update()
{
	// カメラの位置を回転させる
	m_cameraMoveAngle += 0.02f;
	m_cameraPos.x = cosf(m_cameraMoveAngle) * 720.0f;
	m_cameraPos.z = sinf(m_cameraMoveAngle) * 720.0f;


	if (Pad::isPress(PAD_INPUT_3))
	{
		m_cameraTarget.x += 20.0f;
	}
	SetCameraPositionAndTarget_UpVecY(m_cameraPos, m_cameraTarget);





	// ボタンでカメラの視野角を変更する
	if (Pad::isPress(PAD_INPUT_1))
	{
		m_viewAngle -= 0.01f;
		if (m_viewAngle < DX_PI_F / 180.0f * 5.0f)
		{
			m_viewAngle < DX_PI_F / 180.0f * 5.0f;
		}
	}
	if (Pad::isPress(PAD_INPUT_B))
	{
		m_viewAngle += 0.01f;
		if (m_viewAngle < DX_PI_F / 180.0f * 120.0f)
		{
			m_viewAngle < DX_PI_F / 180.0f * 120.0f;
		}
	}
	SetupCamera_Perspective(m_viewAngle);
	return this;
}

void SceneTest::draw()
{
	// 三角形
	VECTOR Pos1,Pos2,Pos3;
	Pos1 = VGet(-300,  300,   0);
	Pos2 = VGet( 300,  300,   0);
	Pos3 = VGet(-300, -300,   0);
	DrawTriangle3D(Pos1, Pos2, Pos3, 0x00ff00, true);

	Pos1 = VGet( 300, -300,   0);
	Pos2 = VGet( 300,  300,   0);
	Pos3 = VGet(-300, -300,   0);
	DrawTriangle3D(Pos1, Pos2, Pos3, 0x00ff00, true);

	Pos1 = VGet(-300,   0,  300);
	Pos2 = VGet( 300,   0,  300);
	Pos3 = VGet(-300,   0, -300);
	DrawTriangle3D(Pos1, Pos2, Pos3, 0x0000ff, true);



	// 球体
	VECTOR Posball;
	float Hankei;
	int vertex;
	Posball.x = 0.0f;
	Posball.y = 200.0f;
	Posball.z = 0.0f;
	Hankei = 128.0f;
	vertex = 200;
	DrawSphere3D(Posball, Hankei, vertex, 0xffffff, true, true);














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
	for (float z = -300.0f; z <= 300.0f; z += 100.0f)
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

	for (float x = -300.0f; x <= 300.0f; x += 100.0f)
	{
		start.x = x;
		end.x = x;
		DrawLine3D(start, end, 0xffff00);
	}
	// 高さグリッドを同様に引く
	start.x = 0.0f;
	start.y = -1200.0f;
	start.z = 0.0f;

	end.x = 0.0f;
	end.y = 1200.0f;
	end.z = 0.0f;
	DrawLine3D(start, end, 0x00ffff);














	DrawFormatString(0, 16, 0xffffff, "FOV : %f", m_viewAngle, true);
	DrawString(  0,   0, "3Dの勉強", 0xffffff);	// X,Y座標でどこに表示しているか
//	DrawString(128,   0, "3Dの勉強", 0xffffff);
//	DrawString(  0, 128, "3Dの勉強", 0xffffff);
}

