#pragma once
#include "BaseScene.h"

#include "game.h"
class SceneManager;
class Map;
class Camera;
class Player;
class BaseEnemy;
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
	BaseEnemy* m_pBaseEnemy;
};