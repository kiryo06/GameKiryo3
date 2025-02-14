#include "DxLib.h"
#include "game.h"
#include "SceneTest.h"


namespace
{

}

void SceneTest::init()
{

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
	DrawLine3D(start, end, 0xff0000);

	DrawString(0, 0, "3Dの勉強", 0xffffff);
}

