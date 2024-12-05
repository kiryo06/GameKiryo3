#pragma once
#include "BaseScene.h"

#include "game.h"
class SceneManager;
class GameOverScene :public BaseScene
{
public:
	GameOverScene(SceneManager& manager);
	virtual ~GameOverScene() override;
	void Init();
	void Update();
	void Draw();
};