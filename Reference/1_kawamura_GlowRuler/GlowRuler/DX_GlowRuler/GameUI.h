#pragma once
#include "Vec2.h"

class Handle;

class GameUI
{
public:
	GameUI();
	~GameUI();

	void Init(int mode);
	void Update();
	void Draw(const Handle& handle);

	int stageNum;

private:
	Vec2 m_stagePos;
	Vec2 m_WindowPos;
	Vec2 m_iconPos;

	int m_gamemode;
};

