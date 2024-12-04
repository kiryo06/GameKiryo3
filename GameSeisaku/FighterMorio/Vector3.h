#pragma once
/*
class Vector3
{
public:
	/// <summary>
	/// �x�N�g���̑����Z
	/// </summary>
	/// <returns></returns>
	bool AddVecter(Vector3& v1, Vector3& v2);
	/// <summary>
	/// �x�N�g�����m�̈����Z
	/// </summary>
	/// <returns></returns>
	bool SudVecter(Vector3& v1, Vector3& v2);
	/// <summary>
	/// �x�N�g���̃X�J���[�{
	/// </summary>
	/// <returns></returns>
	bool ScaleVector(Vector3& vec, float size);
	/// <summary>
	/// �x�N�g���̒���
	/// </summary>
	/// <returns></returns>
	float GetVectorLength();
	/// <summary>
	/// �x�N�g���̐��K��
	/// </summary>
	/// <returns></returns>
	bool NormalizeVector();
private:
	float x;
	float y;
	float z;
};
//*/


struct Vector
{
	float x;
	float y;
	float z;
};

Vector AddVector(Vector& v1, Vector& v2);
Vector SubVector(Vector& v1, Vector& v2);
Vector ScaleVector(Vector& vec, float size);
Vector NormalizeVector(Vector& vec);
float GetVectorLength(Vector& vec);
Vector NormalizeVector(Vector& vec);