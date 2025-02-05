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
	m_Graph(0),
	m_TitleStart(0),
	m_BrinkCounter(0)
{
}

TitleScene::~TitleScene()
{
	DeleteGraph(m_Graph);
	DeleteGraph(m_TitleStart);
	delete m_pTitlePlayMovie;
}

void TitleScene::Init()
{
	m_Graph = LoadGraph("data/image/FighterMorio.png");
	m_TitleStart = LoadGraph("data/image/TitleUIStart_A.png");
	if (m_pTitlePlayMovie != nullptr)
	{
		m_pTitlePlayMovie->Init();
	}
}

void TitleScene::Update()
{
	Pad::Update();
	// ���͏�Ԃ��X�V
	auto input = GetJoypadInputState(DX_INPUT_KEY_PAD1);

#ifdef _DEBUG
	if (Pad::IsTrigger(input & PAD_INPUT_L))
	{
		m_pTitlePlayMovie->SetPlaySwitch(true);
		auto next = std::make_shared<StageSelectionScene>(m_sceneManager);
		m_sceneManager.ChangeScene(next);
		return;
	}
#else	//_DEBUG
	if (Pad::IsTrigger(input & PAD_INPUT_A))
	{
		m_pTitlePlayMovie->SetPlaySwitch(true);
		auto next = std::make_shared<GameScene_1>(m_sceneManager);
		m_sceneManager.ChangeScene(next);
		return;
	}
#endif  //_DEBUG

	if (m_pTitlePlayMovie != nullptr)
	{
		m_pTitlePlayMovie->Update();
	}

	// �_�ŕϐ���1�𑫂�
	m_BrinkCounter++;

	// �_�ŕϐ���60�ɂȂ��Ă�����0�ɂ���
	if (m_BrinkCounter == 60)
	{
		m_BrinkCounter = 0;
	}
}

void TitleScene::Draw()
{
	if (m_pTitlePlayMovie != nullptr)
	{
		m_pTitlePlayMovie->Draw();
	}
#ifdef _DEBUG
	DrawBox(0, 0, 1280, 640, 0x999999, true);
	DrawFormatString(0, 0, 0xffffff, "TitleScene", true);
	DrawFormatString(550, 500, 0xffffff, "A�L�[�������Ă�������", true);
	DrawFormatString(550, 516, 0xffffff, "Y�{�^���������Ă�������", true);
	DrawRotaGraph(640, 200, 1.0, 0, m_Graph, TRUE);
#else	 //_DEBUG
	DrawRotaGraph(640, 200, 1.0, 0, m_Graph, TRUE);
#endif  //__DEBUG
	// �_�ŗp�̕ϐ��̒l�� 30 �����̂Ƃ������`�悷��
	if (m_BrinkCounter < 30)
	{
		DrawRotaGraph(640, 500, 0.5, 0, m_TitleStart, TRUE);
	}
}