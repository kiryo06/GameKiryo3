#pragma once

#include "Vec2.h"

class SceneMain;

class ObjectTest
{
public:
	ObjectTest();
	virtual ~ObjectTest();

	virtual void init();
	virtual void end();

	virtual void update();
	virtual void draw();

protected:
	// グラフィックハンドル
	int		m_hGraph;
	// 左上座標
	Vec2	m_pos;
};