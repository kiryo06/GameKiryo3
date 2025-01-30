#pragma once
#include "DxLib.h"
class Player;
class Camera
{
public:
	Camera();
	~Camera();
	void Init();
	void Update(Player* player);
	/// <summary>
	/// �J�����̖ڕW�|�W�V�������v�Z
	/// </summary>
	/// <param name="playerPos"></param>
	/// <returns></returns>
	VECTOR CalculateAimCameraPos(const VECTOR& playerPos);
	void ClampCameraPos();
	void UpdateDrawOffset();
	VECTOR GetCameraPos() const { return pos; }
	VECTOR GetCameraDrawOffset() const { return drawOffset; }
	bool GetPlayerLeftHit()const { return isLeftHit; }
private:
	VECTOR pos;				// ���ۂ̃J�����̃|�W�V����
	VECTOR drawOffset;		// �S�Ă�DrawObject�ɑ����l
	bool isLeftHit;
};