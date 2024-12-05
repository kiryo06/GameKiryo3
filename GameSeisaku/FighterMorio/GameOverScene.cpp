#include "GameOverScene.h"
#include "SceneManager.h"
#include "TitleScene.h"

#include "DxLib.h"
#include "Pad.h"

GameOverScene::GameOverScene(SceneManager& manager) : BaseScene(manager)
{
}

GameOverScene::~GameOverScene()
{
}

void GameOverScene::Init()
{
}

void GameOverScene::Update()
{
	Pad::Update();
	// “ü—Íó‘Ô‚ğXV
	auto input = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (Pad::IsTrigger(input & PAD_INPUT_X))
	{
		auto next = std::make_shared<TitleScene>(m_sceneManager);
		m_sceneManager.ChangeScene(next);
	}
}

void GameOverScene::Draw()
{
	DrawFormatString(0, 0, 0xffffff, "GameOverScene", true);
	DrawBox(100, 100, 640, 640, 0x3afdaa, true);
}
