#include "GameScene_2.h"
#include "SceneManager.h"
#include "TitleScene.h"

#include "DxLib.h"
#include "Pad.h"

GameScene_2::GameScene_2(SceneManager& manager) : BaseScene(manager)
{
}

GameScene_2::~GameScene_2()
{
}

void GameScene_2::Init()
{
}
void GameScene_2::Update()
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

void GameScene_2::Draw()
{
	DrawFormatString(0, 0, 0xffffff, "GameScene_2", true);
	DrawBox(100, 100, 640, 640, 0xaaaaaa, true);
}