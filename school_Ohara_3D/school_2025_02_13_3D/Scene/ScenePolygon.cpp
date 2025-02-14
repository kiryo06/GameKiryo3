#include "ScenePolygon.h"

ScenePolygon::ScenePolygon()
{
}

void ScenePolygon::init()
{
	SetUseZBuffer3D(true);		// Z�o�b�t�@���g�p����
	SetWriteZBuffer3D(true);	// Z�o�b�t�@�ւ̏������݂��s��

	SetUseBackCulling(true);	// �|���S���̗��ʂ�\�����Ȃ�

	// �J�����̐ݒ�
	
	// �J�����̈ʒu�ƒ����_���w�肷��
	SetCameraPositionAndTarget_UpVecY(VGet(-200,200,720), VGet(0,0,0));

	// �J�����̎���p��ݒ肷��
	SetupCamera_Perspective(DX_PI_F / 3);	// 60�x

	// �J������near, far��ݒ肷��
	SetCameraNearFar(10.0f, 1800.0f);
}

void ScenePolygon::end()
{
}

SceneBase* ScenePolygon::update()
{
	return this;
}

void ScenePolygon::draw()
{
	// X���̐�	��
	DrawLine3D(VGet(-100, 0, 0), VGet(100, 0, 0), 0xff0000);
	// Y���̐�	��
	DrawLine3D(VGet(0, -100, 0), VGet(0, 100, 0), 0xffff00);
	// Z���̐�	��
	DrawLine3D(VGet(0, 0, -100), VGet(0, 0, 100), 0x00ff00);


	DrawString(0, 0, "ScenePolygon", 0xffffff);
}
