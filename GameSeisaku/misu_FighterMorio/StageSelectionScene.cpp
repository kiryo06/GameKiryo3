#include "StageSelectionScene.h"
#include "SceneManager.h"
#include "GameScene.h"

#include "DxLib.h"

StageSelectionScene::StageSelectionScene(SceneManager& manager) : BaseScene(manager)
{
}

StageSelectionScene::~StageSelectionScene()
{
}

void StageSelectionScene::Init()
{
}

void StageSelectionScene::Update()
{
	if (KEY_INPUT_0)
	{
		auto next = std::make_shared<GameScene>(m_sceneManager);
		m_sceneManager.ChangeScene(next);
	}
}

void StageSelectionScene::Draw()
{
	DrawBox(12, 12, 12, 12, 0xff34ff, true);
}
