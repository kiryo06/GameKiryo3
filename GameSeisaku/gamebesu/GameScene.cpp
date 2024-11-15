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
	if (CheckHitKey(KEY_INPUT_X) == 1)
	{
		auto next = std::make_shared<TitleScene>(m_sceneManager);
		m_sceneManager.ChangeScene(next);
	}
}

void GameScene::Draw()
{
	DrawFormatString(0, 0, 0xffffff, "GameScene",true);
	DrawBox(100, 100, 200, 200, 0xffff00, true);
}

