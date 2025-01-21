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
#include "Kuribou.h"

GameScene_1::GameScene_1(SceneManager& manager) : BaseScene(manager),
m_pMap(new Map()),
m_pCamera(new Camera()),
m_pPlayer(new Player()),
m_pKuribou(new Kuribou())
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
	m_pKuribou->Init(1);
}
void GameScene_1::Update()
{
	m_pPlayer->Update(m_pKuribou,1);
	m_pKuribou->Update(1,m_pPlayer);
	m_pCamera->Update(m_pPlayer);
	Pad::Update();
	// ���͏�Ԃ��X�V
	auto input = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (Pad::IsTrigger(input & PAD_INPUT_X))
	{
		auto next = std::make_shared<GameScene_2>(m_sceneManager);
		m_sceneManager.ChangeScene(next);
	}
}

void GameScene_1::Draw()
{
	m_pMap->Draw(1, m_pCamera);
	m_pPlayer->Draw(1,m_pCamera);
	m_pKuribou->Draw(m_pCamera);
#ifdef _DEBUG
	DrawBox(0, 0, 300, 200, 0x444444, true);
	DrawFormatString(0, 0 , 0xffffff, " GameScene_1         ", true);
	DrawFormatString(0, 16, 0xcc0000, " PlayerPosX    : %.1f", m_pPlayer->GetPlayerPos().x, true);
	DrawFormatString(0, 32, 0xcc0000, " PlayerPosY    : %.1f", m_pPlayer->GetPlayerPos().y, true);
	DrawFormatString(0, 48, 0x00cc00, " KuribouPosX   : %.1f", m_pKuribou->GetKuribouPos().x, true);
	DrawFormatString(0, 64, 0x00cc00, " KuribouPosY   : %.1f", m_pKuribou->GetKuribouPos().y, true);
	DrawFormatString(0, 80, 0x00aaaa, " CameraPosX    : %.1f", m_pCamera->GetCameraDrawOffset().x, true);
	DrawFormatString(0, 96, 0x00aaaa, " CameraPosY    : %.1f", m_pCamera->GetCameraDrawOffset().y, true);
#endif // _DEBUG
}