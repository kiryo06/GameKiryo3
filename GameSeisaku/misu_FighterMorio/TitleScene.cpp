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
	if (KEY_INPUT_0)
	{
		auto next = std::make_shared<StageSelectionScene>(m_sceneManager);
		m_sceneManager.ChangeScene(next);
	}
}

void TitleScene::Draw()
{
	DrawBox(12, 12, 43, 43,0x34ffff, true);
}
