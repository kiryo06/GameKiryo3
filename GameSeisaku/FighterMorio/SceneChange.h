#pragma once
#include "game.h"
class SceneChange
{
public:
	SceneChange();
	~SceneChange();
	void Init();
	void Update();
	void Draw();
	void SetDese(bool isdese) { Change = isdese; }
	int GetChange()const {return isSceneChange; }
private:
	float w, h;
	int x; 
	int y;
	int X;
	bool Change;
	bool isSceneChange;
	int m_FrameCounter;
};

