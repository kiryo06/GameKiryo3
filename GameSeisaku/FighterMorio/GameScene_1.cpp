#include "GameScene_1.h"
#include "SceneManager.h"
#include "GameScene_2.h"

#include "DxLib.h"
#include "Pad.h"

#include "Screen.h"
#include "Camera.h"
#include "Map.h"
#include "MapData.h"



GameScene_1::GameScene_1(SceneManager& manager) : BaseScene(manager)
{
}

GameScene_1::~GameScene_1()
{
}

void GameScene_1::Init()
{
}
void GameScene_1::Update()
{
	Pad::Update();
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		auto next = std::make_shared<GameScene_2>(m_sceneManager);
		m_sceneManager.ChangeScene(next);
	}
}

void GameScene_1::Draw()
{
	DrawFormatString(0, 0, 0xffffff, "GameScene_1", true);
	DrawBox(100, 100, 640, 640, 0x555555, true);
}