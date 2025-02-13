#include "DxLib.h"
#include "game.h"
#include "SceneTest.h"


namespace
{
	const char* const kPlayerFilename = "Data/player.bmp";
}

void SceneTest::init()
{
	m_hPlayer = LoadGraph(kPlayerFilename);
	m_obj.init();
}

void SceneTest::end()
{
	DeleteGraph(m_hPlayer);
}

SceneBase* SceneTest::update()
{
	m_obj.update();
	return this;
}

void SceneTest::draw()
{
	m_obj.draw();
}

