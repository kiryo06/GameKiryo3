#include "SceneChange.h"
#include "DxLib.h"

SceneChange::SceneChange():
	w(32),
	h(32),
	x(0),
	y(0),
	X(0),
	Change(false),
	isSceneChange(false),
	m_FrameCounter(0)
{
}

SceneChange::~SceneChange()
{
}

void SceneChange::Init()
{
}

void SceneChange::Update()
{
	if (Change)
	{
		m_FrameCounter+= 3/*GetRand(9)*/;
		while (m_FrameCounter > 0)
		{
			if (m_FrameCounter >= 1)
			{
				x += 64;
				if (x >= 1280)
				{
					X += 64;
					x = 0;
					y += 64;
					if (y >= 704)
					{
						isSceneChange = true;
					}
				}
				m_FrameCounter -= 1;
			}
		}
	}
}

void SceneChange::Draw()
{
	DrawBox(0, 0, 1280, X, 0x333333, TRUE);
	DrawBox(0, y, x, y + 64, 0x333333, TRUE);
}
