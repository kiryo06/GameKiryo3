#pragma once
#include "BaseScene.h"

class SceneManager;
class TitleScene : public BaseScene
{
public:
	int m_Graph;
	TitleScene(SceneManager& manager);
	virtual ~TitleScene() override;
	void Init();
	void Update();
	void Draw();

};

