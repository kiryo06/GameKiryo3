#include "DxLib.h"
#include "Player.h"
#include "Game.h"
#include "Sound.h"
#include <cassert>


Player::Player() :
	m_pos(0, 0),
	m_move(0.0f, 0.0f),
	m_dir(kDirDown),
	m_isMove(false),
	m_wallHit(false),
	m_isLongUpKey(false),
	m_isLongDownKey(false),
	m_isLongLeftKey(false),
	m_isLongRightKey(false),
	m_isClear(false),
	m_moveTime(0),
	m_moving(0,0)
{
}

Player::~Player()
{
}

void Player::Init(float x, float y)
{
	m_firstPos = { static_cast<float>(x) * Game::kGraphWidth + Game::kMapStartPosX + Game::kGraphHalfWidth,
				static_cast<float>(y)* Game::kGraphHeight + Game::kMapStartPosY + Game:: kGraphHalfHeight };
	m_pos = m_firstPos;
	m_colRect.SetCenter(m_pos.x,
		m_pos.y,
		Game::kGraphWidth-1,
		Game::kGraphHeight-1);
	m_isClear = false;
}

void Player::Update()
{
	// パッドの十字キーを使用してプレイヤーを移動させる
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (!m_isClear)
	{
		if (pad & PAD_INPUT_UP)
		{
			if (!m_isLongUpKey && !m_isMove)
			{
				m_move = { 0.0f,0.0f };
				m_move.y --;
				m_dir = kDirUp;
				m_isMove = true;
				m_isLongUpKey = true;
			}
		}
		else m_isLongUpKey = false;
		if (pad & PAD_INPUT_DOWN)
		{
			if (!m_isLongDownKey && !m_isMove)
			{
				m_move = { 0.0f,0.0f };
				m_move.y ++;
				m_dir = kDirDown;
				m_isMove = true;
				m_isLongDownKey = true;
			}
		}
		else m_isLongDownKey = false;
		if (pad & PAD_INPUT_LEFT)
		{
			if (!m_isLongLeftKey && !m_isMove)
			{
				m_move = { 0.0f,0.0f };
				m_move.x --;
				m_dir = kDirLeft;
				m_isMove = true;
				m_isLongLeftKey = true;
			}
		}
		else m_isLongLeftKey = false;
		if (pad & PAD_INPUT_RIGHT)
		{
			if (!m_isLongRightKey && !m_isMove)
			{
				m_move = { 0.0f,0.0f };
				m_move.x ++;
				m_dir = kDirRight;
				m_isMove = true;
				m_isLongRightKey = true;
			}
		}
		else m_isLongRightKey = false;
	}
	else m_dir = kDirUp;
	//// 正規化
	m_move.Normalize();

	// ゴール時はゆっくりに
	if (m_isClear)
	{
		m_move *= 0.5f;
	}

	//// 長さの変更
	m_move *= kSpeed;
	

	// 動いた距離測定
	if (m_isMove)
	{
		m_moving += m_move;
		// 2フレーム以上動いたときにカウント
		if (m_moving == m_move * 2 && !m_isClear)
		{
			m_moveTime++;
		}
	}
	
	// 座標にベクトルを足す
	m_pos += m_move;

	// 当たり判定の更新
	m_colRect.SetCenter(m_pos.x, m_pos.y, Game::kGraphWidth-1, Game::kGraphHeight-1);


}

void Player::Draw()
{
	for (int x = -kSize; x <= kSize; x++)
	{
		for (int y = -kSize; y <= kSize; y++)
		{
			
			Vec2 DrawPoint = { m_pos.x + x + 1, m_pos.y + y + 1 };
			if (!DrawPlayer(DrawPoint))
			{
				Vec2 PosVec = DrawPoint - m_pos;
				float langth = PosVec.Length() + 1;
				if (langth < kSize - 1 && (x != kSize && x != -kSize && y != kSize && y != -kSize))
				{
						DrawPixel(static_cast<int>(DrawPoint.x), static_cast<int>(DrawPoint.y), 0xffffff);
				}
				else if(langth <= kSize)
					DrawPixel(static_cast<int>(DrawPoint.x), static_cast<int>(DrawPoint.y), 0xee0000);
			}
				

		}
	}
}

bool Player::DrawPlayer(Vec2 point)
{
	for (int dx = -kDontEyeSize; dx <= kDontEyeSize; dx++)
	{
		for (int dy = -kDontEyeSize; dy <= kDontEyeSize; dy++)
		{
			Vec2 DontDrawPointR = { m_pos.x + 6 + dx, m_pos.y + dy + 1 };
			Vec2 DontDrawPointL = { m_pos.x - 6 + dx + 1, m_pos.y + dy + 1 };
			Vec2 PosVec = {static_cast<float>(dx),static_cast<float>(dy)};
			float langth = PosVec.Length() + 1;
		
			if (langth <= 4)
			{
				switch (m_dir)
				{
				case kDirDown:
					if (point == DontDrawPointR)
					{
						DrawCircle(DontDrawPointR.x - dx, DontDrawPointR.y - dy, kEyeSize, 0xee0000, true);
						return true;
					}
					else if (point == DontDrawPointL)
					{
						DrawCircle(DontDrawPointL.x - dx, DontDrawPointL.y - dy, kEyeSize,0xee0000, true);
						return true;
					}
					break;

				case kDirLeft:
					if (point == DontDrawPointL)
					{
						DrawCircle(DontDrawPointL.x - dx, DontDrawPointL.y - dy, kEyeSize, 0xee0000, true);
						return true;
					}
					break;

				case kDirRight:
					if (point == DontDrawPointR)
					{
						DrawCircle(DontDrawPointR.x - dx, DontDrawPointR.y - dy, kEyeSize, 0xee0000, true);
						return true;
					}
					break;

				case kDirUp:
					return false;
					break;

				default:
					return false;
					break;
				}
			}
		}
	}
	return false;
}

void Player::WallHit(Rect& wall)
{
	// 壁ヒット判定
	m_wallHit = false;
	m_wallHit = m_colRect.IsCollsion(wall);

	// 壁ヒット時に発動
	if (m_wallHit && !m_isClear)
	{
		m_pos -= m_move;
		m_move = { 0.0f,0.0f };
		m_wallHit = true;
		m_isMove = false;
		m_moving = { 0,0 };
	}
}

void Player::DirWallHit(Rect& dirWall, bool& isPass)
{
	m_wallHit = false;
	if(m_colRect.IsCollsion(dirWall) && !isPass && !m_isClear)
	{
		m_wallHit = true;
		m_pos -= m_move;
		m_move = { 0.0f,0.0f };
		m_isMove = false;
		m_moving = { 0,0 };
	}
}

void Player::GoalIn(Rect& goal)
{
	if (m_colRect.m_top >= goal.m_top &&
		m_colRect.m_bottom <= goal.m_bottom &&
		m_colRect.m_left >= goal.m_left &&
		m_colRect.m_right <= goal.m_right)
	{
		m_move = { 0.0f,0.0f };
		m_isClear = true;
		m_colRect.zero();
		if (m_pos.y > 0 - Game::kGraphHeight * 2)
		{
			m_move = { 0.0f, -kGoalSpeed };
		}
	}
}
