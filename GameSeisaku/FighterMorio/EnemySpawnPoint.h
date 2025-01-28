#pragma once
#include "game.h"
#include <list>
class Player;
class Kuribou;
class Camera;
class EnemySpawnPoint
{
public:
	EnemySpawnPoint();
	~EnemySpawnPoint();
	void Init();
	void Update();
	void Draw();
private:
	Player* m_pPlayer;
	std::list<Kuribou*>m_pKuribou;
	Camera* m_pCamera;
};

