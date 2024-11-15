#pragma once
#include "Vec2.h"

class InColorEfect
{
public:
	InColorEfect();
	~InColorEfect();
	void Init();
	void Update();
	void Draw();

private:
	Vec2 m_pos[8];
	Vec2 m_lastPos[8];
	int m_move;
	int m_rad;
	int m_color;
};

