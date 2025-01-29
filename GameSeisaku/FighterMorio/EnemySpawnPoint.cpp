#include "EnemySpawnPoint.h"
#include "DxLib.h"
#include "Player.h"
#include "Kuribou.h"
#include "Camera.h"
#include "MasterFunction.h"

EnemySpawnPoint::EnemySpawnPoint():
	m_pPlayer(new Player),
	m_pKuribou(),
	m_pCamera(new Camera),
	PlayerPosX(0),
	m_kuribou00(true),
	m_kuribou01(true),
	m_kuribou02(true),
	m_kuribou03(true),
	m_kuribou04(true),
	m_kuribou05(true),
	m_kuribou06(true),
	m_kuribou07(true),
	m_kuribou08(true),
	m_kuribou09(true),
	m_kuribou10(true),
	m_kuribou11(true),
	m_kuribou12(true),
	m_kuribou13(true),
	m_kuribou14(true),
	m_kuribou15(true),
	m_kuribou16(true)
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
	//Kuribou* newKuribou = new Kuribou;
	//newKuribou->Init(1);
	SpawnPos();
	//m_pKuribou.emplace_back(newKuribou);
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

void EnemySpawnPoint::SpawnPos()
{
	PlayerPosX = m_pPlayer->GetPlayerPos().x;
	
	// 1�̖�
	if (PlayerPosX >= 0)
	{
		EnemyPos(1);
	}
	// 2�̖�
	if (PlayerPosX >= 90)
	{
		EnemyPos(2);
	}
	// 3�̖�
	if (PlayerPosX >= 1500)
	{
		EnemyPos(3);
	}
	// 4�̖�
	if (PlayerPosX >= 1600)
	{
		EnemyPos(4);
	}
	// 5�̖�
	if (PlayerPosX >= 2200)
	{
		EnemyPos(5);
	}
	// 6�̖�
	if (PlayerPosX >= 2200)
	{
		EnemyPos(6);
	}
	// 7�̖�
	if (PlayerPosX >= 2200)
	{
		EnemyPos(7);
	}
	// 8�̖�
	if (PlayerPosX >= 2200)
	{
		EnemyPos(8);
	}
	// 9�̖�
	if (PlayerPosX >= 2200)
	{
		EnemyPos(9);
	}
	// 10�̖�
	if (PlayerPosX >= 2200)
	{
		EnemyPos(10);
	}
	// 11�̖�
	if (PlayerPosX >= 2200)
	{
		EnemyPos(11);
	}
	// 12�̖�
	if (PlayerPosX >= 2200)
	{
		EnemyPos(12);
	}
	// 13�̖�
	if (PlayerPosX >= 2200)
	{
		EnemyPos(13);
	}
	// 14�̖�
	if (PlayerPosX >= 2200)
	{
		EnemyPos(14);
	}
	// 15�̖�
	if (PlayerPosX >= 2200)
	{
		EnemyPos(15);
	}
}

void EnemySpawnPoint::EnemyPos(int EnemyNumber)
{
	// �G1�̖ڂ̃X�|�[���ʒu
	if (EnemyNumber == 1)
	{
		Kuribou* newKuribou = new Kuribou;
		newKuribou->Init(1);
		newKuribou->SetPosX(Master::kKuribouPosX01);
		newKuribou->SetPosY(Master::kKuribouPosY01);
		m_pKuribou.emplace_back(newKuribou);
	}
	// �G2�̖ڂ̃X�|�[���ʒu
	if (EnemyNumber == 2)
	{
		Kuribou* newKuribou = new Kuribou;
		newKuribou->Init(1);
		newKuribou->SetPosX(Master::kKuribouPosX02);
		newKuribou->SetPosY(Master::kKuribouPosY02);
		m_pKuribou.emplace_back(newKuribou);
	}
	// �G3�̖ڂ̃X�|�[���ʒu
	if (EnemyNumber == 3)
	{
		Kuribou* newKuribou = new Kuribou;
		newKuribou->Init(1);
		newKuribou->SetPosX(Master::kKuribouPosX03);
		newKuribou->SetPosY(Master::kKuribouPosY03);
		m_pKuribou.emplace_back(newKuribou);
	}
	// �G3�̖ڂ̃X�|�[���ʒu
	if (EnemyNumber == 4)
	{
		Kuribou* newKuribou = new Kuribou;
		newKuribou->Init(1);
		newKuribou->SetPosX(Master::kKuribouPosX04);
		newKuribou->SetPosY(Master::kKuribouPosY04);
		m_pKuribou.emplace_back(newKuribou);
	}
}
