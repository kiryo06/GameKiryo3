#include "GameScene_1.h"
#include "SceneManager.h"
#include "GameScene_2.h"

#include "DxLib.h"
#include "Pad.h"

#include "Screen.h"
#include "Camera.h"
#include "Map.h"
#include "MapData.h"
#include "Player.h"



GameScene_1::GameScene_1(SceneManager& manager) : BaseScene(manager),
m_pPlayer(new Player()),
m_pMap(new Map()),
m_pCamera(new Camera())
{
}

GameScene_1::~GameScene_1()
{
}

void GameScene_1::Init()
{
	m_pPlayer->Init(1);
	m_pMap->Init(1);
	m_pCamera->Init();
}
void GameScene_1::Update()
{
	m_pPlayer->Update(1);
	m_pCamera->Update(m_pPlayer);
	Pad::Update();
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		auto next = std::make_shared<GameScene_2>(m_sceneManager);
		m_sceneManager.ChangeScene(next);
	}
}

void GameScene_1::Draw()
{
	m_pMap->Draw(1, m_pCamera);
	m_pPlayer->Draw(m_pCamera);
#ifdef _DEBUG
	DrawFormatString(0, 0, 0xffffff, "GameScene_1", true);
	DrawFormatString(0, 16, 0xcc0000, " PlayerPosX : %f", m_pPlayer->GetPlayerPos().x, true);
	DrawFormatString(0, 32, 0xcc0000, " PlayerPosY : %f", m_pPlayer->GetPlayerPos().y, true);
	DrawFormatString(0, 48, 0x00aaaa, " CameraPosX : %f", m_pCamera->GetCameraDrawOffset().x, true);
	DrawFormatString(0, 64, 0x00aaaa, " CameraPosY : %f", m_pCamera->GetCameraDrawOffset().y, true);
#endif // _DEBUG
	//DrawBox(100, 100, 640, 640, 0x555555, true);
}