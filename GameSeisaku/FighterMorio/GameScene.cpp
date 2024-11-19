#include "GameScene.h"
#include "SceneManager.h"
#include "GameScene_1.h"

#include "DxLib.h"
#include "Pad.h"

#include "Screen.h"
//#include "Player.h"
//#include "Camera.h"


//Camera camera;
//Player player;
//Map map;
//MapDate& mapdate;


GameScene::GameScene(SceneManager& manager) : BaseScene(manager)
{
}

GameScene::~GameScene()
{
}

void GameScene::Init()
{
	//InitCamera(camera);
	//InitPlayer(player);
	//InitMap(mapdate);

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
	//DrawMap(mapdate, camera);
	DrawFormatString(0, 0, 0xffffff, "GameScene",true);
	DrawBox(100, 100, 640, 640, 0xaaaa00, true);
}