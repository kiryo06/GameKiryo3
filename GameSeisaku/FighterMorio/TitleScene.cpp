#include "TitleScene.h"
#include "SceneManager.h"
#include "StageSelectionScene.h"
#include "TitlePlayMovie.h"
#include "GameScene_1.h"

#include "game.h"

#include "DxLib.h"
#include "Pad.h"

TitleScene::TitleScene(SceneManager& manager) : 
	BaseScene(manager),
	m_pTitlePlayMovie(new TitlePlayMovie),
	m_Graph(0)
{
}

TitleScene::~TitleScene()
{
	DeleteGraph(m_Graph);
	delete m_pTitlePlayMovie;
}

void TitleScene::Init()
{
	m_Graph = LoadGraph("data/image/FighterMorio.png");
	if (m_pTitlePlayMovie != nullptr)
	{
		m_pTitlePlayMovie->Init();
	}
}

void TitleScene::Update()
{
	Pad::Update();
	// 入力状態を更新
	auto input = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	if (m_pTitlePlayMovie != nullptr)
	{
		m_pTitlePlayMovie->Update();
	}
#ifdef _DEBUG
	if (Pad::IsTrigger(input & PAD_INPUT_L))
	{
		m_pTitlePlayMovie->SetPlaySwitch(true);
		auto next = std::make_shared<StageSelectionScene>(m_sceneManager);
		m_sceneManager.ChangeScene(next);
	}
#else	//_DEBUG
	if (Pad::IsTrigger(input & PAD_INPUT_C))
	{
		m_pTitlePlayMovie->SetPlaySwitch(true);
		auto next = std::make_shared<GameScene_1>(m_sceneManager);
		m_sceneManager.ChangeScene(next);
	}
#endif  //_DEBUG
}

void TitleScene::Draw()
{
	if (m_pTitlePlayMovie != nullptr)
	{
		m_pTitlePlayMovie->Draw();
	}

#ifdef _DEBUG
	DrawFormatString(0, 0, 0xffffff, "TitleScene", true);
	DrawFormatString(550, 500, 0xffffff, "Aキーを押してください", true);
	DrawFormatString(550, 516, 0xffffff, "Yボタンを押してください", true);
	DrawRotaGraph(640, 200, 1.0, 0, m_Graph, TRUE);
#else	 //_DEBUG
	DrawFormatString(550, 516, 0xffffff, "Xボタンを押してください", true);
	DrawRotaGraph(640, 200, 1.0, 0, m_Graph, TRUE);
#endif  //__DEBUG
}