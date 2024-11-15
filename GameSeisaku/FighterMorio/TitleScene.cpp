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
	DrawFormatString(0, 0, 0xffffff, "TitleScene", true);
	DrawRotaGraph(640, 300, 0.8 , 0 , m_Graph,TRUE);
//	DrawBox(100, 100, 640, 640,0x00aaaa, true);
}