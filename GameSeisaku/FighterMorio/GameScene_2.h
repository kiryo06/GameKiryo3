#pragma once
#include "BaseScene.h"

#include "game.h"
class SceneManager;
class Map;
class Camera;
class Player;
class Kuribou;
class GameScene_2 : public BaseScene
{
public:
	GameScene_2(SceneManager& manager);
	virtual ~GameScene_2() override;
	void Init();
	void Update();
	void Draw();
private:
	Map* m_pMap;
	Camera* m_pCamera;
	Player* m_pPlayer;
	Kuribou* m_pKuribou;
};
