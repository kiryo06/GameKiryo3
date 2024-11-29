#include "GameScene.h"
#include "SceneManager.h"
#include "GameScene_1.h"

#include "DxLib.h"
#include "Pad.h"

#include "Screen.h"
#include "Camera.h"
#include "Map.h"
#include "MapData.h"
#include "Player.h"



GameScene::GameScene(SceneManager& manager) : BaseScene(manager),
m_pPlayer(new Player()),
m_pMap(new Map()),
m_pCamera(new Camera())
{
}

GameScene::~GameScene()
{
}

void GameScene::Init()
{
	m_pPlayer->Init(0);
	m_pMap->Init(0);
	m_pCamera->Init();
}
void GameScene::Update()
{
	m_pPlayer->Update(0);
	m_pCamera->Update(m_pPlayer);
	Pad::Update();
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		auto next = std::make_shared<GameScene_1>(m_sceneManager);
		m_sceneManager.ChangeScene(next);
	}
}

void GameScene::Draw()
{
	m_pPlayer->Draw(m_pCamera);
	m_pMap->Draw(0, m_pCamera);
	DrawFormatString(0, 0, 0xffffff, "GameScene",true);
	//DrawBox(100, 100, 640, 640, 0xaaaa00, true);
}