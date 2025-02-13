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
	// �O���t�B�b�N�n���h��
	int		m_hGraph;
	// ������W
	Vec2	m_pos;
};