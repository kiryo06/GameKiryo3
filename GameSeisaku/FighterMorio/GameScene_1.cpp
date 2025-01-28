#include "GameScene_1.h"
#include "SceneManager.h"
#include "GameScene_2.h"
#include "GameOverScene.h"

#include "DxLib.h"
#include "Pad.h"
#include "Debug.h"

#include "Screen.h"
#include "Camera.h"
#include "Map.h"
#include "MapData.h"
#include "Player.h"
#include "Kuribou.h"
#include "SystemEngineer.h"



GameScene_1::GameScene_1(SceneManager& manager) : BaseScene(manager),
m_pMap(new Map()),
m_pCamera(new Camera()),
m_pPlayer(new Player()),
m_pKuribou(),
m_pSystemEngineer(new SystemEngineer)
{
}

GameScene_1::~GameScene_1()
{
}

void GameScene_1::Init()
{
	m_pMap->Init(1);
	m_pCamera->Init();
	m_pPlayer->Init(1, m_pSystemEngineer);
	for (auto& item : m_pKuribou)
	{
		item->Init(1);
	}
	m_pSystemEngineer->Init();
}

void GameScene_1::Update()
{
	// 入力状態を更新
	auto input = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	Pad::Update();

	m_pPlayer->Update(m_pKuribou,1);
	// Xキーを押したら敵の中身が増える
	if (input & PAD_INPUT_C)
	{
		Kuribou* newKuribou = new Kuribou;
		newKuribou->Init(1);
		m_pKuribou.emplace_back(newKuribou);
	}
	for (auto& item : m_pKuribou)
	{
		item->Update(1, m_pPlayer);
	}
	m_pCamera->Update(m_pPlayer);
	m_pSystemEngineer->Update();

	// シーン遷移
	if (Pad::IsTrigger(input & PAD_INPUT_X))
	{
		auto next = std::make_shared<GameScene_2>(m_sceneManager);
		m_sceneManager.ChangeScene(next);
	}
	// ゲームオーバー
	//if (m_pPlayer->IsPlayerDeath())
	//{
	//	auto next = std::make_shared<GameOverScene>(m_sceneManager);
	//	m_sceneManager.ChangeScene(next);
	//}
}

void GameScene_1::Draw()
{
	Kuribou* newKuribou = new Kuribou;
	m_pMap->Draw(1, m_pCamera);
	m_pPlayer->Draw(1,m_pCamera);
	for (auto& item : m_pKuribou)
	{
		item->Draw(m_pCamera);
	}
	m_pSystemEngineer->Draw();
#ifdef _DEBUG
	// 半透明の設定
	DEBUG_TRANSPARENCY
		DrawBox(0, 0, 300, 200, 0x444444, true);
	// ブレンドモードをリセット
	DEBUG_RESET
	DrawFormatString(0,   0 ,0xffffff, " GameScene_1         ", true);
	DrawFormatString(0,  16, 0xcc0000, " PlayerPosX    : %.1f", m_pPlayer->GetPlayerPos().x, true);
	DrawFormatString(0,  32, 0xcc0000, " PlayerPosY    : %.1f", m_pPlayer->GetPlayerPos().y, true);
	DrawFormatString(0,  48, 0x00cc00, " KuribouPosX   : %.1f", newKuribou->GetKuribouPos().x, true);
	DrawFormatString(0,  64, 0x00cc00, " KuribouPosY   : %.1f", newKuribou->GetKuribouPos().y, true);
	DrawFormatString(0,  80, 0xaaaaaa, " Kuribou       : %d  ", m_pKuribou.size(), true);
	DrawFormatString(0,  96, 0xaaaaaa, " PlayerDeath   : %1d ", m_pPlayer->GetPlayerDeath(), true);
	DrawFormatString(0, 112, 0xaaaaaa, " Score         : %1d ", m_pSystemEngineer->GetScore(), true);
	DrawFormatString(0, 128, 0xaaaaaa, "               : %1d ", 123456789, true);
	DrawFormatString(0, 144, 0xaaaaaa, "               : %.1f", 123456789, true);
	DrawFormatString(0, 160, 0x00aaaa, " CameraPosX    : %.1f", m_pCamera->GetCameraDrawOffset().x, true);
	DrawFormatString(0, 176, 0x00aaaa, " CameraPosY    : %.1f", m_pCamera->GetCameraDrawOffset().y, true);
#endif // _DEBUG
}