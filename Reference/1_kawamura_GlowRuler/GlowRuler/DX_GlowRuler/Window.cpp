#include "Window.h"
#include "DxLib.h"
#include "Game.h"
#include "Sound.h"
#include "Handle.h"

Window::Window() :
	m_menuWidth(0),
	m_menuHeight(0),
	m_BackWidth(700.0f),
	m_isTitle(false),
	m_isAppString(false),
	m_isWindow(false),
	m_isPause(false),
	m_isSetting(false),
	m_isCredit(false),
	m_isMaker(false),
	m_isGoMake(false),
	m_goTimer(0),
	m_isSelect(false),
	m_stageNum(1),
	m_isRastHit(true),
	m_menuNum(0),
	m_keyTimer(0),
	m_BGMSet(2),
	m_isBGM(false),
	m_SESet(2),
	m_isSE(false),
	m_lightSet(5),
	m_islight(false)
{
	m_stringPos = { 700.0f,Game::kScreenHeight * 0.3f };
	m_cursorPos = { m_stringPos.x - 15, m_stringPos.y };

	m_pSound.resize(4);
	for (int i = 0; i < m_pSound.size(); i++)
	{
		m_pSound[i] = new Sound;
	}
	
}

Window::~Window()
{
	for (int i = 0; i < m_pSound.size(); i++)
	{
		delete m_pSound[i];
		m_pSound[i] = nullptr;
	}
}

void Window::Init(const Handle& handle)
{
	// カーソル音
	m_pSound[0]->InitSE(handle.h_data.hm_S_00);
	// 決定音
	m_pSound[1]->InitSE(handle.h_data.hm_S_01);
	// 戻る音
	m_pSound[2]->InitSE(handle.h_data.hm_S_02);
	// ウインドウ音
	m_pSound[3]->InitSE(handle.h_data.hm_S_03);
}

void Window::Open()
{
	
	if (m_menuWidth < static_cast<int>(Game::kScreenWidth * 0.75f))
	{
		if (!m_pSound[3]->ChackPlaying())
		{
			m_pSound[3]->OnePlay();
			m_pSound[3]->OnePlay();
			m_pSound[3]->OnePlay();
		}
		m_menuWidth += static_cast<int>((Game::kScreenWidth * 0.0375f));
	}
	else if (m_menuHeight < static_cast<int>(Game::kScreenHeight * 0.75f))
		m_menuHeight += (static_cast<int>(Game::kScreenHeight * 0.0375f));
	else
	{
		m_isAppString = true;
		m_isWindow = true;
	}
}

void Window::Close()
{
	m_isAppString = false;
	if (m_menuHeight > 0)
	{
		m_isWindow = false;
		if (!m_pSound[3]->ChackPlaying())
		{
			m_pSound[3]->OnePlay();
			m_pSound[3]->OnePlay();
			m_pSound[3]->OnePlay();
		}
		m_menuHeight -= static_cast<int>((Game::kScreenHeight * 0.0375f));
	}
	else if (m_menuWidth > 0)
		m_menuWidth -= static_cast<int>((Game::kScreenWidth * 0.0375f));
}

void Window::WindowDraw(const Handle& handle)
{
	if (m_menuHeight > 0 && m_menuWidth > 0)
	{
		// ウインドウ
		DrawBox(static_cast<int>((Game::kScreenWidth - m_menuWidth) * 0.5f), static_cast<int>((Game::kScreenHeight - m_menuHeight) * 0.5f),
			static_cast<int>((Game::kScreenWidth + m_menuWidth) * 0.5f), static_cast<int>((Game::kScreenHeight + m_menuHeight) * 0.5f),
			0x332941, true);
		// ウインドウ枠
		DrawBox(static_cast<int>((Game::kScreenWidth - m_menuWidth) * 0.5f), static_cast<int>((Game::kScreenHeight - m_menuHeight) * 0.5f),
			static_cast<int>((Game::kScreenWidth + m_menuWidth) * 0.5f), static_cast<int>((Game::kScreenHeight + m_menuHeight) * 0.5f),
			0xF8E559, false);
	}
	

	// ウインドウ画面のstring
	if (m_isAppString)
	{
		// ポーズウインドウ
		if (m_isPause && !m_isSetting)
		{
			if (m_menuNum == 0)
				DrawString(static_cast<int>(m_stringPos.x - 200), static_cast<int>(m_stringPos.y), "設定", 0xe04000, 0xddc000);
			else
				DrawString(static_cast<int>(m_stringPos.x - 200), static_cast<int>(m_stringPos.y), "設定", 0xe04000);

			if (m_menuNum == 1)
				DrawString(static_cast<int>(m_stringPos.x - 200), static_cast<int>(m_stringPos.y + 100), "タイトルへ", 0xe04000, 0xddc000);
			else
				DrawString(static_cast<int>(m_stringPos.x - 200), static_cast<int>(m_stringPos.y + 100), "タイトルへ", 0xe04000);

			// ２は無し

			if (m_menuNum == 3)
				DrawString(static_cast<int>(m_stringPos.x - 200), static_cast<int>(m_stringPos.y + 330), "ゲームにもどる", 0xe04000, 0xddc000);
			else
				DrawString(static_cast<int>(m_stringPos.x - 200), static_cast<int>(m_stringPos.y + 330), "ゲームにもどる", 0xe04000);

		}

		// メーカーウインドウ
		if (m_isMaker)
		{
			DrawString(static_cast<int>(m_stringPos.x - 200), static_cast<int>(m_stringPos.y), "ステージを選択", 0xe04000);

			if (m_menuNum == 1)
				DrawString(static_cast<int>(m_stringPos.x - 200), static_cast<int>(m_stringPos.y + 100), "ステージ", 0xe04000, 0xddc000);
			else
				DrawString(static_cast<int>(m_stringPos.x - 200), static_cast<int>(m_stringPos.y + 100), "ステージ", 0xe04000);

			// ステージ選択
			if (m_isSelect)
			{
				DrawFormatString2F(m_stringPos.x + 100, static_cast<int>(m_stringPos.y + 100), 0xe04000, 0xddc000, " < [ %d ] > ( 1 ～ 10 )", m_stageNum);
			}
			else
			{
				DrawFormatString2F(m_stringPos.x + 100, static_cast<int>(m_stringPos.y + 100), 0xe04000, 0xffffff, "   [ %d ]   ( 1 ～ 10 )", m_stageNum);
			}


			/*if (m_menuNum == 2)
				DrawString(static_cast<int>(m_stringPos.x - 200), static_cast<int>(m_stringPos.y + 200), "IDからあそぶ(未実装)", 0xe04000, 0xddc000);
			else
				DrawString(static_cast<int>(m_stringPos.x - 200), static_cast<int>(m_stringPos.y + 200), "IDからあそぶ(未実装)", 0xe04000);*/


			if (m_menuNum == 3)
				DrawString(static_cast<int>(m_stringPos.x - 200), static_cast<int>(m_stringPos.y + 330), "もどる", 0xe04000, 0xddc000);
			else
				DrawString(static_cast<int>(m_stringPos.x - 200), static_cast<int>(m_stringPos.y + 330), "もどる", 0xe04000);
		}

		// 設定ウインドウ
		if (m_isSetting)
		{
			DrawStringToHandle(static_cast<int>(m_stringPos.x + 400 + 70), static_cast<int>(m_stringPos.y - 20), "MAX", 0xe04000, handle.h_data.hf_starry_20);
			DrawStringToHandle(static_cast<int>(m_stringPos.x + 100), static_cast<int>(m_stringPos.y - 20), "MIN", 0xe04000, handle.h_data.hf_starry_20);
			if (m_menuNum == 0)
				DrawStringToHandle(static_cast<int>(m_stringPos.x - 200), static_cast<int>(m_stringPos.y), "BGM", 0xe04000, handle.h_data.hf_starry_40, 0xddc000);
			else
				DrawStringToHandle(static_cast<int>(m_stringPos.x - 200), static_cast<int>(m_stringPos.y), "BGM", 0xe04000, handle.h_data.hf_starry_40 );


			if (m_menuNum == 1)
				DrawStringToHandle(static_cast<int>(m_stringPos.x - 200), static_cast<int>(m_stringPos.y + 100), "SE", 0xe04000, handle.h_data.hf_starry_40, 0xddc000);
			else
				DrawStringToHandle(static_cast<int>(m_stringPos.x - 200), static_cast<int>(m_stringPos.y + 100), "SE", 0xe04000, handle.h_data.hf_starry_40);


			if (m_menuNum == 2)
				DrawStringToHandle(static_cast<int>(m_stringPos.x - 200), static_cast<int>(m_stringPos.y + 200), "LIGHT", 0xe04000, handle.h_data.hf_starry_40, 0xddc000);
			else
				DrawStringToHandle(static_cast<int>(m_stringPos.x - 200), static_cast<int>(m_stringPos.y + 200), "LIGHT", 0xe04000, handle.h_data.hf_starry_40);


			if (m_menuNum == 3)
				DrawString(static_cast<int>(m_stringPos.x - 200), static_cast<int>(m_stringPos.y + 330), "もどる", 0xe04000, 0xddc000);
			else
				DrawString(static_cast<int>(m_stringPos.x - 200), static_cast<int>(m_stringPos.y + 330), "もどる", 0xe04000);

			// 各種設定バー
			// BGM調整バー
			if (m_isBGM)
			{
				DrawBox(static_cast<int>(m_stringPos.x) + 100, static_cast<int>(m_stringPos.y + 20) + 4,
					static_cast<int>(m_stringPos.x) + 400 + 100, static_cast<int>(m_stringPos.y + 20) + 2 + 4,
					0xe04000, true);
				DrawCircle(static_cast<int>(m_stringPos.x) + (100 * (m_BGMSet)) + 100, static_cast<int>(m_stringPos.y + 20) + 1 + 4, 10,
					0xF8E559, true);
			}
			else
			{
				DrawBox(static_cast<int>(m_stringPos.x) + 100, static_cast<int>(m_stringPos.y + 20) + 4,
					static_cast<int>(m_stringPos.x) + 400 + 100, static_cast<int>(m_stringPos.y + 20) + 2 + 4,
					0xe04000, true);
				DrawCircle(static_cast<int>(m_stringPos.x) + (100 * (m_BGMSet )) + 100, static_cast<int>(m_stringPos.y + 20) + 1 + 4, 5,
					0xe04000, true);
			}
			// SE調整バー
			if (m_isSE)
			{
				DrawBox(static_cast<int>(m_stringPos.x) + 100, static_cast<int>(m_stringPos.y + 120) + 4,
					static_cast<int>(m_stringPos.x) + 400 + 100, static_cast<int>(m_stringPos.y + 120) + 2 + 4,
					0xe04000, true);
				DrawCircle(static_cast<int>(m_stringPos.x) + (100 * (m_SESet)) + 100, static_cast<int>(m_stringPos.y + 120) + 1 + 4, 10,
					0xF8E559, true);
			}
			else
			{
				DrawBox(static_cast<int>(m_stringPos.x) + 100, static_cast<int>(m_stringPos.y + 120) + 4,
					static_cast<int>(m_stringPos.x) + 400 + 100, static_cast<int>(m_stringPos.y + 120) + 2 + 4,
					0xe04000, true);
				DrawCircle(static_cast<int>(m_stringPos.x) + (100 * (m_SESet)) + 100, static_cast<int>(m_stringPos.y + 120) + 1 + 4, 5,
					0xe04000, true);
			}
			// 光量調整バー
			if (m_islight)
			{
				DrawBox(static_cast<int>(m_stringPos.x) + 100, static_cast<int>(m_stringPos.y + 220) + 4,
					static_cast<int>(m_stringPos.x) + 400 + 100, static_cast<int>(m_stringPos.y + 220) + 2 + 4,
					0xe04000, true);
				DrawCircle(static_cast<int>(m_stringPos.x) + (100 * (m_lightSet - 1)) + 100, static_cast<int>(m_stringPos.y + 220) + 1 + 4, 10,
					0xF8E559, true);
			}
			else
			{
				DrawBox(static_cast<int>(m_stringPos.x) + 100, static_cast<int>(m_stringPos.y + 220) + 4,
					static_cast<int>(m_stringPos.x) + 400 + 100, static_cast<int>(m_stringPos.y + 220) + 2 + 4,
					0xe04000, true);
				DrawCircle(static_cast<int>(m_stringPos.x) + (100 * (m_lightSet - 1)) + 100, static_cast<int>(m_stringPos.y + 220) + 1 + 4, 5,
					0xe04000, true);
			}
		}

		// クレジットウインドウ
		if (m_isCredit)
		{
			DrawString(static_cast<int>(m_stringPos.x - 200), static_cast<int>(m_stringPos.y), "音楽 ： 魔王魂", 0xe04000);
			DrawString(static_cast<int>(m_stringPos.x - 200), static_cast<int>(m_stringPos.y + 330), "もどる", 0xe04000, 0xddc000);
		}

		
	}
	// ChangeFontFromHandle(handle.h_data.hf_util_32);
}

void Window::Pause(bool flag)
{
	if (!m_isPause) m_isPause = true;
	this->CursorUpdate();
}

void Window::Setting()
{
	if (!m_isSetting) m_isSetting = true;
	this->CursorUpdate();
}

void Window::Credit()
{
	if (!m_isCredit) m_isCredit = true;
	this->CursorUpdate();
}

void Window::Maker()
{
	if (!m_isMaker) m_isMaker = true;
	this->CursorUpdate();
}



void Window::CursorUpdate()
{
	for (int i = 0; i < m_pSound.size(); i++)
	{
		m_pSound[i]->UpdateSE(m_SESet);
	}

	//////////////
	// キー入力 //
	//////////////
	// パッド
	int pad = GetJoypadInputState(DX_INPUT_PAD1);
	// 決定ボタン
	int hitSpace = CheckHitKey(KEY_INPUT_SPACE);
	// メニュー選択　十字上下キー
	int hitU = CheckHitKey(KEY_INPUT_UP);
	int hitD = CheckHitKey(KEY_INPUT_DOWN);
	// ステージ選択　十字左右キー
	int hitL = CheckHitKey(KEY_INPUT_LEFT);
	int hitR = CheckHitKey(KEY_INPUT_RIGHT);

	//////////
	// 操作 //
	//////////
	// ウインドウ展開後から操作可能
	if (!m_isWindow && (m_isPause || m_isSetting || m_isCredit || m_isMaker))
	{
		this->Open();
	}
	else if (m_isWindow && !m_isRastHit)
	{
		/* カーソル操作 */
		// クレジット画面は表記＆戻るのみなので固定
		/*if (m_isCredit)
		{
			m_menuNum = 3;
		}*/
		// 音量光量　左右キー
		// BGM
		if (m_isBGM)
		{
			if (hitR || pad == PAD_INPUT_RIGHT)
			{
				m_pSound[0]->OnePlay();
				m_pSound[0]->OnePlay();
				m_pSound[0]->OnePlay();
				if (m_BGMSet < 4)
				{
					m_BGMSet++;
				}
			}
			if (hitL || pad == PAD_INPUT_LEFT)
			{
				m_pSound[0]->OnePlay();
				m_pSound[0]->OnePlay();
				m_pSound[0]->OnePlay();
				if (m_BGMSet > 0)
				{
					m_BGMSet--;
				}
			}
		}
		// SE
		else if (m_isSE)
		{
			if (hitR || pad == PAD_INPUT_RIGHT)
			{
				m_pSound[0]->OnePlay();
				m_pSound[0]->OnePlay();
				m_pSound[0]->OnePlay();
				if (m_SESet < 4)
				{
					m_SESet++;
				}
			}
			if (hitL || pad == PAD_INPUT_LEFT)
			{
				m_pSound[0]->OnePlay();
				m_pSound[0]->OnePlay();
				m_pSound[0]->OnePlay();
				if (m_SESet > 0)
				{
					m_SESet--;
				}
			}
		}
		// 光量
		else if (m_islight)
		{
			if (hitR || pad == PAD_INPUT_RIGHT)
			{
				m_pSound[0]->OnePlay();
				m_pSound[0]->OnePlay();
				m_pSound[0]->OnePlay();
				if (m_lightSet < 5)
				{
					m_lightSet++;
				}
			}
			if (hitL || pad == PAD_INPUT_LEFT)
			{
				m_pSound[0]->OnePlay();
				m_pSound[0]->OnePlay();
				m_pSound[0]->OnePlay();
				if (m_lightSet > 1)
				{
					m_lightSet--;
				}
			}
		}
		// メーカーのステージセレクト
		else if (m_isSelect)
		{
			if (hitR || pad == PAD_INPUT_RIGHT)
			{
				m_pSound[0]->OnePlay();
				m_pSound[0]->OnePlay();
				m_pSound[0]->OnePlay();
				if (m_stageNum < 10)
				{
					m_stageNum++;
				}
				else m_stageNum = 1;
			}
			if (hitL || pad == PAD_INPUT_LEFT)
			{
				m_pSound[0]->OnePlay();
				m_pSound[0]->OnePlay();
				m_pSound[0]->OnePlay();
				if (m_stageNum > 1)
				{
					m_stageNum--;
				}
				else m_stageNum = 10;
			}
		}
		else
		{
			// メニュー選択　上下キー
			if (hitU || pad == PAD_INPUT_UP)
			{
				m_pSound[0]->OnePlay();
				m_pSound[0]->OnePlay();
				m_pSound[0]->OnePlay();
				// ポーズ画面のカーソル動作
				if (m_isPause && !m_isSetting)
				{
					if (m_menuNum == 3) m_menuNum = 1;
					else if (m_menuNum == 1) m_menuNum = 0;
					else if (m_menuNum == 0) m_menuNum = 3;
				}
				// メーカー
				if (m_isMaker && !m_isSetting)
				{
					if (m_menuNum == 1) m_menuNum = 3;
					else m_menuNum = 1;
				}
				// 設定
				if (m_isSetting)
				{
					if (m_menuNum > 0) m_menuNum--;
					else m_menuNum = 3;
				}
				// クレジット
				if (m_isCredit)
				{
					m_menuNum = 3;
				}
			}
			if (hitD || pad == PAD_INPUT_DOWN)
			{
				m_pSound[0]->OnePlay();
				m_pSound[0]->OnePlay();
				m_pSound[0]->OnePlay();
				// ポーズ画面のカーソル動作
				if (m_isPause && !m_isSetting)
				{
					if (m_menuNum == 0) m_menuNum = 1;
					else if (m_menuNum == 1) m_menuNum = 3;
					else if (m_menuNum == 3) m_menuNum = 0;
				}
				// メーカー
				if (m_isMaker && !m_isSetting)
				{
					if (m_menuNum == 3) m_menuNum = 1;
					else m_menuNum = 3;
				}
				// 設定
				if (m_isSetting)
				{
					if (m_menuNum < 3) m_menuNum++;
					else m_menuNum = 0;
				}
				// クレジット
				if (m_isCredit)
				{
					m_menuNum = 3;
				}
			}
		}

		/* 各ウインドウメニュー操作 */
		switch (m_menuNum)
		{
		case 0:
			m_cursorPos.y = m_stringPos.y + 8;
			if (hitSpace || pad == PAD_INPUT_1)
			{
				m_pSound[1]->OnePlay();
				// ポーズ画面：設定画面へ
				if (m_isPause && !m_isSetting)
				{
					m_isSetting = true;
					break;
				}
				// メーカー: つくる
				if (m_isMaker)
				{
					m_isGoMake = true;
					m_isMaker = false;
					break;
				}
				// 設定画面：BGM
				if (m_isSetting)
				{
					m_isBGM = !m_isBGM;
					break;
				}
			}
			break;
		case 1:
			m_cursorPos.y = m_stringPos.y + 100 + 8;
			if (hitSpace || pad == PAD_INPUT_1)
			{
				m_pSound[1]->OnePlay();
				// ポーズ画面：タイトルシーンへ
				if (m_isPause && !m_isSetting)
				{
					m_isTitle = true;
					break;
				}
				// メーカー: あそぶ
				if (m_isMaker) 
				{
					m_isSelect = !m_isSelect;
					break;
				}
				// 設定画面：サウンドエフェクト
				if (m_isSetting) 
				{
					m_isSE = !m_isSE;
					break;
				}
			}
			break;
		case 2:
			m_cursorPos.y = m_stringPos.y + 200 + 8;
			if (hitSpace || pad == PAD_INPUT_1)
			{
				m_pSound[1]->OnePlay();
				// メーカー: IDであそぶ
				if (m_isMaker) {}
				// 設定画面：光量
				if (m_isSetting)
				{
					m_islight = !m_islight;
					break;
				}
			}
			break;
		case 3:
			m_cursorPos.y = m_stringPos.y + 330 + 8;
			// 終了フラグ
			if (hitSpace || pad == PAD_INPUT_1)
			{
				m_pSound[1]->OnePlay();
				// ウインドウを閉じる
				if (m_isMaker)
				{
					m_isMaker = false;
					m_menuNum = 0;
					break;
				}
				if (m_isSetting)
				{
					m_isSetting = false;
					m_menuNum = 0;
					break;
				}
				else if (m_isPause)
				{
					m_isPause = false;
					m_menuNum = 0;
					break;
				}
				if (m_isCredit)
				{
					m_isCredit = false;
					m_menuNum = 0;
					break;
				}
			}
			break;
		default:
			break;
		}
		/*if (m_goTimer < 180) m_goTimer++;
		else
		{
			if (m_isGoMake) m_isGoMake = false;
			m_goTimer = 0;
		}*/

		if (pad == PAD_INPUT_8)
		{
			// ウインドウを閉じる
			if (m_isMaker)
			{
				m_isMaker = false;
				m_menuNum = 0;
			}
			if (m_isSetting)
			{
				m_isSetting = false;
				m_menuNum = 0;
			}
			else if (m_isPause)
			{
				m_isPause = false;
				m_menuNum = 0;
			}
			if (m_isCredit)
			{
				m_isCredit = false;
				m_menuNum = 0;
			}
		}
	}

	// こっちでの Close 要らなそうだね
	/*if (m_isWindow && (!m_isPause && !m_isSetting && !m_isCredit))
	{
		this->Close();
	}*/
	
	// 直前フレームでのキー押し判定
	if (hitSpace || hitU || hitD || hitL || hitR || pad) m_isRastHit = true;
	else m_isRastHit = false;
}

void Window::SetSetting(int BGM, int SE, int light)
{
	m_BGMSet = BGM;
	m_SESet = SE;
	m_lightSet = light;
}