#include "Player.h"
#include <DxLib.h>
#include "../Input.h"

//#define CHANGE_STATE(state) update_ = &Player::state_Update; draw_ = &Player::state Draw; animFrame_ = 0;

namespace
{
	constexpr int anim_interval = 7;
	constexpr int anim_num      = 8;
	constexpr int center_pos_x  = 24;
	constexpr int center_pos_y  = 48;
	constexpr int cut_width     = 48;
	constexpr int cut_height    = 64;
	constexpr double ex_rate    = 3.0;
	constexpr float move_speed = 2.0f;

	const Position2 kInitPos = { 320, 240 };

	const std::string kIdlePath = "image/Player/idle.png";
	const std::string kWalkPath = "image/Player/walk.png";
}

void Player::IdleUpdate(Input& input)
{
	// こいつ、このフレームも動きつつ状態遷移を…！
	if (Move(input))
	{
		update_ = &Player::WalkUpdate;
		draw_ = &Player::WalkDraw;
		animFrame_ = 0;
	}
}

void Player::IdleDraw() const
{
	// アニメーションクラスに汚いのを全部押し付けたいんですが
	auto idx = (animFrame_ / anim_interval) % anim_num;
	DrawRectRotaGraph2(static_cast<int>(pos_.x), static_cast<int>(pos_.y),
		cut_width * idx, cut_height * static_cast<int>(currentDir_),
		cut_width, cut_height,
		center_pos_x, center_pos_y,
		ex_rate, 0.0f,
		idleH_, true);
}

void Player::WalkUpdate(Input& input)
{
	if (!Move(input))
	{
		update_ = &Player::IdleUpdate;
		draw_ = &Player::IdleDraw;
		animFrame_ = 0;
	}
}

void Player::WalkDraw() const
{
	// アニメーションクラスに汚いのを全部押し付けたいんですが
	auto idx = (animFrame_ / anim_interval) % anim_num;
	DrawRectRotaGraph2(static_cast<int>(pos_.x), static_cast<int>(pos_.y),
		cut_width * idx, cut_height * static_cast<int>(currentDir_),
		cut_width, cut_height,
		center_pos_x, center_pos_y,
		ex_rate, 0.0f,
		walkH_, true);
}

Player::Player(GameScene& gameScene) :
	Actor(gameScene),
	idleH_(0),
	animFrame_(0),
	currentDir_(Direction::down),
	update_(&Player::IdleUpdate),
	draw_(&Player::IdleDraw)
{
	idleH_ = LoadGraph(kIdlePath.c_str());
	walkH_ = LoadGraph(kWalkPath.c_str());
	pos_ = kInitPos;
}

Player::~Player()
{
}

void Player::Update(Input& input)
{
	++animFrame_;

	(this->*update_)(input);
}

bool Player::Move(Input& input)
{
	Vector2 vec{};
	if (input.IsPressed("up"))
	{
		currentDir_ = Direction::up;
		--vec.y;
	}
	if (input.IsPressed("down"))
	{
		currentDir_ = Direction::down;
		++vec.y;
	}
	if (input.IsPressed("left"))
	{
		currentDir_ = Direction::left;
		--vec.x;
	}
	if (input.IsPressed("right"))
	{
		currentDir_ = Direction::right;
		++vec.x;
	}

	pos_ += vec.Normalized() * move_speed;
	return vec.x != 0 || vec.y != 0;
}

void Player::Draw() const
{
	(this->*draw_)();
}

void Player::OnHit(Collision& collision)
{
}
