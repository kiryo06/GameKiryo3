#include "Vector3.h"
#include <math.h>
/*
bool Vector3::AddVecter(Vector3& v1,Vector3& v2)
{
	Vector3 ret;
	ret.x = v1.x + v2.x;
	ret.y = v1.y + v2.y;
	ret.z = v1.z + v2.z;
	return;
}

bool Vector3::SudVecter(Vector3& v1, Vector3& v2)
{
	Vector3 ret;
	ret.x = v1.x - v2.x;
	ret.y = v1.y - v2.y;
	ret.z = v1.z - v2.z;
	return;
}

bool Vector3::ScaleVector(Vector3& vec, float size)
{
	Vector3 ret;
	ret.x = vec.x * size;
	ret.y = vec.y * size;
	ret.z = vec.z * size;
	return;
}

bool Vector3::NormalizeVector()
{
	return false;
}

float Vector3::GetVectorLength()
{
	return 0.0f;
}
//*/

//------------------------------//
// �x�N�g�����m�̑����Z.
//------------------------------//
Vector AddVector(Vector& v1, Vector& v2)
{
	Vector ret;
	ret.x = v1.x + v2.x;
	ret.y = v1.y + v2.y;
	ret.z = v1.z + v2.z;
	return ret;
}

//------------------------------//
// �x�N�g�����m�̈����Z.
//------------------------------//
Vector SubVector(Vector& v1, Vector& v2)
{
	Vector ret;
	ret.x = v1.x - v2.x;
	ret.y = v1.y - v2.y;
	return ret;
}

//------------------------------//
// �x�N�g���̃X�J���[�{.
//------------------------------//
Vector ScaleVector(Vector& vec, float size)
{
	Vector ret;
	ret.x = vec.x * size;
	ret.y = vec.y * size;
	return ret;
}

//--------------------------------//
// �x�N�g���̒���.
//--------------------------------//
float GetVectorLength(Vector& vec)
{
	return (float)sqrt((vec.x * vec.x) + (vec.y * vec.y));
}

//------------------------------//
// �x�N�g���̐��K��.
//------------------------------//
Vector NormalizeVector(Vector& vec)
{
	Vector ret;
	ret.x = ret.y = 0.0f;
	float length = GetVectorLength(vec);
	if (length != 0)
	{
		ret.x = vec.x / length;
		ret.y = vec.y / length;
	}
	return ret;
}