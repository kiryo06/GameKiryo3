#pragma once

//struct Player;
class Camera
{
public:
	Camera();
	~Camera();
	void Init();
	void Update();
	VECTOR GetCameraPos() { return pos; }
	VECTOR GetCameraDrawOffset() { return drawOffset; }
private:
	VECTOR pos;				// 実際のカメラのポジション
	VECTOR drawOffset;		// 全てのDrawObjectに足す値
};