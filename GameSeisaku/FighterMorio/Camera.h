#pragma once

struct Player;
struct Camera
{
	VECTOR pos;				// ���ۂ̃J�����̃|�W�V����
	VECTOR drawOffset;		// �S�Ă�DrawObject�ɑ����l
};

void InitCamera(Camera& camera);
void UpdateCamera(Camera& camera, const Player& player);