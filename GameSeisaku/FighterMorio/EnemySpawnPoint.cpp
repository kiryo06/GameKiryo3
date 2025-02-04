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
	for (auto& item : m_pKuribou)
	{
		item->Draw(m_pCamera);
	}
}

void EnemySpawnPoint::SpawnPos()
{
	PlayerPosX = m_pPlayer->GetPlayerPos().x;
	
	// 1�̖�
	if (PlayerPosX >= Master::kSpawnPosX01)
	{
		EnemyPos(1);
	}
	// 2�̖�
	if (PlayerPosX >= Master::kSpawnPosX02)
	{
		EnemyPos(2);
	}
	// 3�̖�
	if (PlayerPosX >= Master::kSpawnPosX03)
	{
		EnemyPos(3);
	}
	// 4�̖�
	if (PlayerPosX >= Master::kSpawnPosX04)
	{
		EnemyPos(4);
	}
	// 5�̖�
	if (PlayerPosX >= Master::kSpawnPosX05)
	{
		EnemyPos(5);
	}
	// 6�̖�
	if (PlayerPosX >= Master::kSpawnPosX06)
	{
		EnemyPos(6);
	}
	// 7�̖�
	if (PlayerPosX >= Master::kSpawnPosX07)
	{
		EnemyPos(7);
	}
	// 8�̖�
	if (PlayerPosX >= Master::kSpawnPosX08)
	{
		EnemyPos(8);
	}
	// 9�̖�
	if (PlayerPosX >= Master::kSpawnPosX09)
	{
		EnemyPos(9);
	}
	// 10�̖�
	if (PlayerPosX >= Master::kSpawnPosX10)
	{
		EnemyPos(10);
	}
	// 11�̖�
	if (PlayerPosX >= Master::kSpawnPosX11)
	{
		EnemyPos(11);
	}
	// 12�̖�
	if (PlayerPosX >= Master::kSpawnPosX12)
	{
		EnemyPos(12);
	}
	// 13�̖�
	if (PlayerPosX >= Master::kSpawnPosX13)
	{
		EnemyPos(13);
	}
	// 14�̖�
	if (PlayerPosX >= Master::kSpawnPosX14)
	{
		EnemyPos(14);
	}
	// 15�̖�
	if (PlayerPosX >= Master::kSpawnPosX15)
	{
		EnemyPos(15);
	}
	// 16�̖�
	if (PlayerPosX >= Master::kSpawnPosX16)
	{
		EnemyPos(16);
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
	// �G4�̖ڂ̃X�|�[���ʒu
	if (EnemyNumber == 4)
	{
		Kuribou* newKuribou = new Kuribou;
		newKuribou->Init(1);
		newKuribou->SetPosX(Master::kKuribouPosX04);
		newKuribou->SetPosY(Master::kKuribouPosY04);
		m_pKuribou.emplace_back(newKuribou);
	}
	// �G5�̖ڂ̃X�|�[���ʒu
	if (EnemyNumber == 5)
	{
		Kuribou* newKuribou = new Kuribou;
		newKuribou->Init(1);
		newKuribou->SetPosX(Master::kKuribouPosX05);
		newKuribou->SetPosY(Master::kKuribouPosY05);
		m_pKuribou.emplace_back(newKuribou);
	}
	// �G6�̖ڂ̃X�|�[���ʒu
	if (EnemyNumber == 6)
	{
		Kuribou* newKuribou = new Kuribou;
		newKuribou->Init(1);
		newKuribou->SetPosX(Master::kKuribouPosX06);
		newKuribou->SetPosY(Master::kKuribouPosY06);
		m_pKuribou.emplace_back(newKuribou);
	}
	// �G7�̖ڂ̃X�|�[���ʒu
	if (EnemyNumber == 7)
	{
		Kuribou* newKuribou = new Kuribou;
		newKuribou->Init(1);
		newKuribou->SetPosX(Master::kKuribouPosX07);
		newKuribou->SetPosY(Master::kKuribouPosY07);
		m_pKuribou.emplace_back(newKuribou);
	}
	// �G8�̖ڂ̃X�|�[���ʒu
	if (EnemyNumber == 8)
	{
		Kuribou* newKuribou = new Kuribou;
		newKuribou->Init(1);
		newKuribou->SetPosX(Master::kKuribouPosX08);
		newKuribou->SetPosY(Master::kKuribouPosY08);
		m_pKuribou.emplace_back(newKuribou);
	}
	// �G9�̖ڂ̃X�|�[���ʒu
	if (EnemyNumber == 9)
	{
		Kuribou* newKuribou = new Kuribou;
		newKuribou->Init(1);
		newKuribou->SetPosX(Master::kKuribouPosX09);
		newKuribou->SetPosY(Master::kKuribouPosY09);
		m_pKuribou.emplace_back(newKuribou);
	}
	// �G10�̖ڂ̃X�|�[���ʒu
	if (EnemyNumber == 10)
	{
		Kuribou* newKuribou = new Kuribou;
		newKuribou->Init(1);
		newKuribou->SetPosX(Master::kKuribouPosX10);
		newKuribou->SetPosY(Master::kKuribouPosY10);
		m_pKuribou.emplace_back(newKuribou);
	}
	// �G11�̖ڂ̃X�|�[���ʒu
	if (EnemyNumber == 11)
	{
		Kuribou* newKuribou = new Kuribou;
		newKuribou->Init(1);
		newKuribou->SetPosX(Master::kKuribouPosX11);
		newKuribou->SetPosY(Master::kKuribouPosY11);
		m_pKuribou.emplace_back(newKuribou);
	}
	// �G12�̖ڂ̃X�|�[���ʒu
	if (EnemyNumber == 12)
	{
		Kuribou* newKuribou = new Kuribou;
		newKuribou->Init(1);
		newKuribou->SetPosX(Master::kKuribouPosX12);
		newKuribou->SetPosY(Master::kKuribouPosY12);
		m_pKuribou.emplace_back(newKuribou);
	}
	// �G13�̖ڂ̃X�|�[���ʒu
	if (EnemyNumber == 13)
	{
		Kuribou* newKuribou = new Kuribou;
		newKuribou->Init(1);
		newKuribou->SetPosX(Master::kKuribouPosX13);
		newKuribou->SetPosY(Master::kKuribouPosY13);
		m_pKuribou.emplace_back(newKuribou);
	}
	// �G14�̖ڂ̃X�|�[���ʒu
	if (EnemyNumber == 14)
	{
		Kuribou* newKuribou = new Kuribou;
		newKuribou->Init(1);
		newKuribou->SetPosX(Master::kKuribouPosX14);
		newKuribou->SetPosY(Master::kKuribouPosY14);
		m_pKuribou.emplace_back(newKuribou);
	}
	// �G15�̖ڂ̃X�|�[���ʒu
	if (EnemyNumber == 15)
	{
		Kuribou* newKuribou = new Kuribou;
		newKuribou->Init(1);
		newKuribou->SetPosX(Master::kKuribouPosX15);
		newKuribou->SetPosY(Master::kKuribouPosY15);
		m_pKuribou.emplace_back(newKuribou);
	}
	// �G16�̖ڂ̃X�|�[���ʒu
	if (EnemyNumber == 16)
	{
		Kuribou* newKuribou = new Kuribou;
		newKuribou->Init(1);
		newKuribou->SetPosX(Master::kKuribouPosX16);
		newKuribou->SetPosY(Master::kKuribouPosY16);
		m_pKuribou.emplace_back(newKuribou);
	}
}
