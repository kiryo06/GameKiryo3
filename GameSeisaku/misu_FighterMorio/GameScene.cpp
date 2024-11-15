#include "GameScene.h"
#include "SceneManager.h"
#include "TitleScene.h"

#include "DxLib.h"

GameScene::GameScene(SceneManager& manager) : BaseScene(manager)
{
}

GameScene::~GameScene()
{
}

void GameScene::Init()
{
}

void GameScene::Update()
{
	if (KEY_INPUT_0)
	{
		auto next = std::make_shared<TitleScene>(m_sceneManager);
		m_sceneManager.ChangeScene(next);
	}
}

void GameScene::Draw()
{
	DrawBox(12, 12, 12, 12, 0xffff34, true);
}

