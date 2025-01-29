#include "GameOverScene.h"
#include "SceneManager.h"
#include "TitleScene.h"

#include "DxLib.h"
#include "Pad.h"
#include "Debug.h"

#include "GameOver.h"


GameOverScene::GameOverScene(SceneManager& manager) : BaseScene(manager),
m_pGameOver(new GameOver())
{
}

GameOverScene::~GameOverScene()
{
}

void GameOverScene::Init()
{
	m_pGameOver->Init();
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
	m_pGameOver->Update();
}

void GameOverScene::Draw()
{
	m_pGameOver->Draw();
}
