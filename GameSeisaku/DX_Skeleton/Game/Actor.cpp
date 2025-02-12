#include "Actor.h"

Actor::Actor(GameScene& gameScene) :
	gameScene_(gameScene)
{
}

void Actor::SetPosition(const Position2& pos)
{
	pos_ = pos;
}
