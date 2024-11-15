#include "GameUI.h"
#include "DxLib.h"
#include "Game.h"
#include "Handle.h"

GameUI::GameUI():
	m_stagePos(0,0),
	m_iconPos(0,0),
	m_WindowPos(0,0),
	stageNum(1),
	m_gamemode(0)
{
}

GameUI::~GameUI()
{
}

void GameUI::Init(int mode)
{
	m_gamemode = mode;
	m_stagePos = { 50.0f,40.0f };
	m_iconPos = { Game::kScreenWidth - 400.0f, 40.0f };
	m_WindowPos = { Game::kScreenWidth - 150.0f, 40.0f };
}

void GameUI::Update()
{
}

void GameUI::Draw(const Handle& handle)
{
	DrawFormatString2FToHandle(m_stagePos.x, Game::kScreenHeight - 110,
		0xe0e0e0, 0x8986eb, handle.h_data.hf_util_32, "É|Å[ÉY [ ESC  or  Start ]");
	DrawFormatString2FToHandle(m_stagePos.x, m_stagePos.y,
		0xe0e0e0, 0x8986eb, handle.h_data.hf_starry_64, "S T A G E  %d", stageNum);

	if (m_gamemode == 1)
	{
		DrawFormatString2FToHandle(m_stagePos.x - 20, Game::kScreenHeight - 70,
			0xe0e0e0, 0x8986eb, handle.h_data.hf_util_32, "Ç‚ÇËÇ»Ç®Çµ [ Z  or  X button ]", stageNum);
	}

}
