//#include "GameScene.h"
//#include "SceneManager.h"
//#include "GameScene_1.h"
//
//#include "DxLib.h"
//#include "Pad.h"
//
//#include "Screen.h"
//#include "Camera.h"
//#include "Map.h"
//#include "MapData.h"
//#include "Player.h"
//#include "Kuribou.h"
//
//
//
//GameScene::GameScene(SceneManager& manager) : BaseScene(manager),
//m_pMap(new Map()),
//m_pCamera(new Camera()),
//m_pPlayer(new Player()),
//m_pKuribou(new Kuribou())
//{
//}
//
//GameScene::~GameScene()
//{
//}
//
//void GameScene::Init()
//{
//	m_pMap->Init(0);
//	m_pCamera->Init();
//	m_pPlayer->Init(0);
//	m_pKuribou->Init(0);
//}
//void GameScene::Update()
//{
//	m_pPlayer->Update(m_pKuribou,0);
//	m_pKuribou->Update(0,m_pPlayer);
//	m_pCamera->Update(m_pPlayer);
//	Pad::Update();
//	// 入力状態を更新
//	auto input = GetJoypadInputState(DX_INPUT_KEY_PAD1);
//	if (Pad::IsTrigger(input & PAD_INPUT_X))
//	{
//		auto next = std::make_shared<GameScene_1>(m_sceneManager);
//		m_sceneManager.ChangeScene(next);
//	}
//}
//
//void GameScene::Draw()
//{
//	m_pMap->Draw(0, m_pCamera);
//	m_pPlayer->Draw(1,m_pCamera);
//	m_pKuribou->Draw(m_pCamera);
//#ifdef _DEBUG
//	DrawBox(0, 0, 300, 200, 0x444444, true);
//	DrawFormatString(0,   0, 0xffffff, " GameScene           ", true);
//	DrawFormatString(0,  16, 0xcc0000, " PlayerPosX    : %.1f", m_pPlayer->GetPlayerPos().x, true);
//	DrawFormatString(0,  32, 0xcc0000, " PlayerPosY    : %.1f", m_pPlayer->GetPlayerPos().y, true);
//	DrawFormatString(0,  48, 0x00cc00, " KuribouPosX   : %.1f", m_pKuribou->GetKuribouPos().x, true);
//	DrawFormatString(0,  64, 0x00cc00, " KuribouPosY   : %.1f", m_pKuribou->GetKuribouPos().y, true);
//	DrawFormatString(0,  80, 0xaaaaaa, " EnemyDamage   : %.1d", 123456789, true);
//	DrawFormatString(0,  96, 0xaaaaaa, "               : %.1d", 123456789, true);
//	DrawFormatString(0, 112, 0xaaaaaa, "               : %.1d", 123456789, true);
//	DrawFormatString(0, 128, 0xaaaaaa, "               : %.1d", 123456789, true);
//	DrawFormatString(0, 144, 0xaaaaaa, "               : %.1d", 123456789, true);
//	DrawFormatString(0, 160, 0x00aaaa, " CameraPosX    : %.1f", m_pCamera->GetCameraDrawOffset().x, true);
//	DrawFormatString(0, 176, 0x00aaaa, " CameraPosY    : %.1f", m_pCamera->GetCameraDrawOffset().y, true);
//#endif // _DEBUG
//}







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
#include "Kuribou.h"



GameScene::GameScene(SceneManager& manager) : BaseScene(manager),
m_pMap(new Map()),
m_pCamera(new Camera()),
m_pPlayer(new Player()),
m_pKuribou()
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
	for (auto& item : m_pKuribou)
	{
		item->Init(0);
	}
}
void GameScene::Update()
{
	// 入力状態を更新
	auto input = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	m_pPlayer->Update(m_pKuribou, 0);
	if (input & PAD_INPUT_C)
	{
		Kuribou* newKuribou = new Kuribou;
		newKuribou->Init(0);
		m_pKuribou.emplace_back(newKuribou);
	}
	for (auto& item : m_pKuribou)
	{
		item->Update(0, m_pPlayer);
	}
	m_pCamera->Update(m_pPlayer);
	Pad::Update();
	if (Pad::IsTrigger(input & PAD_INPUT_X))
	{
		auto next = std::make_shared<GameScene_1>(m_sceneManager);
		m_sceneManager.ChangeScene(next);
	}
}

void GameScene::Draw()
{
	m_pMap->Draw(0, m_pCamera);
	m_pPlayer->Draw(1, m_pCamera);
	for (auto& item : m_pKuribou)
	{
		item->Draw(m_pCamera);
	}
#ifdef _DEBUG
	DrawBox(0, 0, 300, 200, 0x444444, true);
	DrawFormatString(0,   0, 0xffffff, " GameScene          ", true);
	DrawFormatString(0,  16, 0xcc0000, " PlayerPosX   : %.1f", m_pPlayer->GetPlayerPos().x, true);
	DrawFormatString(0,  32, 0xcc0000, " PlayerPosY   : %.1f", m_pPlayer->GetPlayerPos().y, true);
	DrawFormatString(0,  48, 0x00cc00, " KuribouPosX  : %.1f", Kuribou().GetKuribouPos().x, true);
	DrawFormatString(0,  64, 0x00cc00, " KuribouPosY  : %.1f", Kuribou().GetKuribouPos().y, true);
	DrawFormatString(0,  80, 0xaaaaaa, " Kuribou      : %d", m_pKuribou.size(), true);
	DrawFormatString(0,  96, 0xaaaaaa, " PlayerDeath  : %.1d", m_pPlayer->GetPlayerDeath(), true);
	DrawFormatString(0, 112, 0xaaaaaa, "              : %.1f", 123456789, true);
	DrawFormatString(0, 128, 0xaaaaaa, "              : %.1f", 123456789, true);
	DrawFormatString(0, 144, 0xaaaaaa, "              : %.1f", 123456789, true);
	DrawFormatString(0, 160, 0x00aaaa, " CameraPosX   : %.1f", m_pCamera->GetCameraDrawOffset().x, true);
	DrawFormatString(0, 176, 0x00aaaa, " CameraPosY   : %.1f", m_pCamera->GetCameraDrawOffset().y, true);
#endif // _DEBUG
}

