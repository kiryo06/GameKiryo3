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
	// VECTOR�\����
	// 3D���W��\������̂ɕK�v��x,y,z��3�������o�[�Ƃ��Ď��\����
	VECTOR start;	// �n�_
	VECTOR end;		// �I�_

	start.x = -300.0f;
	start.y = 0.0f;
	start.z = 0.0f;

	end.x = 300.0f;
	end.y = 0.0f;
	end.z = 0.0f;
	DrawLine3D(start, end, 0xff0000);

	DrawString(0, 0, "3D�̕׋�", 0xffffff);
}

