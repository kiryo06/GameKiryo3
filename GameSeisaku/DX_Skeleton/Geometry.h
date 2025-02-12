#pragma once
// �Q�[�����Ŏg�p����􉽊w���̌^���`����ꏊ

/// <summary>
/// �x�N�g��(2D)
/// </summary>
struct Vector2
{
	float x, y;

	Vector2() : x(0.0f), y(0.0f) {}
	Vector2(const float& x, const float& y) : x(x), y(y) {}

	// �����cpp�ɕ�����ƌ��₷����
	void operator+=(const Vector2& vec);
	void operator-=(const Vector2& vec);
	void operator*=(const float& scale);
	void operator/=(const float&   div);

	Vector2 operator+(const Vector2& right) const;
	Vector2 operator-(const Vector2& right) const;
	Vector2 operator*(const float&   right) const;
	Vector2 operator/(const float&   right) const;

	// �������g��ύX����̂Œ���
	void Normalize();
	// const���Ă�̂ň��S���Ă�������
	Vector2 Normalized() const;
	float Length() const;
};

// �ʖ������������
using Position2 = Vector2;

/// <summary>
/// �T�C�Y(2D�Q�[���Ŏg�p����s�N�Z���T�C�Y)
/// </summary>
struct Size
{
	int w, h;
};

/// <summary>
/// ��`(������)�\����
/// ��`�Ƃ͒����`�̂���
/// </summary>
struct Rect
{
	Position2 center;//���S�_
	Size size;//
	float Left() const;
	float Top() const;
	float Right() const;
	float Bottom() const;

	void Draw();
};

