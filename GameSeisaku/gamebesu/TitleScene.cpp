#include "TitleScene.h"
#include "SceneManager.h"
#include "StageSelectionScene.h"

#include "DxLib.h"

TitleScene::TitleScene(SceneManager& manager) : BaseScene(manager)
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Init()
{
}

void TitleScene::Update()
{
	if (CheckHitKey(KEY_INPUT_Z) == 1)
	{
		auto next = std::make_shared<StageSelectionScene>(m_sceneManager);
		m_sceneManager.ChangeScene(next);
	}
}

void TitleScene::Draw()
{
	DrawFormatString(0, 0, 0xffffff, "TitleScene", true);
	DrawBox(100, 100, 200, 200,0x00ffff, true);
}
