#include "Geometry.h"
#include <cmath>
#include "DxLib.h"

void Vector2::operator+=(const Vector2& vec)
{
	x += vec.x;
	y += vec.y;
}

void Vector2::operator-=(const Vector2& vec)
{
	x -= vec.x;
	y -= vec.y;
}

void Vector2::operator*=(const float& scale)
{
	x *= scale;
	y *= scale;
}

void Vector2::operator/=(const float& div)
{
	x /= div;
	y /= div;
}

Vector2 Vector2::operator+(const Vector2& right) const
{
	// 波かっこで囲むと一時オブジェクトを作らなくていいので楽
	// しかも値のコピーが減るので速い
	return {x + right.x, y + right.y};
}

Vector2 Vector2::operator-(const Vector2& right) const
{
	return { x - right.x, y - right.y };
}

Vector2 Vector2::operator*(const float& right) const
{
	return { x * right, y * right };
}

Vector2 Vector2::operator/(const float& right) const
{
	return { x / right, y / right };
}

void Vector2::Normalize()
{
	float length = Length();

	if (length == 0.0f) return;

	x /= length;
	y /= length;
}

Vector2 Vector2::Normalized() const
{
	float length = Length();

	if (length == 0.0f) return {};

	return { x / length, y / length };
}

float Vector2::Length() const
{
	return hypotf(x, y);
}

float Rect::Left() const
{
	return center.x - size.w / 2;
}

float Rect::Top() const
{
	return center.y - size.h / 2;
}

float Rect::Right() const
{
	return center.x + size.w / 2;
}

float Rect::Bottom() const
{
	return center.y + size.h / 2;
}

void Rect::Draw()
{
	DrawBox(Left(),Top(),Right(),Bottom(),col,false,2.0f);
}
