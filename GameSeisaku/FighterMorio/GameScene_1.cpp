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
#include "BaseEnemy.h"



GameScene_1::GameScene_1(SceneManager& manager) : BaseScene(manager),
m_pMap(new Map()),
m_pCamera(new Camera()),
m_pPlayer(new Player()),
m_pBaseEnemy(new BaseEnemy())
{
}

GameScene_1::~GameScene_1()
{
}

void GameScene_1::Init()
{
	m_pMap->Init(1);
	m_pCamera->Init();
	m_pPlayer->Init(1);
	m_pBaseEnemy->Init(1);
}
void GameScene_1::Update()
{
	m_pPlayer->Update(1);
	m_pBaseEnemy->Update(1);
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
	m_pPlayer->Draw(m_pCamera);
	m_pBaseEnemy->Draw(m_pCamera);
	m_pMap->Draw(1, m_pCamera);
#ifdef _DEBUG
	DrawFormatString(0, 0, 0xffffff, "GameScene_1", true);
	DrawFormatString(0, 16, 0xcc0000, " PlayerPosX    : %.3f", m_pPlayer->GetPlayerPos().x, true);
	DrawFormatString(0, 32, 0xcc0000, " PlayerPosY    : %.3f", m_pPlayer->GetPlayerPos().y, true);
	DrawFormatString(0, 48, 0x00cc00, " BaseEnemyPosX : %.3f", m_pBaseEnemy->GetBaseEnemyPos().x, true);
	DrawFormatString(0, 64, 0x00cc00, " BaseEnemyPosY : %.3f", m_pBaseEnemy->GetBaseEnemyPos().y, true);
	DrawFormatString(0, 80, 0x00aaaa, " CameraPosX    : %.3f", m_pCamera->GetCameraDrawOffset().x, true);
	DrawFormatString(0, 96, 0x00aaaa, " CameraPosY    : %.3f", m_pCamera->GetCameraDrawOffset().y, true);
#endif // _DEBUG
	//DrawBox(100, 100, 640, 640, 0x555555, true);
}