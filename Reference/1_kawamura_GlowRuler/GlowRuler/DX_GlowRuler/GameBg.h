#pragma once
#include "Vec2.h"

struct Dia
{
	Vec2 pos = { 0,0 };
	Vec2 tripos = { 0,0 };
	int color = 0;
};

class GameBg
{
public:
	GameBg();
	~GameBg();
	void Init(int no, int color);
	void Update();
	void Draw();
	void Fade(bool isAlpha);

	void SetFlag(bool isColor) { m_isColor = isColor; };

	void Reset() { m_isClear = false; }

private:
	Dia m_dia;
	int m_dir;
	double m_angle_R;
	double m_angle_L;

	int m_alpha;
	bool m_isAlpha;
	int m_timer;

	bool m_isColor;
	bool m_isClear;

	int m_diaNo;

	float m_lotMove;
};

