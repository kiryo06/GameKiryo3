#pragma once
#include "BaseScene.h"

#include "game.h"
#include "MapDate.h"
class SceneManager;
class GameScene_2 : public BaseScene
{
public:
	GameScene_2(SceneManager& manager);
	virtual ~GameScene_2() override;
	void Init();
	void Update();
	void Draw();
};
