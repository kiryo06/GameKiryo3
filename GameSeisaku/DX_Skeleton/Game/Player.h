#pragma once
#include "Actor.h"

class Player : public Actor
{
private:
	enum class Direction
	{
		// ���Ԃ͂��̒ʂ�
		down,
		left,
		leftup,
		up,
		rightup,
		right
	};

	Direction currentDir_;
	int idleH_;
	int walkH_;
	int animFrame_;

	using UpdateFunc_t = void (Player::*)(Input&);
	using DrawFunc_t = void (Player::*)() const;

	void IdleUpdate(Input& input);
	void IdleDraw() const;

	void WalkUpdate(Input& input);
	void WalkDraw() const;

	UpdateFunc_t update_;
	DrawFunc_t draw_;

	// �ړ��̏����𕪂���
	// �ړ�������true
	bool Move(Input& input);
public:
	Player(GameScene& gameScene);
	~Player();

	void Update(Input& input) override;
	void Draw() const override;

	void OnHit(Collision& collision) override;
};

