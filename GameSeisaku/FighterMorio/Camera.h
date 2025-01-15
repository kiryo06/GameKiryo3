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
	VECTOR GetCameraPos() const { return pos; }
	VECTOR GetCameraDrawOffset() const { return drawOffset; }
private:
	VECTOR pos;				// 実際のカメラのポジション
	VECTOR drawOffset;		// 全てのDrawObjectに足す値
};