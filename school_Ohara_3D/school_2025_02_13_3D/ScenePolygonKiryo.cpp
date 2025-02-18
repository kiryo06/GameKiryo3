#include "ScenePolygonKiryo.h"

ScenePolygonKiryo::ScenePolygonKiryo()
{
}

void ScenePolygonKiryo::init()
{
	SetUseZBuffer3D(true);		// Z�o�b�t�@���g�p����
	SetWriteZBuffer3D(true);	// Z�o�b�t�@�ւ̏������݂��s��

	SetUseBackCulling(true);	// �|���S���̗��ʂ�\�����Ȃ�

	// �J�����̐ݒ�

	// �J�����̈ʒu�ƒ����_���w�肷��
	//SetCameraPositionAndTarget_UpVecY(VGet(-200,200,720), VGet(0,0,0));
	SetCameraPositionAndTarget_UpVecY(VGet(0, 400, -360), VGet(0, 0, 0));

	// �J�����̎���p��ݒ肷��
	SetupCamera_Perspective(DX_PI_F / 3);	// 60�x

	// �J������near, far��ݒ肷��
	SetCameraNearFar(10.0f, 1800.0f);

	// �e�N�X�`���̓ǂݍ���
	m_textureHandle = LoadGraph("Data/car.jpg");
}

void ScenePolygonKiryo::end()
{
	// �e�N�X�`�����������J������
	DeleteGraph(m_textureHandle);
}

SceneBase* ScenePolygonKiryo::update()
{
	return nullptr;
}

void ScenePolygonKiryo::draw()
{
	VERTEX3D Vertex[1*3];	// ���_�f�[�^�̔z���3��������

	Vertex[0].pos = VGet(-200, 0, 200);	// ���_���W
	Vertex[0].norm = VGet(0, 1, 0);	// �@�� �|���S���̌����Ă������
	Vertex[0].dif = GetColorU8(255, 255, 255, 255);	// �f�t���[�Y?�J���[
	Vertex[0].spc = GetColorU8(255, 255, 255, 255);	// �X�y�L����?�J���[
	Vertex[0].u = 0.0f;		// �e�N�X�`�����W	����͎g��Ȃ�
	Vertex[0].v = 0.0f;
	Vertex[0].su = 0.0f;
	Vertex[0].sv = 0.0f;

	Vertex[1].pos = VGet(200, 0, 200);	// ���_���W
	Vertex[1].norm = VGet(0, 1, 0);	// �@�� �|���S���̌����Ă������
	Vertex[1].dif = GetColorU8(255, 255, 255, 255);	// �f�t���[�Y?�J���[
	Vertex[1].spc = GetColorU8(255, 255, 255, 255);	// �X�y�L����?�J���[
	Vertex[1].u = 0.5f;		// �e�N�X�`�����W	����͎g��Ȃ�
	Vertex[1].v = 0.0f;
	Vertex[1].su = 0.0f;
	Vertex[1].sv = 0.0f;

	Vertex[2].pos = VGet(-200, 0, -200);	// ���_���W
	Vertex[2].norm = VGet(0, 1, 0);	// �@�� �|���S���̌����Ă������
	Vertex[2].dif = GetColorU8(255, 255, 255, 255);	// �f�t���[�Y?�J���[
	Vertex[2].spc = GetColorU8(255, 255, 255, 255);	// �X�y�L����?�J���[
	Vertex[2].u = 0.0f;		// �e�N�X�`�����W	����͎g��Ȃ�
	Vertex[2].v = 1.0f;
	Vertex[2].su = 0.0f;
	Vertex[2].sv = 0.0f;













	// X���̐�	��
	DrawLine3D(VGet(-2000, 0, 0), VGet(2000, 0, 0), 0xff0000);
	// Y���̐�	��
	DrawLine3D(VGet(0, -2000, 0), VGet(0, 2000, 0), 0xffff00);
	// Z���̐�	��
	DrawLine3D(VGet(0, 0, -2000), VGet(0, 0, 2000), 0x00ff00);
	// 3D��ԏ�̍��W��2D���W�ɕϊ����ĕ�����ɕ\���������I
	VECTOR pos2D;
	pos2D = ConvWorldPosToScreenPos(VGet(330, 0, 0));
	DrawString(pos2D.x, pos2D.y, "X+", 0xffffff);
	pos2D = ConvWorldPosToScreenPos(VGet(-330, 0, 0));
	DrawString(pos2D.x, pos2D.y, "X-", 0xffffff);
	pos2D = ConvWorldPosToScreenPos(VGet(0, 330, 0));
	DrawString(pos2D.x, pos2D.y, "Y+", 0xffffff);
	pos2D = ConvWorldPosToScreenPos(VGet(0, -330, 0));
	DrawString(pos2D.x, pos2D.y, "Y-", 0xffffff);
	pos2D = ConvWorldPosToScreenPos(VGet(0, 0, 330));
	DrawString(pos2D.x, pos2D.y, "Z+", 0xffffff);
	pos2D = ConvWorldPosToScreenPos(VGet(0, 0, -330));
	DrawString(pos2D.x, pos2D.y, "Z-", 0xffffff);
	DrawString(0, 0, "�V��", 0xffffff);
}
