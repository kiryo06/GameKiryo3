#pragma once
#include <cmath>

class Vec2
{
public:
	float x;
	float y;

	Vec2() :
		x(0.0f),
		y(0.0f)
	{
	}

	Vec2(float x, float y) :
		x(x),
		y(y)
	{
	}

	// ‰‰Zq
	Vec2 operator +() const
	{
		return *this;
	}

	Vec2 operator -() const
	{
		return Vec2{ -x,-y };
	}

	/// ‘«‚µZ
	Vec2 operator +(Vec2 vec) const
	{
		return Vec2{ x + vec.x, y + vec.y };
	}
	Vec2 operator +=(Vec2 vec)
	{
		x += vec.x;
		y += vec.y;
		return *this;
	}

	/// ˆø‚«Z
	Vec2 operator -(Vec2 vec) const
	{
		return Vec2{ x - vec.x, y - vec.y };
	}
	Vec2 operator -=(Vec2 vec)
	{
		x -= vec.x;
		y -= vec.y;
		return *this;
	}

	/// Š|‚¯Z
	Vec2 operator *(float scale) const
	{
		return Vec2{ x * scale, y * scale };
	}
	Vec2 operator *=(float scale)
	{
		x *= scale;
		y *= scale;
		return *this;
	}

	/// Š„‚èZ
	Vec2 operator /(float scale) const
	{
		return Vec2{ x / scale, y / scale };
	}
	Vec2 operator /=(float scale)
	{
		x /= scale;
		y /= scale;
		return *this;
	}

	bool operator !=(Vec2 vec)
	{
		return (static_cast<int>(x) != static_cast<int>(vec.x) || static_cast<int>(y) != (vec.y));
	}

	bool operator ==(Vec2 vec)	{
		return (static_cast<int>(x) == static_cast<int>(vec.x) && static_cast<int>(y) == (vec.y));
	}

	float WallLength(Vec2 a) const
	{
		return sqrtf(a.x * a.x + a.y * a.y);
	}

	/// <summary>
	/// ƒxƒNƒgƒ‹‚Ì’·‚³‚Ì2æ‚ğ‹‚ß‚é
	/// </summary>
	/// <returns>’·‚³‚Ì2æ</returns>
	float SqLength() const
	{
		return x * x + y * y;
	}

	/// <summary>
	/// ƒxƒNƒgƒ‹‚Ì’·‚³‚ğ‹‚ß‚é
	/// </summary>
	/// <returns>’·‚³</returns>
	float Length() const
	{
		return sqrtf(SqLength());
	}

	/// <summary>
	/// ©g‚Ì³‹K‰»‚ğs‚¤
	/// </summary>
	void Normalize()
	{
		float len = Length();

		// ’·‚³0ˆÈ‰º‚È‚çˆ—‚ğs‚í‚È‚¢
		if (len <= 0.0f) return;

		x /= len;
		y /= len;
	}
};