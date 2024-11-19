#include "GameScene.h"
#include "SceneManager.h"
#include "GameScene_1.h"

#include "DxLib.h"
#include "Pad.h"

#include "Screen.h"
#include "Camera.h"
//#include "Player.h"
#include "Map.h"
#include "MapData.h"
Camera camera;
//Player player;
Map* pMap = new Map();
Map map;

GameScene::GameScene(SceneManager& manager) : BaseScene(manager)
{
}

GameScene::~GameScene()
{
}

void GameScene::Init()
{
	InitCamera(camera);
	//InitPlayer(player);
	pMap->Init();

}
void GameScene::Update()
{
	//UpdatePlayer(player, map);
	//UpdateCamera(camera, player);
	Pad::Update();
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		auto next = std::make_shared<GameScene_1>(m_sceneManager);
		m_sceneManager.ChangeScene(next);
	}
}

void GameScene::Draw()
{
	//DrawPlayer(player, camera);
	pMap->Draw(camera);
	DrawFormatString(0, 0, 0xffffff, "GameScene",true);
	//DrawBox(100, 100, 640, 640, 0xaaaa00, true);
}