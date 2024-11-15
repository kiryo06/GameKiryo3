#pragma once
#include "Vec2.h"
class pColorBg
{
public:
	pColorBg();
	~pColorBg();
	void Init();
	void Update(int color);
	void Draw();

	void SetisDontMove(bool ismove) { m_isMove = !ismove; };
private:
	Vec2 m_pos;
	int m_dir;
	float m_rad;
	int m_waveLange;
	int m_waveMove;
	int m_angle;
	int m_alpha;
	int m_timer;
	int m_color;
	bool m_isMove;
};