#include "Collsion.h"

Collsion::Collsion(Actor& owner, const Rect& rect, CollsionType type):
    owner_(owner), 
    rect_(rect), 
    type_(type)
{
}

Collsion::Collsion(Actor& owner)
{
}

void Collsion::SetRect()
{
}

void Collsion::SetPosition(const Position2& pos)
{
}

void Collsion::Rect() const
{
}
