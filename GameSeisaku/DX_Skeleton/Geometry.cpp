#include "Geometry.h"
#include <cmath>

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
	// �g�������ň͂ނƈꎞ�I�u�W�F�N�g�����Ȃ��Ă����̂Ŋy
	// �������l�̃R�s�[������̂ő���
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
