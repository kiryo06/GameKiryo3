#pragma once
// ゲーム中で使用する幾何学情報の型を定義する場所

/// <summary>
/// ベクトル(2D)
/// </summary>
struct Vector2
{
	float x, y;

	Vector2() : x(0.0f), y(0.0f) {}
	Vector2(const float& x, const float& y) : x(x), y(y) {}

	// やっぱcppに分けると見やすいな
	void operator+=(const Vector2& vec);
	void operator-=(const Vector2& vec);
	void operator*=(const float& scale);
	void operator/=(const float&   div);

	Vector2 operator+(const Vector2& right) const;
	Vector2 operator-(const Vector2& right) const;
	Vector2 operator*(const float&   right) const;
	Vector2 operator/(const float&   right) const;

	// 自分自身を変更するので注意
	void Normalize();
	// constついてるので安心してください
	Vector2 Normalized() const;
	float Length() const;
};

// 別名を作っただけ
using Position2 = Vector2;

/// <summary>
/// サイズ(2Dゲームで使用するピクセルサイズ)
/// </summary>
struct Size
{
	int w, h;
};

/// <summary>
/// 矩形(くけい)構造体
/// 矩形とは長方形のこと
/// </summary>
struct Rect
{
	Position2 center;//中心点
	Size size;//
	float Left() const;
	float Top() const;
	float Right() const;
	float Bottom() const;

	void Draw();
};

