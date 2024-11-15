#include "GameScene.h"
#include "Game.h"
// #include "GameBg.h"
#include "Map.h"
#include "GameUI.h"
#include "Window.h"
#include "File.h"
#include "Handle.h"

namespace
{
}

GameScene::GameScene() :
	m_stageNum(0),
	m_isTransScene(false),
	m_alpha(0),
	m_timePos(Game::kScreenWidth * 0.8f, 80),
	m_time(0),
	m_timeWidth(0),
	m_sumTime(0),
	m_isTimeAttack(0),
	m_isPause(false),
	m_isSetting(false),
	m_isRastHit(false),
	m_keyTimer(60),
	m_isBackScene(false),
	m_UpdateTimer(0),
	m_incitePos(Game::kScreenWidth * 0.8f, Game::kScreenHeight * 0.4f)
{
	// a = new GameBg;
	m_pMap = new Map;
	m_pUI = new GameUI;
	m_pWindow = new Window;
}

GameScene::~GameScene()
{
	// delete a;
	// a = nullptr;
	delete m_pMap;
	m_pMap = nullptr;
	delete m_pUI;
	m_pUI = nullptr;
	delete m_pWindow;
	m_pWindow = nullptr;
}

void GameScene::Init(int stageNum, int gameMode, int light, int BGM, int SE, const Handle& handle)
{
	m_stageNum = stageNum;
	m_isTimeAttack = gameMode;
	this->SetUti(BGM, SE, light);
	// SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alpha);
	m_pMap->Init(m_isTimeAttack, m_stageNum, BGM, SE, handle);
	// UI
	m_pUI->Init(m_isTimeAttack);
	m_pUI->stageNum = m_stageNum;
	// ポーズ
	m_pWindow->Init(handle);
}

void GameScene::StageUpdate(const Handle& handle)
{
	if (m_pMap != nullptr)
	{
		if (m_pMap->GetTransFlag())
		{
			m_sumTime += m_time;
			if (m_isTimeAttack == 0)
			{
				

				delete m_pMap;
				m_pMap = nullptr;
				m_alpha = 0;
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alpha);
				if (m_stageNum < Game::kStageNum - 1)
				{
					m_stageNum++;
					m_pMap = new Map;
					m_pMap->Init(m_isTimeAttack, m_stageNum, m_pWindow->GetBGM(), m_pWindow->GetSE(), handle);
					m_pUI->stageNum = m_stageNum;
				}
				else
				{
					m_stageNum = 0;
					m_isTransScene = true;
				}
			}
			// ステージ選択時
			else if(m_isTimeAttack == 1)
			{
				delete m_pMap;
				m_pMap = nullptr;
				m_alpha = 0;
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alpha);
				m_stageNum = 0;
				m_isTransScene = true;
			}
		}
	}
}

void GameScene::Update()
{
	// a->Update();
	// 入力
	int pad = GetJoypadInputState(DX_INPUT_PAD1);
	int hitESC = CheckHitKey(KEY_INPUT_ESCAPE);

	// ポーズ画面動作
	if (m_pMap != nullptr)
	{
		// 音量更新
		m_pMap->SetSound(m_pWindow->GetBGM(), m_pWindow->GetSE());

		m_pMap->Update(m_pWindow->GetPause());
		
		m_isBackScene = m_pWindow->GetBackTitle();

		m_time = m_pMap->GetTime();

		// 連続ポーズ防止
		if ((hitESC || pad == PAD_INPUT_8) && !m_isRastHit && m_keyTimer > 60 && !m_pWindow->GetSettingFlag())
		{
			m_keyTimer = 0;
			m_isPause = true;
		}
		//　直前フレームの入力判定
		if (hitESC || pad == PAD_INPUT_8) m_isRastHit = true;
		else m_isRastHit = false;

		// ポーズ画面のupdate
		if (m_isPause && !m_isSetting) m_pWindow->Pause(m_isPause);
		else if (m_isSetting) m_pWindow->Setting();
		else m_pWindow->Close();

		// ポーズ閉じた瞬間ポーズを防止
		if (m_isPause && !m_pWindow->GetPause())
			m_keyTimer = 0;

		// フラグ受け取りfalse化
		m_isPause = m_pWindow->GetPause();
		m_isSetting = m_pWindow->GetSettingFlag();
	}
	m_keyTimer++;
}

void GameScene::Draw(const Handle& handle)
{
	// a->Draw();
	if (m_pMap != nullptr)
	{
		if (m_alpha < 255)
		{
			m_alpha += 17;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alpha);
		}

		

		m_pMap->Draw(handle);
		// UI
		m_pUI->Draw(handle);

		

		DrawFormatStringToHandle(static_cast<int>(m_timePos.x), static_cast<int>(m_timePos.y), 0xff4e4e, handle.h_data.hf_util_32, "移動回数：%d  ",m_time);

		if (m_time >= 300 && m_time < 500)
		{
			DrawStringToHandle(static_cast<int>(m_incitePos.x), static_cast<int>(m_incitePos.y), "苦戦してますねぇ...  ", 0xff4e4e, handle.h_data.hf_util_16);
		}
		if (m_time >= 500 && m_time < 1000)
		{
			DrawStringToHandle(static_cast<int>(m_incitePos.x), static_cast<int>(m_incitePos.y), "そんなにむずかしくしたっけ...?  ", 0xff4e4e, handle.h_data.hf_util_16);
		}
		if (m_time >= 1000 && m_time < 1500)
		{
			DrawStringToHandle(static_cast<int>(m_incitePos.x), static_cast<int>(m_incitePos.y), "もしかしてここで遊んでる...?  ", 0xff4e4e, handle.h_data.hf_util_16);
		}
		if (m_time >= 1500 && m_time < 2000)
		{
			DrawStringToHandle(static_cast<int>(m_incitePos.x), static_cast<int>(m_incitePos.y), "指疲れてるでしょ...  ", 0xff4e4e, handle.h_data.hf_util_16);
		}
		if (m_time >= 2000 && m_time < 10000)
		{
			DrawStringToHandle(static_cast<int>(m_incitePos.x), static_cast<int>(m_incitePos.y), "もう書くこと無いよ...\n頑張ったな...  ", 0xff4e4e, handle.h_data.hf_util_16);
		}
		if (m_time >= 10000)
		{
			DrawStringToHandle(static_cast<int>(m_incitePos.x), static_cast<int>(m_incitePos.y), "いや、さすがにドン引きだよ...\nほんとにもうこれ以上は無いよ...  ", 0xff4e4e, handle.h_data.hf_util_16);
		}
		
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_pMap->GetAlpha());
		DrawBox(0, 0, Game::kScreenWidth + 1, Game::kScreenHeight + 1, 0x000000, true);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

		m_pWindow->WindowDraw(handle);
	}
}

int GameScene::GetBGM() const
{
	return m_pWindow->GetBGM();
}

int GameScene::GetSE() const
{
	return m_pWindow->GetSE();
}

int GameScene::GetLight() const
{
	return m_pWindow->GetLight();
}

void GameScene::SetUti(int BGM, int SE, int light)
{
	m_pWindow->SetSetting(BGM, SE, light);
}
