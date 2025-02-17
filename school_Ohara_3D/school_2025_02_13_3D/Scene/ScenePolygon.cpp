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
	//SetCameraPositionAndTarget_UpVecY(VGet(-200,200,720), VGet(0,0,0));
	SetCameraPositionAndTarget_UpVecY(VGet(0, 400, -360), VGet(0, 0, 0));

	// カメラの視野角を設定する
	SetupCamera_Perspective(DX_PI_F / 3);	// 60度

	// カメラのnear, farを設定する
	SetCameraNearFar(10.0f, 1800.0f);

	// テクスチャの読み込み
	m_textureHandle = LoadGraph("Data/car.jpg");
}

void ScenePolygon::end()
{
	// テクスチャメモリを開放する
	DeleteGraph(m_textureHandle);
}

SceneBase* ScenePolygon::update()
{
	return this;
}

void ScenePolygon::draw()
{
	// X軸の線	赤
	DrawLine3D(VGet(-200, 0, 0), VGet(200, 0, 0), 0xff0000);
	// Y軸の線	黄
	DrawLine3D(VGet(0, -200, 0), VGet(0, 200, 0), 0xffff00);
	// Z軸の線	緑
	DrawLine3D(VGet(0, 0, -200), VGet(0, 0, 200), 0x00ff00);

	/*DrawTriangle3D(
		VGet(-200, 0,  200),
		VGet( 200, 0,  200),
		VGet(-200, 0, -200),
		0xff0000, true);*/

	// ↑の三角形をDrawPolygon3Dを使って表示してみる
	VERTEX3D Vertex[6];	// 頂点データの配列を3つ準備する

	Vertex[0].pos = VGet(-200, 0, 200);	// 頂点座標
	Vertex[0].norm = VGet(0, 1, 0);	// 法線 ポリゴンの向いている方向
	Vertex[0].dif = GetColorU8(255, 255, 255, 255);	// デフューズ?カラー
	Vertex[0].spc = GetColorU8(255, 255, 255, 255);	// スペキュラ?カラー
	Vertex[0].u = 0.0f;		// テクスチャ座標	今回は使わない
	Vertex[0].v = 0.0f;
	Vertex[0].su = 0.0f;
	Vertex[0].sv = 0.0f;

	Vertex[1].pos = VGet(200, 0, 200);	// 頂点座標
	Vertex[1].norm = VGet(0, 1, 0);	// 法線 ポリゴンの向いている方向
	Vertex[1].dif = GetColorU8(255, 255, 255, 255);	// デフューズ?カラー
	Vertex[1].spc = GetColorU8(255, 255, 255, 255);	// スペキュラ?カラー
	Vertex[1].u = 0.5f;		// テクスチャ座標	今回は使わない
	Vertex[1].v = 0.0f;
	Vertex[1].su = 0.0f;
	Vertex[1].sv = 0.0f;

	Vertex[2].pos = VGet(-200, 0, -200);	// 頂点座標
	Vertex[2].norm = VGet(0, 1, 0);	// 法線 ポリゴンの向いている方向
	Vertex[2].dif = GetColorU8(255, 255, 255, 255);	// デフューズ?カラー
	Vertex[2].spc = GetColorU8(255, 255, 255, 255);	// スペキュラ?カラー
	Vertex[2].u = 0.0f;		// テクスチャ座標	今回は使わない
	Vertex[2].v = 1.0f;
	Vertex[2].su = 0.0f;
	Vertex[2].sv = 0.0f;

	Vertex[3].pos = VGet(200, 0, 200);	// 頂点座標
	Vertex[3].norm = VGet(0, 1, 0);	// 法線 ポリゴンの向いている方向
	Vertex[3].dif = GetColorU8(255, 255, 255, 255);	// デフューズ?カラー
	Vertex[3].spc = GetColorU8(255, 255, 255, 255);	// スペキュラ?カラー
	Vertex[3].u = 0.5f;		// テクスチャ座標	今回は使わない
	Vertex[3].v = 0.0f;
	Vertex[3].su = 0.0f;
	Vertex[3].sv = 0.0f;

	Vertex[4].pos = VGet(200, 0, -200);	// 頂点座標
	Vertex[4].norm = VGet(0, 1, 0);	// 法線 ポリゴンの向いている方向
	Vertex[4].dif = GetColorU8(255, 255, 255, 255);	// デフューズ?カラー
	Vertex[4].spc = GetColorU8(255, 255, 255, 255);	// スペキュラ?カラー
	Vertex[4].u = 0.5f;		// テクスチャ座標	今回は使わない
	Vertex[4].v = 1.0f;
	Vertex[4].su = 0.0f;
	Vertex[4].sv = 0.0f;

	Vertex[5].pos = VGet(-200, 0, -200);	// 頂点座標
	Vertex[5].norm = VGet(0, 1, 0);	// 法線 ポリゴンの向いている方向
	Vertex[5].dif = GetColorU8(255, 255, 255, 255);	// デフューズ?カラー
	Vertex[5].spc = GetColorU8(255, 255, 255, 255);	// スペキュラ?カラー
	Vertex[5].u = 0.0f;		// テクスチャ座標	今回は使わない
	Vertex[5].v = 1.0f;
	Vertex[5].su = 0.0f;
	Vertex[5].sv = 0.0f;

	DrawPolygon3D(Vertex, 2, m_textureHandle, false);
























	// 3D空間上の座標を2D座標に変換して文字列に表示したい！
	VECTOR pos2D;
	pos2D = ConvWorldPosToScreenPos(VGet(330, 0, 0));
	DrawString(pos2D.x, pos2D.y, "X+", 0xffffff);
	pos2D = ConvWorldPosToScreenPos(VGet(-330, 0, 0));
	DrawString(pos2D.x, pos2D.y, "X-", 0xffffff);
	pos2D = ConvWorldPosToScreenPos(VGet(0, 330, 0));
	DrawString(pos2D.x, pos2D.y, "Y+", 0xffffff);
	pos2D = ConvWorldPosToScreenPos(VGet(0, -330, 0));
	DrawString(pos2D.x, pos2D.y, "Y-", 0xffffff);
	pos2D = ConvWorldPosToScreenPos(VGet(0, 0, 330));
	DrawString(pos2D.x, pos2D.y, "Z+", 0xffffff);
	pos2D = ConvWorldPosToScreenPos(VGet(0, 0, -330));
	DrawString(pos2D.x, pos2D.y, "Z-", 0xffffff);
	DrawString(0, 0, "ScenePolygon", 0xffffff);
}
