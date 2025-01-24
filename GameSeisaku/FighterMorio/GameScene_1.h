#pragma once
#include "BaseScene.h"

#include "game.h"
#include <list>

class SceneManager;
class Map;
class Camera;
class Player;
class Kuribou;
class SystemEngineer;
class GameScene_1 : public BaseScene
{
public:
	GameScene_1(SceneManager& manager);
	virtual ~GameScene_1() override;
	void Init();
	void Update();
	void Draw();
private:
	Map* m_pMap;
	Camera* m_pCamera;
	Player* m_pPlayer;
	std::list<Kuribou*>m_pKuribou;
	SystemEngineer* m_pSystemEngineer;
};