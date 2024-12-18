#include "GameScene_2.h"
#include "SceneManager.h"
#include "GameOverScene.h"

#include "DxLib.h"
#include "Pad.h"

#include "Screen.h"
#include "Camera.h"
#include "Map.h"
#include "MapData.h"
#include "Player.h"
#include "BaseEnemy.h"

GameScene_2::GameScene_2(SceneManager& manager) : BaseScene(manager),
m_pMap(new Map()),
m_pCamera(new Camera()),
m_pPlayer(new Player()),
m_pBaseEnemy(new BaseEnemy())
{
}

GameScene_2::~GameScene_2()
{
}

void GameScene_2::Init()
{
	m_pMap->Init(2);
	m_pCamera->Init();
	m_pPlayer->Init(2);
	m_pBaseEnemy->Init(2);
}
void GameScene_2::Update()
{
	m_pPlayer->Update(2);
	m_pBaseEnemy->Update(2, m_pPlayer);
	m_pCamera->Update(m_pPlayer);
	Pad::Update();
	// “ü—Íó‘Ô‚ğXV
	auto input = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (Pad::IsTrigger(input & PAD_INPUT_X))
	{
		auto next = std::make_shared<GameOverScene>(m_sceneManager);
		m_sceneManager.ChangeScene(next);
	}
}

void GameScene_2::Draw()
{

	m_pMap->Draw(2, m_pCamera);
	m_pPlayer->Draw(2, m_pCamera);
	m_pBaseEnemy->Draw(m_pCamera);
#ifdef _DEBUG
	DrawFormatString(0, 0, 0xffffff, "GameScene_2", true);
	DrawFormatString(0, 16, 0xcc0000, " PlayerPosX    : %.1f", m_pPlayer->GetPlayerPos().x, true);
	DrawFormatString(0, 32, 0xcc0000, " PlayerPosY    : %.1f", m_pPlayer->GetPlayerPos().y, true);
	DrawFormatString(0, 48, 0x00cc00, " BaseEnemyPosX : %.1f", m_pBaseEnemy->GetBaseEnemyPos().x, true);
	DrawFormatString(0, 64, 0x00cc00, " BaseEnemyPosY : %.1f", m_pBaseEnemy->GetBaseEnemyPos().y, true);
	DrawFormatString(0, 80, 0x00aaaa, " CameraPosX    : %.1f", m_pCamera->GetCameraDrawOffset().x, true);
	DrawFormatString(0, 96, 0x00aaaa, " CameraPosY    : %.1f", m_pCamera->GetCameraDrawOffset().y, true);
#endif // _DEBUG
	//DrawBox(100, 100, 640, 640, 0xaaaaaa, true);
}