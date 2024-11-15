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
	if (CheckHitKey(KEY_INPUT_Y) == 1)
	{
		auto next = std::make_shared<GameScene>(m_sceneManager);
		m_sceneManager.ChangeScene(next);
	}
}

void StageSelectionScene::Draw()
{
	DrawFormatString(0, 0, 0xffffff, "StageSelectionScene", true);
	DrawBox(100, 100, 200, 200, 0xff00ff, true);
}
