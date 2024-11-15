#include "SceneManager.h"
#include "TitleScene.h"

SceneManager::SceneManager()
{
	std::shared_ptr<TitleScene>pScene = std::make_shared<TitleScene>(*this);
	m_pScene = pScene;
	m_sceneState = SceneState::Title;
}

SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{
}

void SceneManager::Update()
{
}

void SceneManager::Draw()
{
	m_pScene->Draw();
}

//void SceneManager::ChangeScene(SceneState nextSceneState)
//{
//	if (m_sceneState == nextSceneState)
//	{
//		return;
//	}
//	if (nextSceneState == SceneState::Title)
//	{
//		std::shared_ptr<TitleScene>pScene = std::make_shared<TitleScene>();
//		m_pScene = pScene;
//		m_sceneState = nextSceneState;
//	}
//	if (nextSceneState == SceneState::Game)
//	{
//		std::shared_ptr<TitleScene>pScene = std::make_shared<TitleScene>();
//		m_pScene = pScene;
//		m_sceneState = nextSceneState;
//	}
//}

void SceneManager::ChangeScene(const std::shared_ptr<BaseScene>& next)
{
	m_pScene = next;
}
