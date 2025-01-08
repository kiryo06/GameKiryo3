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
#include "BaseEnemy.h"



GameScene::GameScene(SceneManager& manager) : BaseScene(manager),
m_pMap(new Map()),
m_pCamera(new Camera()),
m_pPlayer(new Player()),
m_pBaseEnemy(new BaseEnemy())
{
}

GameScene::~GameScene()
{
}

void GameScene::Init()
{
	m_pMap->Init(0);
	m_pCamera->Init();
	m_pPlayer->Init(0);
	m_pBaseEnemy->Init(0);
}
void GameScene::Update()
{
	m_pPlayer->Update(0);
	m_pBaseEnemy->Update(0,m_pPlayer);
	m_pCamera->Update(m_pPlayer);
	Pad::Update();
	// 入力状態を更新
	// 入力状態を更新
	auto input = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (Pad::IsTrigger(input & PAD_INPUT_X))
	{
		auto next = std::make_shared<GameScene_1>(m_sceneManager);
		m_sceneManager.ChangeScene(next);
	}
}

void GameScene::Draw()
{
	m_pMap->Draw(0, m_pCamera);
	m_pPlayer->Draw(1,m_pCamera);
	m_pBaseEnemy->Draw(m_pCamera);
#ifdef _DEBUG
	DrawBox(0, 0, 300, 200, 0x444444, true);
	DrawFormatString(0,   0, 0xffffff, " GameScene           ", true);
	DrawFormatString(0,  16, 0xcc0000, " PlayerPosX    : %.1f", m_pPlayer->GetPlayerPos().x, true);
	DrawFormatString(0,  32, 0xcc0000, " PlayerPosY    : %.1f", m_pPlayer->GetPlayerPos().y, true);
	DrawFormatString(0,  48, 0x00cc00, " BaseEnemyPosX : %.1f", m_pBaseEnemy->GetBaseEnemyPos().x, true);
	DrawFormatString(0,  64, 0x00cc00, " BaseEnemyPosY : %.1f", m_pBaseEnemy->GetBaseEnemyPos().y, true);
	DrawFormatString(0,  80, 0xaaaaaa, "               : %.1d", 123456789, true);
	DrawFormatString(0,  96, 0xaaaaaa, "               : %.1d", 123456789, true);
	DrawFormatString(0, 112, 0xaaaaaa, "               : %.1d", 123456789, true);
	DrawFormatString(0, 128, 0xaaaaaa, "               : %.1d", 123456789, true);
	DrawFormatString(0, 144, 0xaaaaaa, "               : %.1d", 123456789, true);
	DrawFormatString(0, 160, 0x00aaaa, " CameraPosX    : %.1f", m_pCamera->GetCameraDrawOffset().x, true);
	DrawFormatString(0, 176, 0x00aaaa, " CameraPosY    : %.1f", m_pCamera->GetCameraDrawOffset().y, true);
#endif // _DEBUG
	//DrawBox(100, 100, 640, 640, 0xaaaa00, true);
}