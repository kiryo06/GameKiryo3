#include "DxLib.h"
#include "game.h"
#include "SceneTest.h"
#include <cmath>
#include "Pad.h"


namespace
{
}

SceneTest::SceneTest():
	m_viewAngle(0.0f),
	m_cameraMoveAngle(0.0f)
{
}

void SceneTest::init()
{
	SetUseZBuffer3D(true);		// Z�o�b�t�@���g�p����
	SetWriteZBuffer3D(true);	// Z�o�b�t�@�ւ̏������݂��s��
	SetUseBackCulling(true);	// �|���S���̗��ʂ�\�����Ȃ�

	// �J�����̏��������s��
	// 600*600�̃O���b�h����ʒ���������ɗ���悤�ɐݒ�
	// �J����(���_)�̈ʒu
	m_cameraPos.x = 0.0f;
	m_cameraPos.y = 200.0f;
	m_cameraPos.z = 720.0f;

	// �J�������ǂ��������Ă��邩(�����_)
	m_cameraTarget.x = 0.0f;
	m_cameraTarget.y = 200.0f;
	m_cameraTarget.z = 0.0f;

	// �J�����̈ʒu�ƒ����_���w�肷��
	SetCameraPositionAndTarget_UpVecY(m_cameraPos, m_cameraTarget);



	// �J�����̎���p��ݒ肷��
	m_viewAngle = DX_PI_F / 3.0f;	// 60�x
	SetupCamera_Perspective(m_viewAngle);



	// �J������near, far��ݒ肷��
	// ��ʂɕ\������鋗���͈̔͂�ݒ肷��
	// �J��������near�ȏ㗣��Ă��āAfar���߂��ɂ�����̂�
	// �Q�[�����ɕ\�������
	// far�͂��܂�傫�����鐔����ݒ肵�Ȃ��悤�ɋC��t����(�\���o�O�ɂȂ���)
	SetCameraNearFar(10.0f, 1800.0f);
}

void SceneTest::end()
{

}

SceneBase* SceneTest::update()
{
	// �J�����̈ʒu����]������
	m_cameraMoveAngle += 0.02f;
	m_cameraPos.x = cosf(m_cameraMoveAngle) * 720.0f;
	m_cameraPos.z = sinf(m_cameraMoveAngle) * 720.0f;


	if (Pad::isPress(PAD_INPUT_3))
	{
		m_cameraTarget.x += 20.0f;
	}
	SetCameraPositionAndTarget_UpVecY(m_cameraPos, m_cameraTarget);





	// �{�^���ŃJ�����̎���p��ύX����
	if (Pad::isPress(PAD_INPUT_1))
	{
		m_viewAngle -= 0.01f;
		if (m_viewAngle < DX_PI_F / 180.0f * 5.0f)
		{
			m_viewAngle < DX_PI_F / 180.0f * 5.0f;
		}
	}
	if (Pad::isPress(PAD_INPUT_B))
	{
		m_viewAngle += 0.01f;
		if (m_viewAngle < DX_PI_F / 180.0f * 120.0f)
		{
			m_viewAngle < DX_PI_F / 180.0f * 120.0f;
		}
	}
	SetupCamera_Perspective(m_viewAngle);
	return this;
}

void SceneTest::draw()
{
	// �O�p�`
	VECTOR Pos1,Pos2,Pos3;
	Pos1 = VGet(-300,  300,   0);
	Pos2 = VGet( 300,  300,   0);
	Pos3 = VGet(-300, -300,   0);
	DrawTriangle3D(Pos1, Pos2, Pos3, 0x00ff00, true);

	Pos1 = VGet( 300, -300,   0);
	Pos2 = VGet( 300,  300,   0);
	Pos3 = VGet(-300, -300,   0);
	DrawTriangle3D(Pos1, Pos2, Pos3, 0x00ff00, true);

	Pos1 = VGet(-300,   0,  300);
	Pos2 = VGet( 300,   0,  300);
	Pos3 = VGet(-300,   0, -300);
	DrawTriangle3D(Pos1, Pos2, Pos3, 0x0000ff, true);



	// ����
	VECTOR Posball;
	float Hankei;
	int vertex;
	Posball.x = 0.0f;
	Posball.y = 200.0f;
	Posball.z = 0.0f;
	Hankei = 128.0f;
	vertex = 200;
	DrawSphere3D(Posball, Hankei, vertex, 0xffffff, true, true);














	// VECTOR�\����
	// 3D���W��\������̂ɕK�v��x,y,z��3�������o�[�Ƃ��Ď��\����
	VECTOR start;	// �n�_
	VECTOR end;		// �I�_

	start.x = -300.0f;
	start.y = 0.0f;
	start.z = 0.0f;

	end.x = 300.0f;
	end.y = 0.0f;
	end.z = 0.0f;
	// �������̃O���b�h��for�����g���ĕ`�悷��
	// �n�_�I�_��XY���W�͕ς��Ȃ�
	// Z�̂�for�����g���ĕω�������
	for (float z = -300.0f; z <= 300.0f; z += 100.0f)
	{
		start.z = z;
		end.z = z;
		DrawLine3D(start, end, 0xff0000);
	}

	// ���s�O���b�h�𓯗l�Ɉ���
	start.x = 0.0f;
	start.y = 0.0f;
	start.z = -300.0f;

	end.x = 0.0f;
	end.y = 0.0f;
	end.z = 300.0f;

	for (float x = -300.0f; x <= 300.0f; x += 100.0f)
	{
		start.x = x;
		end.x = x;
		DrawLine3D(start, end, 0xffff00);
	}
	// �����O���b�h�𓯗l�Ɉ���
	start.x = 0.0f;
	start.y = -1200.0f;
	start.z = 0.0f;

	end.x = 0.0f;
	end.y = 1200.0f;
	end.z = 0.0f;
	DrawLine3D(start, end, 0x00ffff);














	DrawFormatString(0, 16, 0xffffff, "FOV : %f", m_viewAngle, true);
	DrawString(  0,   0, "3D�̕׋�", 0xffffff);	// X,Y���W�łǂ��ɕ\�����Ă��邩
//	DrawString(128,   0, "3D�̕׋�", 0xffffff);
//	DrawString(  0, 128, "3D�̕׋�", 0xffffff);
}

