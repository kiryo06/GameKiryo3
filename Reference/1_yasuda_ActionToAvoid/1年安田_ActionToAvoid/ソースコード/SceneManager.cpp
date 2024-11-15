#include "SceneManager.h"
#include "Scene.h"

SceneManager::~SceneManager()
{
	delete scene_;
}

void SceneManager::Update(Input& input)
{
	scene_->Update(input);
}

void SceneManager::Draw()
{
	scene_->Draw();
}

void SceneManager::ChangeScene(Scene* nextScene)
{
	if (scene_ != nullptr) {//‘O‚ÌƒV[ƒ“‚ª‚ ‚Á‚½‚ç
		delete scene_;//‰ğ•ú‚µ‚Ä‚¨‚­
	}
	scene_ = nextScene;
}
