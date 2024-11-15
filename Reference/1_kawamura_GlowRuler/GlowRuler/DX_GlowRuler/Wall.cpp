#include "Wall.h"
#include "Dxlib.h"
#include "Game.h"
#include "Handle.h"
#include <cassert>


Wall::Wall():
	m_pos{0,0},
	m_isFixed(false),
	m_isMove(false),
	m_mousePos(0,0),
	m_isClick(false)
{
}

Wall::~Wall()
{
}

void Wall::Init(int x, int y)
{
	m_pos = {	static_cast<float>(x) * Game::kGraphWidth + Game::kMapStartPosX + Game::kGraphHalfWidth,
				static_cast<float>(y) * Game::kGraphHeight + Game::kMapStartPosY + Game::kGraphHalfHeight };
	m_colRect.SetCenter(m_pos.x,
						m_pos.y,
						Game::kGraphWidth,
						Game::kGraphHeight);
	
	
}

void Wall::Update()
{
}

void Wall::Draw(const Handle& handle)
{
	DrawExtendGraph(static_cast<int>(m_pos.x - (Game::kGraphHalfWidth)),
		static_cast<int>(m_pos.y - (Game::kGraphHalfHeight)),
		static_cast<int>(m_pos.x + (Game::kGraphHalfWidth) - 1),
		static_cast<int>(m_pos.y + (Game::kGraphHalfHeight) - 1),
		handle.h_data.hi_wall, true);
}
