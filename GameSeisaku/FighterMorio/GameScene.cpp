#include "GameScene.h"
#include "SceneManager.h"
#include "GameScene_1.h"

#include "DxLib.h"
#include "Pad.h"

#include "Screen.h"
#include "Camera.h"
#include "Map.h"
#include "MapData.h"



GameScene::GameScene(SceneManager& manager) : BaseScene(manager),
m_pMap(new Map()),
m_pCamera(new Camera())
{
}

GameScene::~GameScene()
{
}

void GameScene::Init()
{
	m_pCamera->Init();
	m_pMap->Init(0);
}
void GameScene::Update()
{
	//UpdatePlayer(player, map);
	m_pCamera->Update();
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
	m_pMap->Draw(0, m_pCamera);
	DrawFormatString(0, 0, 0xffffff, "GameScene",true);
	//DrawBox(100, 100, 640, 640, 0xaaaa00, true);
}