#include <iostream>
#include <string>
#include "TitleScene.h"
#include "DxLib.h"
#include "Game.h"
#include "Window.h"
#include "Sound.h"
#include "Handle.h"

using namespace std;

namespace
{
	constexpr int kMenuMoveValueY = 40;
}

TitleScene::TitleScene() :
	m_titleWidth(0),
	m_startWidth(0),
	m_selectWidth(0),
	m_alpha(0),
	m_isAlpha(false),
	m_appStartTimer(0),
	m_appSelectTimer(0),
	m_isKey(false),
	m_isTransScene(false),
	m_startNum(1),
	m_isRastHit(false),
	m_gameMode(0),
	m_menuNum(0),
	m_cursorMove(0),
	m_cursorMoveVec(1),
	m_isEnd(false),
	m_isMaker(false),
	m_isSetting(false),
	m_isCredit(false),
	m_isWindow(false)
{
	m_pWindow = new Window;
	m_pos = { (Game::kScreenWidth * 0.5f), 0.0f};
	m_cursorPos = { 0,0 };
	m_pSound.resize(3);
	for (int i = 0; i < m_pSound.size(); i++)
	{
		m_pSound[i] = new Sound;
	}
	

	//Bg関連
	m_bg.resize(9);
	for (int i = 0; i < 9; i++)
	{
		m_bg[i].m_bgPos = { static_cast<float>(GetRand(1800) - 100),-100.0f };
		m_bg[i].m_isLight = false;
		if(GetRand(1) == 0)
			m_bg[i].m_bgLightMove = { 10.0f, 20.0f };
		else
			m_bg[i].m_bgLightMove = { - 10.0f, 20.0f };
		m_bg[i].m_moveTimer = GetRand(15);;

		m_bg[i].m_wavePos = { 0,0 };
		m_bg[i].m_isWave = false;
		m_bg[i].m_waveDir = 0;

		// 色
		if (i % 3 == 0) m_bg[i].m_bgColor = 0xff69b4;
		else if(i % 3 == 1) m_bg[i].m_bgColor = 0x39ff14;
		else m_bg[i].m_bgColor = 0x00aeef;
		// タイマー
		m_bg[i].m_bgCoolTimer = i * 30;
	}
	
}

TitleScene::~TitleScene()
{
	delete m_pWindow;
	m_pWindow = nullptr;
	m_pSound[0]->Stop();
	for (int i = 0; i < m_pSound.size(); i++)
	{
		delete m_pSound[i];
		m_pSound[i] = nullptr;
	}
}

void TitleScene::Init( int light, int BGM, int SE, const Handle& handle)
{
	this->SetUti(BGM, SE,light);
	if(m_titleWidth < 0) m_titleWidth = GetDrawStringWidth("Color Dust", static_cast<int>(strlen("Color Dust")));
	m_startWidth = GetDrawStringWidth("MODE:[↑↓]  SELECT[← →]  START:[SPACE]", static_cast<int>(strlen("MODE:[↑↓]  SELECT[← →]  START:[SPACE]")));
	m_selectWidth = 400;

	m_cursorPos.x = m_pos.x - (m_selectWidth * 0.5f) - 15;
	m_pWindow->Init(handle);

	
	
	// タイトルBGM
	m_pSound[0]->InitBGM(handle.h_data.hm_B_0);
	// カーソル音
	m_pSound[1]->InitSE(handle.h_data.hm_S_00);
	// 決定音
	m_pSound[2]->InitSE(handle.h_data.hm_S_01);

	// 音量更新
	for (int i = 0; i < m_pSound.size(); i++)
	{
		if (i == 0) m_pSound[i]->UpdateBGM(BGM);
		else m_pSound[i]->UpdateSE(SE);
	}

	m_pSound[0]->LoopPlay();
}

void TitleScene::Update()
{
	// 音量更新
	for (int i = 0; i < m_pSound.size(); i++)
	{
		if (i == 0) m_pSound[i]->UpdateBGM(m_pWindow->GetBGM());
		else m_pSound[i]->UpdateSE(m_pWindow->GetSE());
	}

	// メニュー選択　十字上下キー
	int pad = GetJoypadInputState(DX_INPUT_PAD1);
	// 上
	int hitU = CheckHitKey(KEY_INPUT_UP); 
	int hitD = CheckHitKey(KEY_INPUT_DOWN);
	// ステージ選択　十字左右キー
	int hitL = CheckHitKey(KEY_INPUT_LEFT);
	int hitR = CheckHitKey(KEY_INPUT_RIGHT);

	// 決定　スペースキー
	int hitSpace = CheckHitKey(KEY_INPUT_SPACE);

	//////////////////////
	// 初期フェードイン //
	//////////////////////

	// タイトル位置下げ
	if (m_pos.y < Game::kScreenHeight * 0.25f)
	{
		m_pos.y += 2.0f;
	}
	// タイトル出し途中のアルファ
	if (m_alpha < 255 && !m_isKey)
	{
		m_alpha++;
	}
	// タイトルフェードインのショートカット
	if (m_pos.y > 2.0f && m_alpha > 1)
	{
		if ((hitSpace || pad == PAD_INPUT_1) && !m_isRastHit && !m_isAlpha)
		{
			m_pos.y = Game::kScreenHeight * 0.25f;
			m_alpha = 255;
			m_isRastHit = true;
		}
	}
	// メニューを表示させるフラグ
	if (m_alpha >= 255) m_isAlpha = true;


	//////////////
	// キー入力 //
	//////////////

	// フェードイン後から操作可能
	if (m_isAlpha && !m_isRastHit && !m_isKey)
	{
		// ウィンドウが出ているときはタイトル操作しない
		if (!m_isWindow)
		{
			// メニュー選択　上下キー
			if (hitU || pad == PAD_INPUT_UP)
			{
				m_pSound[1]->OnePlay();
				m_pSound[1]->OnePlay();
				m_pSound[1]->OnePlay();
				if (m_menuNum > 0) m_menuNum--;
				else m_menuNum = 4;
			}
			if (hitD || pad == PAD_INPUT_DOWN)
			{
				m_pSound[1]->OnePlay();
				m_pSound[1]->OnePlay();
				m_pSound[1]->OnePlay();
				if (m_menuNum < 4) m_menuNum++;
				else m_menuNum = 0;
			}
			// ステージ選択　左右キー　(選択スタートにカーソル合わせた時のみ)
			if (m_menuNum == 1)
			{
				if (hitR || pad == PAD_INPUT_RIGHT)
				{
					m_pSound[1]->OnePlay();
					m_pSound[1]->OnePlay();
					m_pSound[1]->OnePlay();
					if (m_startNum < Game::kStageNum - 1)m_startNum++;
					else m_startNum = 1;
				}
				if (hitL || pad == PAD_INPUT_LEFT)
				{
					m_pSound[1]->OnePlay();
					m_pSound[1]->OnePlay();
					m_pSound[1]->OnePlay();
					if (m_startNum > 1)m_startNum--;
					else m_startNum = Game::kStageNum - 1;
				}
			}
			// 各メニュー操作
			if (m_menuNum == 0)
			{
				// TAモード
				m_gameMode = 0;
				// カーソル位置移動
				m_cursorPos.y = m_pos.y + 350 + (kMenuMoveValueY * m_menuNum) + 12;
				if (hitSpace || pad == PAD_INPUT_1)
				{
					m_pSound[2]->OnePlay();
					m_isKey = true;
				}
			}
			else if (m_menuNum == 1)
			{
				// 選択モード
				m_gameMode = 1;
				m_cursorPos.y = m_pos.y + 350 + (kMenuMoveValueY *m_menuNum) + 12;
				if (hitSpace || pad == PAD_INPUT_1)
				{
					m_pSound[2]->OnePlay();
					m_isKey = true;
				}
			}
			/*
			else if (m_menuNum == 2)				// メーカーモード
			{
				m_gameMode = 2;
				m_cursorPos.y = m_pos.y + 350 + (kMenuMoveValueY * m_menuNum) + 12;
				if (hitSpace)
				{
					m_pSound[2]->OnePlay();
					m_isMaker = true;
				}
			}
			*/
			else if (m_menuNum == 2)
			{
				m_cursorPos.y = m_pos.y + 350 + (kMenuMoveValueY * m_menuNum) + 12;
				// 設定ウインドウ表示
				if (hitSpace || pad == PAD_INPUT_1)
				{
					m_pSound[2]->OnePlay();
					m_isSetting = true;
				}
			}
			else if (m_menuNum == 3)
			{
				m_cursorPos.y = m_pos.y + 350 + (kMenuMoveValueY * m_menuNum) + 12;
				// 終了フラグ
				if (hitSpace || pad == PAD_INPUT_1)
				{
					m_pSound[2]->OnePlay();
					m_isEnd = true;
				}
			}
			else if (m_menuNum == 4)
			{
				m_cursorPos.y = m_pos.y + 350 + (kMenuMoveValueY * m_menuNum) + 12;
				// 権利表記ウインドウ表示
				if (hitSpace || pad == PAD_INPUT_1)
				{
					m_pSound[2]->OnePlay();
					m_isCredit = true;
				}
			}
		}

		// ウインドウが出ているか
		if (m_isMaker || m_isSetting || m_isCredit)m_isWindow = true;
		else m_isWindow = false;

		// ウインドウ表示
		if (m_isMaker) m_pWindow->Maker();
		else if (m_isSetting) m_pWindow->Setting();
		else if (m_isCredit) m_pWindow->Credit();
		else m_pWindow->Close();

		// ウインドウ消えた時にfalse化
		if (m_pWindow->GetGoMakeFlag())
		{
			m_isWindow = false;
			m_isKey = true;
		}
		m_isMaker = m_pWindow->GetMakerFlag();
		m_isSetting = m_pWindow->GetSettingFlag();
		m_isCredit = m_pWindow->GetCreditFlag();
	}
	// 直前フレームでのキー押し判定
	if (hitU || hitD || hitL || hitR || hitSpace || pad) m_isRastHit = true;
	else m_isRastHit = false;

	// ステージ選択時のアニメーション
	if (m_cursorMove >= 10)
		m_cursorMoveVec = -1;
	if (m_cursorMove <= 0)
		m_cursorMoveVec = 1;
	m_cursorMove += m_cursorMoveVec;

	////////////////////////
	// フェードアウト処理 //
	////////////////////////

	if (!m_isWindow && m_appStartTimer < 120)
	{
		if (m_isKey)
		{
			m_appStartTimer += 12;
			if (m_alpha > 0) m_alpha -= 5;
			else m_isTransScene = true;
		}
	}
	else m_appStartTimer = 0;

	// bg
	for (int i = 0; i < 9; i++)
	{
		// 動作開始
		if(m_bg[i].m_bgCoolTimer > 300)
		{
			m_bg[i].m_bgPos += m_bg[i].m_bgLightMove;

			// 30フレームごとにx進行方向反転
			if (m_bg[i].m_moveTimer > 40)
			{
				m_bg[i].m_moveTimer = GetRand(15);
				m_bg[i].m_bgLightMove.x = - m_bg[i].m_bgLightMove.x;
				m_bg[i].m_isWave = true;
				m_bg[i].m_waveDir = 0;
				m_bg[i].m_wavePos = m_bg[i].m_bgPos;
			}
			else m_bg[i].m_moveTimer++;
		}
		

		// 場外なら初期位置を再設定
		if (m_bg[i].m_bgPos.y > 930 || m_bg[i].m_bgPos.x < -30 || m_bg[i].m_bgPos.x > Game::kScreenWidth +30)
		{
			m_bg[i].m_bgPos = { static_cast<float>(GetRand(1800) - 100), -100.0f };
			if (GetRand(1) == 0)
				m_bg[i].m_bgLightMove = { 10.0f, 20.0f };
			else
				m_bg[i].m_bgLightMove = { -10.0f, 20.0f };
			m_bg[i].m_bgCoolTimer = 0;
		}

		if (m_bg[i].m_isWave)
		{
			if (m_bg[i].m_waveDir < 200)
				m_bg[i].m_waveDir += 6;
			else
			{
				m_bg[i].m_waveDir = 0;
				m_bg[i].m_isWave = false;
			}
		}

		// タイマー
		m_bg[i].m_bgCoolTimer++;
	}
}



void TitleScene::Draw(const Handle& handle)
{
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alpha);
	// Bg
	for (int i = 0; i < 9; i++)
	{
		DrawCircle(static_cast<int>(m_bg[i].m_bgPos.x), static_cast<int>(m_bg[i].m_bgPos.y), 6, m_bg[i].m_bgColor, true);
		if (m_bg[i].m_isWave)
		{
			if(m_alpha > 255 - (m_bg[i].m_waveDir * 2 - (400 - 255)))
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - (m_bg[i].m_waveDir * 2 - (400-255)));
			DrawCircle(static_cast<int>(m_bg[i].m_wavePos.x), static_cast<int>(m_bg[i].m_wavePos.y), m_bg[i].m_waveDir, m_bg[i].m_bgColor, false);
		}
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alpha);

	//// タイトル
	//DrawExtendGraph(static_cast<int>(m_pos.x - (m_titleWidth * 0.5f) - 400), static_cast<int>(m_pos.y - 150),
	//	static_cast<int>(m_pos.x - (m_titleWidth * 0.5f) + 400), static_cast<int>(m_pos.y + 250),
	//	handle.h_data.hi_logoBg, true);


	DrawExtendGraph(static_cast<int>(m_pos.x - (m_titleWidth * 0.5f) - 400), static_cast<int>(m_pos.y - 150),
		static_cast<int>(m_pos.x - (m_titleWidth * 0.5f) + 400), static_cast<int>(m_pos.y + 250),
		handle.h_data.hi_logoBg, true);

	// ChangeFontFromHandle(m_backTitleFont);
	DrawStringToHandle(static_cast<int>(m_pos.x - (m_titleWidth * 0.5f) - 240), static_cast<int>(m_pos.y + 15), "Glow  Ruler", 0x101010, handle.h_data.hf_backTitle,0x303030);
	// ChangeFontFromHandle(m_titleFont);
	DrawStringToHandle(static_cast<int>(m_pos.x - (m_titleWidth * 0.5f) - 250), static_cast<int>(m_pos.y), "Glow  Ruler", 0xffffff, handle.h_data.hf_title);
	// ChangeFontFromHandle(m_otherFont);
	
	// タイトルメニュー
	if (m_isAlpha) // if (a >= 255) だと、フェードアウトしない
	{
		
		// 操作
		DrawStringToHandle(static_cast<int>(Game::kScreenWidth - 550), static_cast<int>(m_pos.y) + 570, "操作：", 0xffffff, handle.h_data.hf_util_32);
		DrawStringToHandle(static_cast<int>(Game::kScreenWidth - 450), static_cast<int>(m_pos.y) + 550, "　↑　\n←↓→", 0xffffff, handle.h_data.hf_util_32);
		DrawStringToHandle(static_cast<int>(Game::kScreenWidth - 340), static_cast<int>(m_pos.y) + 570, "決定：SPACE or A", 0xffffff, handle.h_data.hf_util_32);
		// カーソル
		/*DrawTriangle(static_cast<int>(m_cursorPos.x + 6 - 150), static_cast<int>(m_cursorPos.y),
					static_cast<int>(m_cursorPos.x - 2 - 150),static_cast<int>(m_cursorPos.y + 4),
					static_cast<int>(m_cursorPos.x - 2 - 150), static_cast<int>(m_cursorPos.y - 4),
					0xF8E559, true);*/

		// タイムアタック
		if (m_menuNum == 0 && m_appStartTimer < 60) // 選択時
			DrawString(static_cast<int>(m_pos.x - (m_selectWidth * 0.5f) - 250), static_cast<int>(m_pos.y) + 300 + 35* m_menuNum, "ランキング チャレンジ", 0xe04000, 0xddc000);
		else if (m_menuNum == 0)					// 選択時＋決定時
		{
			DrawString(static_cast<int>(m_pos.x - (m_selectWidth * 0.5f) - 250), static_cast<int>(m_pos.y) + 300 + 35 * m_menuNum, "ランキング チャレンジ", 0xe04000, 0xb0b0b0);
		}
		else										// 未選択時
			DrawString(static_cast<int>(m_pos.x - (m_selectWidth * 0.5f) - 220), static_cast<int>(m_pos.y) + 300 + 35 * 0, "ランキング チャレンジ", 0xe04000, 0xb0b0b0);
		

		// ステージ選択
		if (m_menuNum == 1 && m_appStartTimer < 60) // 選択時
		{
			DrawString(static_cast<int>(m_pos.x - (m_selectWidth * 0.5f) - 250), static_cast<int>(m_pos.y) + 300 + 35 * m_menuNum, "セレクトステージ", 0xe04000, 0xddc000);
			DrawFormatString2F(m_pos.x - 40 - m_cursorMove, m_pos.y + 300 + 35 * m_menuNum, 0xe04000, 0xddc000, "＜");
			DrawFormatString2F(m_pos.x, m_pos.y + 300 + 35 * m_menuNum, 0xe04000, 0xddc000, "[");
			if(m_startNum < 10)
				DrawFormatString2F(m_pos.x + 40, m_pos.y + 300 + 35 * m_menuNum, 0xe04000, 0xddc000, "%d", m_startNum);
			else
				DrawFormatString2F(m_pos.x + 35, m_pos.y + 300 + 35 * m_menuNum, 0xe04000, 0xddc000, "%d", m_startNum);
			DrawFormatString2F(m_pos.x + 85, m_pos.y + 300 + 35 * m_menuNum, 0xe04000, 0xddc000, "]　 ( 1 ～ %d )", Game::kStageNum - 1);
			DrawFormatString2F(m_pos.x + 85 + 10 + m_cursorMove, m_pos.y + 300 + 35 * m_menuNum, 0xe04000, 0xddc000, "＞");
		}
		else if (m_menuNum == 1)					// 選択時＋決定時
		{
			DrawString(static_cast<int>(m_pos.x - (m_selectWidth * 0.5f) - 250), static_cast<int>(m_pos.y) + 300 + 35 * m_menuNum, "セレクトステージ", 0xe04000, 0xb0b0b0);
			DrawFormatString2F(m_pos.x - 40 - m_cursorMove, m_pos.y + 300 + 35 * m_menuNum, 0xe04000, 0xb0b0b0, "＜");
			DrawFormatString2F(m_pos.x, m_pos.y + 300 + 35 * m_menuNum, 0xe04000, 0xb0b0b0, "[");
			if (m_startNum < 10)
				DrawFormatString2F(m_pos.x + 40, m_pos.y + 300 + 35 * m_menuNum, 0xe04000, 0xb0b0b0, "%d", m_startNum);
			else
				DrawFormatString2F(m_pos.x + 35, m_pos.y + 300 + 35 * m_menuNum, 0xe04000, 0xb0b0b0, "%d", m_startNum);
			DrawFormatString2F(m_pos.x + 85, m_pos.y + 300 + 35 * m_menuNum, 0xe04000, 0xb0b0b0, "]　 ( 1 ～ %d )", Game::kStageNum - 1);
			DrawFormatString2F(m_pos.x + 85 + 10 + m_cursorMove, m_pos.y + 300 + 35 * m_menuNum, 0xe04000, 0xb0b0b0, "＞");
		}
		else										// 未選択時
		{
			DrawString(static_cast<int>(m_pos.x - (m_selectWidth * 0.5f) - 220), static_cast<int>(m_pos.y) + 300 + 35 * 1, "セレクトステージ", 0xe04000, 0xb0b0b0);
			DrawFormatString2F(m_pos.x , m_pos.y + 300 + 35 * 1, 0xe04000, 0xb0b0b0, "[");
			if (m_startNum < 10)
				DrawFormatString2F(m_pos.x + 40, m_pos.y + 300 + 35 * 1, 0xe04000, 0xb0b0b0, "%d", m_startNum);
			else
				DrawFormatString2F(m_pos.x + 35, m_pos.y + 300 + 35 * 1, 0xe04000, 0xb0b0b0, "%d", m_startNum);
			DrawFormatString2F(m_pos.x + 85, m_pos.y + 300 + 35 * 1, 0xe04000, 0xb0b0b0, "]　 ( 1 ～ %d )", Game::kStageNum - 1);
		}

		/*
		// メーカー
		if (m_menuNum == 2 && m_appStartTimer < 60) // 選択時
			DrawString(static_cast<int>(m_pos.x - (m_selectWidth * 0.5f) - 170), static_cast<int>(m_pos.y) + 430, "ステージメーカー", 0xe04000, 0xddc000);
		else if (m_menuNum == 2)					// 選択時＋決定時
			DrawString(static_cast<int>(m_pos.x - (m_selectWidth * 0.5f) - 170), static_cast<int>(m_pos.y) + 350, "ステージメーカー", 0xe04000, 0xb0b0b0);
		else										// 未選択時
			DrawString(static_cast<int>(m_pos.x - (m_selectWidth * 0.5f) - 150), static_cast<int>(m_pos.y) + 430, "ステージメーカー", 0xe04000, 0xb0b0b0);
		*/

		// 設定
		if (m_menuNum == 2 && m_appStartTimer < 60) // 選択時
			DrawString(static_cast<int>(m_pos.x - (m_selectWidth * 0.5f) - 250), static_cast<int>(m_pos.y) + 300 + 35 * m_menuNum, "設定", 0xe04000, 0xddc000);
		else if (m_menuNum == 2)					// 選択時＋決定時
			DrawString(static_cast<int>(m_pos.x - (m_selectWidth * 0.5f) - 250), static_cast<int>(m_pos.y) + 300 + 35 * m_menuNum, "設定", 0xe04000, 0xb0b0b0);
		else										// 未選択時
			DrawString(static_cast<int>(m_pos.x - (m_selectWidth * 0.5f) - 220), static_cast<int>(m_pos.y) + 300 + 35 * 2, "設定", 0xe04000, 0xb0b0b0);


		// ゲーム終了
		if (m_menuNum == 3 && m_appStartTimer < 60) // 選択時
			DrawString(static_cast<int>(m_pos.x - (m_selectWidth * 0.5f) - 250), static_cast<int>(m_pos.y) + 300 + 35 * m_menuNum, "終了", 0xe04000, 0xddc000);
		else if (m_menuNum == 3)					// 選択時＋決定時
			DrawString(static_cast<int>(m_pos.x - (m_selectWidth * 0.5f) - 250), static_cast<int>(m_pos.y) + 300 + 35 * m_menuNum, "終了", 0xe04000, 0xb0b0b0);
		else										// 未選択時
			DrawString(static_cast<int>(m_pos.x - (m_selectWidth * 0.5f) - 220), static_cast<int>(m_pos.y) + 300 + 35 * 3, "終了", 0xe04000, 0xb0b0b0);


		// 権利表記
		if (m_menuNum == 4 && m_appStartTimer < 60) // 選択時
			DrawString(static_cast<int>(m_pos.x - (m_selectWidth * 0.5f) - 250), static_cast<int>(m_pos.y) + 300 + 35 * m_menuNum, "クレジット", 0xe04000, 0xddc000);
		else if (m_menuNum == 4)					// 選択時＋決定時
			DrawString(static_cast<int>(m_pos.x - (m_selectWidth * 0.5f) - 250), static_cast<int>(m_pos.y) + 300 + 35 * m_menuNum, "クレジット", 0xe04000, 0xb0b0b0);
		else										// 未選択時
			DrawString(static_cast<int>(m_pos.x - (m_selectWidth * 0.5f) - 220), static_cast<int>(m_pos.y) + 300 + 35 * 4, "クレジット", 0xe04000, 0xb0b0b0);
		
		m_pWindow->WindowDraw(handle);
		
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - m_alpha);
		DrawBox(0, 0, Game::kScreenWidth + 1, Game::kScreenHeight + 1, 0x000000, true);

	}
}

int TitleScene::GetLight() const
{
	return m_pWindow->GetLight();
}

int TitleScene::GetBGM() const
{
	return m_pWindow->GetBGM();
}

int TitleScene::GetSE() const
{
	return m_pWindow->GetSE();
}

void TitleScene::SetUti(int BGM, int SE, int light)
{
	m_pWindow->SetSetting(BGM, SE, light);
}
