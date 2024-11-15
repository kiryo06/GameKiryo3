#pragma once
#include "BaseScene.h"

class SceneManager;
class TitleScene :
    public BaseScene
{
public:
	TitleScene(SceneManager& manager);
	virtual ~TitleScene() override;
	void Init();
	void Update();
	void Draw();

};

