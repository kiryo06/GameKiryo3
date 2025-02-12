#pragma once
#include"Geometry.h"
class Actor;

enum class CollsionType
{
	Player,
	Block,
	Enemy,
};

class Collsion
{
private:
	CollsionType type_;
	Rect rect_;
	Actor& owner_;
public:
	Collsion(Actor& owner, const Rect& rect, CollsionType type);
	Collsion(Actor& owner);
	void SetRect();
	void SetPosition(const Position2& pos);
	void Rect() const;
};
