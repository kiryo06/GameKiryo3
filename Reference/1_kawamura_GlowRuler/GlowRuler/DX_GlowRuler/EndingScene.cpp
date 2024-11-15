#include "EndingScene.h"
#include "DxLib.h"
#include "Sound.h"
#include "Handle.h"

namespace
{
	constexpr int kTempStringPosX = 30;
	constexpr float kStringPosXfromScreen = Game::kScreenWidth * 0.825f;
}

EndingScene::EndingScene() :
	m_clearWidth(0),
	m_startWidth(0),
	m_timeWidth(0),
	m_alpha(0),
	m_isAlpha(false),
	m_appStartTimer(0),
	m_isKey(false),
	m_isTransScene(false),
	m_resultTime(0),
	m_gameMode(0),
	m_efectDir(0),
	m_FadeAlpha(0),
	m_flashTimer(0),
	m_isUpdateSound(false)
{
	m_pos = { (Game::kScreenWidth * 0.1f), Game::kScreenHeight * 0.1f };
	m_RankResult = { 0,0,0,0,0 };

	// サウンド
	m_pSound.resize(4);
	for (int i = 0; i < m_pSound.size(); i++)
	{
		m_pSound[i] = new Sound;
	}

	for (int i = 0; i < 5; i++)
	{
		m_rankPosMove[i] = 500;
	}
}

EndingScene::~EndingScene()
{
	m_pSound[0]->Stop();
	for (int i = 0; i < m_pSound.size(); i++)
	{
		delete m_pSound[i];
		m_pSound[i] = nullptr;
	}
}

void EndingScene::Init(int time, int gameMode, int BGM, int SE, const Rank& timerank, const Handle& handle)
{
	m_clearWidth = GetDrawStringWidth("CLEAR", static_cast<int>(strlen("CLEAR")));
	m_startWidth = GetDrawStringWidth("PRESS SPACE", static_cast<int>(strlen("PRESS SPACE")));
	m_timeWidth = GetDrawStringWidth("記録  　 回", static_cast<int>(strlen("記録  　 回")));
	m_gameMode = gameMode;
	m_resultTime = time;
	m_RankResult = timerank;

	

	// リザルトBGM
	m_pSound[0]->InitSE(handle.h_data.hm_S_12);
	// 決定音
	m_pSound[1]->InitSE(handle.h_data.hm_S_01);
	// 記録更新音
	m_pSound[2]->InitSE(handle.h_data.hm_S_09);
	// ランキング移動音
	m_pSound[3]->InitSE(handle.h_data.hm_S_11);

	// 音量更新
	for (int i = 0; i < m_pSound.size(); i++)
	{
		m_pSound[i]->UpdateSE(SE);
	}

	m_pSound[0]->OnePlay();
}

void EndingScene::Update()
{
	int pad = GetJoypadInputState(DX_INPUT_PAD1);
	int hitSpace = CheckHitKey(KEY_INPUT_SPACE);
	if (m_alpha < 255 && !m_isKey)
	{
		m_alpha += 5;
	}
	if (m_alpha >= 255)
	{
		for (int i = 0; i < 5; i++)
		{
			if (i == 0 || m_rankPosMove[i - 1] <= 0)
			{
				if (m_rankPosMove[i] > 0)
				{
					m_rankPosMove[i] -= 25;
					if (m_rankPosMove[i] == 500 - 25)
					{
						m_pSound[3]->OnePlay();
					}
				}
			}
		}
		m_alpha = 255;
		m_isAlpha = true;
		if ((hitSpace || pad == PAD_INPUT_1) && !m_isKey)
		{
			m_pSound[1]->OnePlay();
			m_isKey = true;
		}
	}
	if (m_appStartTimer < 120)
	{
		if (!m_isKey) m_appStartTimer++;
		else
		{
			m_appStartTimer += 12;
		}
	}
	else m_appStartTimer = 0;

	if (m_isKey)
	{
		if (m_FadeAlpha < 255)
			m_FadeAlpha += 5;
		if (m_FadeAlpha >= 255)
			m_isTransScene = true;
	}

	if (m_efectDir <= Game::kScreenWidth * 0.5f)
		m_efectDir += 20;

	if (m_flashTimer < 40)
	{
		m_flashTimer++;
	}
	else
	{
		m_flashTimer = 0;
	}
}

void EndingScene::Draw(const Handle& handle)
{
	// エフェクト
	/*
	for (int i = 10; i >= 0; i--)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - (i * 25));
		DrawCircle(static_cast<int>(Game::kScreenWidth * 0.5f), static_cast<int>(Game::kScreenHeight * 0.5f), m_efectDir + (i * 30), 0xee82ee, true);
	}
	*/
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alpha);
	DrawBox(0, 0, Game::kScreenWidth + 1, Game::kScreenHeight + 1, 0xba70d3, true);
	DrawBox(Game::kScreenWidth + 1, Game::kScreenHeight + 1, static_cast<int>(Game::kScreenWidth * 0.7f), 0, 0x603d90, true);
	// テキスト
	DrawStringToHandle(static_cast<int>(m_pos.x - (m_clearWidth * 0.5f)), static_cast<int>(m_pos.y), "C L E A R", 0xb22222,handle.h_data.hf_starry_64, 0xffffff);
	
	if (m_gameMode == 0)
	{
		// 今回の回数
		if((m_resultTime == m_RankResult.time_1 || m_resultTime == m_RankResult.time_2 ||
			m_resultTime == m_RankResult.time_3 || m_resultTime == m_RankResult.time_4 ||
			m_resultTime == m_RankResult.time_5)
			&& m_flashTimer <= 20
			&& m_rankPosMove[4] <= 0)
		{
			if (!m_isUpdateSound)
			{
				m_isUpdateSound = true;
				m_pSound[2]->OnePlay();
			}
			DrawFormatString2FToHandle(Game::kScreenWidth * 0.175f, Game::kScreenHeight * 0.4f,
				0xffd300, 0x8986eb, handle.h_data.hf_util_72, "　記録  %d 回", m_resultTime);
			DrawFormatString2FToHandle(Game::kScreenWidth * 0.175f, Game::kScreenHeight * 0.6f,
				0xffd300, 0x8986eb, handle.h_data.hf_starry_64, "NEW RECORD !!!!", m_resultTime);
		}
		else if ((m_resultTime == m_RankResult.time_1 || m_resultTime == m_RankResult.time_2 ||
			m_resultTime == m_RankResult.time_3 || m_resultTime == m_RankResult.time_4 ||
			m_resultTime == m_RankResult.time_5)
			&& m_rankPosMove[4] <= 0)
		{
			DrawFormatString2FToHandle(Game::kScreenWidth * 0.175f, Game::kScreenHeight * 0.4f,
				0xffffff, 0x8986eb, handle.h_data.hf_util_72, "　記録  %d 回", m_resultTime);
			DrawFormatString2FToHandle(Game::kScreenWidth * 0.175f, Game::kScreenHeight * 0.6f,
				0xffffff, 0x8986eb, handle.h_data.hf_starry_64, "NEW RECORD !!!!", m_resultTime);
		}
		else
		{
			DrawFormatString2FToHandle(Game::kScreenWidth * 0.175f, Game::kScreenHeight * 0.4f,
				0xffffff, 0x8986eb, handle.h_data.hf_util_72, "　記録  %d 回", m_resultTime);
		}

		// ランキング
		DrawStringToHandle(static_cast<int>((Game::kScreenWidth * 0.78f)), static_cast<int>(Game::kScreenHeight * 0.075f), "All Stage\n Ranking",
			0xb22222, handle.h_data.hf_starry_48, 0xffffff);

		DrawFormatString2FToHandle((kStringPosXfromScreen) - (m_timeWidth * 0.5f) - kTempStringPosX + m_rankPosMove[0],Game::kScreenHeight * 0.3f, 0xffffff, 0x8986eb,
			handle.h_data.hf_util_40,"１st　%d 回", m_RankResult.time_1);
		DrawFormatString2FToHandle((kStringPosXfromScreen - 5) - (m_timeWidth * 0.5f) - kTempStringPosX + m_rankPosMove[1], Game::kScreenHeight * 0.4f, 0xffffff, 0x8986eb,
			handle.h_data.hf_util_40, "２nd　%d 回",m_RankResult.time_2);
		DrawFormatString2FToHandle((kStringPosXfromScreen) - (m_timeWidth * 0.5f) - kTempStringPosX + m_rankPosMove[2], Game::kScreenHeight * 0.5f, 0xffffff, 0x8986eb,
			handle.h_data.hf_util_40, "３rd　%d 回", m_RankResult.time_3);0x8986eb,
		DrawFormatString2FToHandle((kStringPosXfromScreen) - (m_timeWidth * 0.5f) - kTempStringPosX + m_rankPosMove[3], Game::kScreenHeight * 0.6f, 0xffffff, 0x8986eb,
			handle.h_data.hf_util_40, "４th　%d 回", m_RankResult.time_4);
		DrawFormatString2FToHandle((kStringPosXfromScreen) - (m_timeWidth * 0.5f) - kTempStringPosX + m_rankPosMove[4], Game::kScreenHeight * 0.7f, 0xffffff, 0x8986eb,
			handle.h_data.hf_util_40, "５th　%d 回", m_RankResult.time_5);

		// 記録更新で黄色くランキング点灯
		if (m_resultTime == m_RankResult.time_1 && m_flashTimer <= 20 && m_rankPosMove[4] <= 0)
		{
			DrawFormatString2FToHandle((kStringPosXfromScreen) - (m_timeWidth * 0.5f) - kTempStringPosX + m_rankPosMove[0], Game::kScreenHeight * 0.3f, 0xffd300, 0x8986eb,
				handle.h_data.hf_util_40, "１st　%d 回", m_RankResult.time_1);
		}
		else if (m_resultTime == m_RankResult.time_2 && m_flashTimer <= 20 && m_rankPosMove[4] <= 0)
		{
			DrawFormatString2FToHandle((kStringPosXfromScreen - 5) - (m_timeWidth * 0.5f) - kTempStringPosX + m_rankPosMove[1], Game::kScreenHeight * 0.4f, 0xffd300, 0x8986eb,
				handle.h_data.hf_util_40, "２nd　%d 回", m_RankResult.time_2);
		}
		else if (m_resultTime == m_RankResult.time_3 && m_flashTimer <= 20 && m_rankPosMove[4] <= 0)
		{
			DrawFormatString2FToHandle((kStringPosXfromScreen) - (m_timeWidth * 0.5f) - kTempStringPosX + m_rankPosMove[2], Game::kScreenHeight * 0.5f, 0xffd300, 0x8986eb,
				handle.h_data.hf_util_40, "３rd　%d 回", m_RankResult.time_3);
		}
		else if (m_resultTime == m_RankResult.time_4 && m_flashTimer <= 20 && m_rankPosMove[4] <= 0)
		{
			DrawFormatString2FToHandle((kStringPosXfromScreen) - (m_timeWidth * 0.5f) - kTempStringPosX + m_rankPosMove[3], Game::kScreenHeight * 0.6f, 0xffd300, 0x8986eb,
				handle.h_data.hf_util_40, "４th　%d 回", m_RankResult.time_4);
		}
		else if (m_resultTime == m_RankResult.time_5 && m_flashTimer <= 20 && m_rankPosMove[4] <= 0)
		{
			DrawFormatString2FToHandle((kStringPosXfromScreen) - (m_timeWidth * 0.5f) - kTempStringPosX + m_rankPosMove[4], Game::kScreenHeight * 0.7f, 0xffd300, 0x8986eb,
				handle.h_data.hf_util_40, "５th　%d 回", m_RankResult.time_5);
		}
		
		

		
		
	}
	else if (m_gameMode == 1)
	{
		// 今回の回数
		DrawFormatString2FToHandle(Game::kScreenWidth * 0.175f, Game::kScreenHeight * 0.4f,
			0xffffff, 0x8986eb, handle.h_data.hf_util_72, "　記録  %d 回", m_resultTime);

		// ランキング
		DrawStringToHandle(static_cast<int>((Game::kScreenWidth * 0.78f)), static_cast<int>(Game::kScreenHeight * 0.075f), "All Stage\n Ranking",
			0xb22222, handle.h_data.hf_starry_48, 0xffffff);

		DrawFormatString2FToHandle((kStringPosXfromScreen) - (m_timeWidth * 0.5f) - kTempStringPosX + m_rankPosMove[0], Game::kScreenHeight * 0.3f, 0xffffff, 0x8986eb,
			handle.h_data.hf_util_40, "１st　%d 回", m_RankResult.time_1);
		DrawFormatString2FToHandle((kStringPosXfromScreen - 5) - (m_timeWidth * 0.5f) - kTempStringPosX + m_rankPosMove[1], Game::kScreenHeight * 0.4f, 0xffffff, 0x8986eb,
			handle.h_data.hf_util_40, "２nd　%d 回", m_RankResult.time_2);
		DrawFormatString2FToHandle((kStringPosXfromScreen) - (m_timeWidth * 0.5f) - kTempStringPosX + m_rankPosMove[2], Game::kScreenHeight * 0.5f, 0xffffff, 0x8986eb,
			handle.h_data.hf_util_40, "３rd　%d 回", m_RankResult.time_3);
		DrawFormatString2FToHandle((kStringPosXfromScreen) - (m_timeWidth * 0.5f) - kTempStringPosX + m_rankPosMove[3], Game::kScreenHeight * 0.6f, 0xffffff, 0x8986eb,
			handle.h_data.hf_util_40, "４th　%d 回", m_RankResult.time_4);
		DrawFormatString2FToHandle((kStringPosXfromScreen) - (m_timeWidth * 0.5f) - kTempStringPosX + m_rankPosMove[4], Game::kScreenHeight * 0.7f, 0xffffff, 0x8986eb,
			handle.h_data.hf_util_40, "５th　%d 回", m_RankResult.time_5);

		DrawStringToHandle(static_cast<int>((kStringPosXfromScreen) - (m_timeWidth * 0.5f) - kTempStringPosX) + m_rankPosMove[4], static_cast<int>(Game::kScreenHeight * 0.85f),
				"ランキングにも\n　　チャレンジしてみよう !!", 0xffffff, handle.h_data.hf_util_24);
	}
	if (m_isAlpha && m_appStartTimer < 60)
	{
		DrawString(static_cast<int>(Game::kScreenWidth * 0.2f), static_cast<int>(Game::kScreenHeight * 0.8f), "PRESS　 SPACE or A", 0xffffff);
	}
	// フェードアウト用
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_FadeAlpha);
	DrawBox(0, 0, Game::kScreenWidth + 1, Game::kScreenHeight + 1, 0x000000, true);
}
