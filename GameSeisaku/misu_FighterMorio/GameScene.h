#pragma once
#include "BaseScene.h"

class SceneManager;
class GameScene : public BaseScene
{
public:
	GameScene(SceneManager& manager);
	virtual ~GameScene() override;
	void Init();
	void Update();
	void Draw();

};

