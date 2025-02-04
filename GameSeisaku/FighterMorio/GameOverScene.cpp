#include "GameOverScene.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "GameScene_1.h"

#include "DxLib.h"
#include "Pad.h"
#include "Debug.h"

#include "GameOver.h"
#include "SceneChange.h"


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
	// ���͏�Ԃ��X�V
	auto input = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	m_pGameOver->Update();

	// ������x
	if (Pad::IsTrigger(input & PAD_INPUT_A))
	{
		auto next = std::make_shared<GameScene_1>(m_sceneManager);
		m_sceneManager.ChangeScene(next);
	}

	// �^�C�g����ʂɖ߂�
	if (Pad::IsTrigger(input & PAD_INPUT_B))
	{
		auto next = std::make_shared<TitleScene>(m_sceneManager);
		m_sceneManager.ChangeScene(next);
	}
#ifdef _DEBUG
	// �^�C�g����ʂɖ߂�
	if (Pad::IsTrigger(input & PAD_INPUT_L))
	{
		auto next = std::make_shared<TitleScene>(m_sceneManager);
		m_sceneManager.ChangeScene(next);
	}
#endif // _DEBUG

}

void GameOverScene::Draw()
{
	m_pGameOver->Draw();
}
