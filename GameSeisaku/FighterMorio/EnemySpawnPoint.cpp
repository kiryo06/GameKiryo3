#include "EnemySpawnPoint.h"
#include "DxLib.h"
#include "Player.h"
#include "Kuribou.h"
#include "Camera.h"

EnemySpawnPoint::EnemySpawnPoint():
	m_pPlayer(),
	m_pKuribou(),
	m_pCamera()
{
}

EnemySpawnPoint::~EnemySpawnPoint()
{
}

void EnemySpawnPoint::Init()
{
	for (auto& item : m_pKuribou)
	{
		item->Init(1);
	}
}

void EnemySpawnPoint::Update()
{
	// プレイヤーがある位置に到着すると敵が出現する
	if (m_pPlayer->GetPlayerPos().x == 957)
	{
		Kuribou* newKuribou = new Kuribou;
		newKuribou->Init(1);
		newKuribou->SetPosY(900.0f);
		m_pKuribou.emplace_back(newKuribou);
	}

	for (auto& item : m_pKuribou)
	{
		item->Update(1, m_pPlayer);
	}
}

void EnemySpawnPoint::Draw()
{
	Kuribou* newKuribou = new Kuribou;
	for (auto& item : m_pKuribou)
	{
		item->Draw(m_pCamera);
	}
}
