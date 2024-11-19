#include "TitleScene.h"
#include "SceneManager.h"
#include "StageSelectionScene.h"

#include "DxLib.h"
#include "Pad.h"

TitleScene::TitleScene(SceneManager& manager) : 
	BaseScene(manager),
	m_Graph(0)
{
}

TitleScene::~TitleScene()
{
	DeleteGraph(m_Graph);
}

void TitleScene::Init()
{
	m_Graph = LoadGraph("data/image/tekikou_1114.png");
}

void TitleScene::Update()
{
	Pad::Update();
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		auto next = std::make_shared<StageSelectionScene>(m_sceneManager);
		m_sceneManager.ChangeScene(next);
	}
}

void TitleScene::Draw()
{
	DrawBox(0, 0, 1280, 640, 0x00baa0, true);
	DrawFormatString(0, 0, 0xffffff, "TitleScene", true);
	DrawFormatString(550, 500, 0xffffff, "ZÉLÅ[ÇâüÇµÇƒÇ≠ÇæÇ≥Ç¢", true);
	DrawRotaGraph(640, 225, 0.5 , 0 , m_Graph,TRUE);
}