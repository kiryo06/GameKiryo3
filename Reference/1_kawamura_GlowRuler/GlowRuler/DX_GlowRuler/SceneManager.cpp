#include "SceneManager.h"
#include "DxLib.h"
#include "Game.h"
#include "Handle.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "EndingScene.h"
#include "Setting.h"
#include "File.h"
#include "StageMakerScene.h"

SceneManager::SceneManager() :
	m_stageNum(1),
	m_isTransScene(false),
	m_time(0),
	m_gameMode(0),
	m_isEnd(false),
	m_isMaker(false),
	m_lightPow(5),
	m_BGMPow(2),
	m_SEPow(2),
	m_handleNum(0),
	m_handleTimer(0)
{
	m_handleData = new Handle;
	m_dataFile = new File;

	m_pTitle = new TitleScene;
	m_pMaker = nullptr;
	m_pGame = nullptr;
	m_pEnding = nullptr;
	m_pSet = new Uti;
}

SceneManager::~SceneManager()
{
	delete m_handleData;
	m_handleData = nullptr;

	if (m_pTitle != nullptr)
	{
		delete m_pTitle;
		m_pTitle = nullptr;
	}
	if (m_pGame != nullptr)
	{
		delete m_pGame;
		m_pGame = nullptr;
	}
	if (m_pEnding != nullptr)
	{
		delete m_pEnding;
		m_pEnding = nullptr;
	}
	if (m_pMaker != nullptr)
	{
		delete m_pMaker;
		m_pMaker = nullptr;
	}
	delete m_pSet;
	m_pSet = nullptr;

	delete m_dataFile;
	m_dataFile = nullptr;
}

void SceneManager::Init()
{
	m_pSet->SetUti(m_BGMPow, m_SEPow, m_lightPow);
	// タイトルシーンからスタート
	m_pTitle->Init( m_lightPow, m_BGMPow, m_SEPow, *m_handleData);
	ChangeFontFromHandle(m_handleData->h_data.hf_util_32);
}

void SceneManager::SceneMove()
{
	/////////////////////////////////////////////////////////////
	// タイトル→ゲーム→エンディング→タイトル･･･の一連の流れ //
	/////////////////////////////////////////////////////////////
	// 各シーンの遷移判定
	if (m_pTitle != nullptr) m_isTransScene = m_pTitle->GetTransFlag();
	else if (m_pGame != nullptr) m_isTransScene = m_pGame->GetTransFlag();
	else if (m_pEnding != nullptr) m_isTransScene = m_pEnding->GetTransFlag();

	// シーン遷移時起動
	if (m_isTransScene)
	{
		m_isTransScene = false;
		// ゲーム準備
		if (m_pTitle != nullptr)
		{
			// ゲームモードの選択
			m_gameMode = m_pTitle->GetMode();
			// 明るさ
			m_lightPow = m_pTitle->GetLight();
			if (m_gameMode != 2)
			{
				// 選択スタート時、ステージ番号をGET
				if (m_gameMode == 1)
					m_stageNum = m_pTitle->GetStartNum();
				else m_stageNum = 1;
				
				// タイトルメモリ解放
				delete m_pTitle;
				m_pTitle = nullptr;
				// ゲーム準備
				m_pGame = new GameScene;
				m_pGame->Init(m_stageNum, m_gameMode, m_lightPow, m_BGMPow, m_SEPow, *m_handleData);
			}
			// メーカーモード
			else
			{
				// タイトルメモリ解放
				delete m_pTitle;
				m_pTitle = nullptr;
				// メーカー準備
				m_pMaker = new StageMakerScene;
				m_pMaker->Init(m_gameMode);
			}
		}

		// エンディング準備
		else if (m_pGame != nullptr)
		{
			m_time = m_pGame->GetSumTime();
			if (m_gameMode == 0)
			{
				m_dataFile->ChangeTime(m_time);
			}
			Rank timeRank = { m_dataFile->GetTime(0),m_dataFile->GetTime(1),
						m_dataFile->GetTime(2),m_dataFile->GetTime(3),m_dataFile->GetTime(4),};
			// 設定更新
			m_BGMPow = m_pGame->GetBGM();
			m_SEPow = m_pGame->GetSE();
			m_lightPow = m_pGame->GetLight();
			// ゲームメモリ解放
			delete m_pGame;
			m_pGame = nullptr;
			// エンディング準備
			m_pEnding = new EndingScene;
			m_pEnding->Init(m_time, m_gameMode, m_BGMPow, m_SEPow, timeRank, *m_handleData);
		}
		// タイトル準備
		else if (m_pEnding != nullptr)
		{
			// ゲームメモリ解放
			delete m_pEnding;
			m_pEnding = nullptr;
			// エンディング準備
			m_pTitle = new TitleScene;
			m_pTitle->Init(m_lightPow, m_BGMPow, m_SEPow, *m_handleData);
		}
	}
	//////////////////////////////////////////
	// ゲームシーン中にタイトルシーンに戻る //
	//////////////////////////////////////////
	if (m_pGame != nullptr)
	{
		if (m_pGame->GetBackFlag())
		{
			// 設定更新
			m_BGMPow = m_pGame->GetBGM();
			m_SEPow = m_pGame->GetSE();
			m_lightPow = m_pGame->GetLight();

			delete m_pGame;
			m_pGame = nullptr;
			m_pTitle = new TitleScene;
			m_pTitle->Init(m_lightPow, m_BGMPow, m_SEPow, *m_handleData);
		}
	}
	////////////////////////////////
	// メーカーからタイトルに戻る //
	////////////////////////////////
	if (m_pMaker != nullptr)
	{
		if (m_pMaker->GetBackFlag())
		{
			delete m_pMaker;
			m_pMaker = nullptr;
			m_pTitle = new TitleScene;
			m_pTitle->Init(m_lightPow, m_BGMPow, m_SEPow, *m_handleData);
		}
	}

}



void SceneManager::Update()
{
	
	// タイトル
	if (m_pTitle != nullptr)
	{
		// 設定更新
		m_BGMPow = m_pTitle->GetBGM();
		m_SEPow = m_pTitle->GetSE();
		m_lightPow = m_pTitle->GetLight();

		m_pTitle->Update();
		m_isEnd = m_pTitle->GetEndFlag();
	}
	// ゲーム
	if (m_pGame != nullptr)
	{
		// 設定更新
		m_BGMPow = m_pGame->GetBGM();
		m_SEPow = m_pGame->GetSE();
		m_lightPow = m_pGame->GetLight();

		m_pGame->Update();
		m_pGame->StageUpdate(*m_handleData);
	}
	// エンディング
	if (m_pEnding != nullptr) m_pEnding->Update();

	// メーカー
	if (m_pMaker != nullptr) m_pMaker->Update();

	// 各種設定の反映
	m_pSet->SetUti(m_BGMPow, m_SEPow, m_lightPow);
	m_pSet->Update();
}

void SceneManager::Draw()
{
	

	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x1f152d, true);
	// タイトル
	if (m_pTitle != nullptr) m_pTitle->Draw(*m_handleData);
	// ゲーム
	if (m_pGame != nullptr) m_pGame->Draw(*m_handleData);
	// エンディング
	if (m_pEnding != nullptr) m_pEnding->Draw(*m_handleData);

	// メーカー
	if (m_pMaker != nullptr) m_pMaker->Draw(*m_handleData);

	// 画面の明るさ調整
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_pSet->GetLight());
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}
