#pragma once
#include "BaseScene.h"

#include "game.h"
class SceneManager;
class Map;
class Camera;
class Player;
class GameScene : public BaseScene
{
public:
	GameScene(SceneManager& manager);
	virtual ~GameScene() override;
	void Init();
	void Update();
	void Draw();
private:
	Map* m_pMap;
	Camera* m_pCamera;
	Player* m_pPlayer;
};

