#include "GameScene_1.h"
#include "SceneManager.h"
#include "GameScene_2.h"

#include "DxLib.h"
#include "Pad.h"

#include "Screen.h"
#include "Camera.h"
#include "Map.h"
#include "MapData.h"



GameScene_1::GameScene_1(SceneManager& manager) : BaseScene(manager),
m_pMap(new Map()),
m_pCamera(new Camera())
{
}

GameScene_1::~GameScene_1()
{
}

void GameScene_1::Init()
{
	m_pCamera->Init();
	m_pMap->Init(1);
}
void GameScene_1::Update()
{
	//UpdatePlayer(player, map);
	m_pCamera->Update();
	Pad::Update();
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		auto next = std::make_shared<GameScene_2>(m_sceneManager);
		m_sceneManager.ChangeScene(next);
	}
}

void GameScene_1::Draw()
{
	//DrawPlayer(player, camera);
	m_pMap->Draw(1, m_pCamera);
	DrawFormatString(0, 0, 0xffffff, "GameScene_1", true);
	//DrawBox(100, 100, 640, 640, 0x555555, true);
}