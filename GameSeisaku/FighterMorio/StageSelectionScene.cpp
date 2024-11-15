#include "StageSelectionScene.h"
#include "SceneManager.h"
#include "GameScene.h"

#include "DxLib.h"
#include "Pad.h"

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
	Pad::Update();
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		auto next = std::make_shared<GameScene>(m_sceneManager);
		m_sceneManager.ChangeScene(next);
	}
}

void StageSelectionScene::Draw()
{
	DrawFormatString(0, 0, 0xffffff, "StageSelectionScene", true);
	DrawBox(100, 100, 640, 640, 0xaa00aa, true);
}
