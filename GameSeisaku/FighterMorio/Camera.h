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
	VECTOR pos;				// ���ۂ̃J�����̃|�W�V����
	VECTOR drawOffset;		// �S�Ă�DrawObject�ɑ����l
};