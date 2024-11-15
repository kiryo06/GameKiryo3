#include "Setting.h"

Uti::Uti() :
	m_light(0),
	m_BGM(0),
	m_SE(0)
{
	m_lightSet = 5;
	m_BGMSet = 5;
	m_SESet = 5;
}

Uti::~Uti()
{
}

void Uti::Init()
{
}

void Uti::Update()
{
	m_light = 255 - static_cast<int>(255 * m_lightSet * 0.2f);
}

void Uti::SetUti(int BGM, int SE, int light)
{
	m_lightSet = light;
	m_BGMSet = BGM;
	m_SESet = SE;
}
