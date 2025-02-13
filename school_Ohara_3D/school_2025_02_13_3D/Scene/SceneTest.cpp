#include "DxLib.h"
#include "game.h"
#include "SceneTest.h"


namespace
{

}

void SceneTest::init()
{
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
}

void SceneTest::end()
{

}

SceneBase* SceneTest::update()
{

	return this;
}

void SceneTest::draw()
{
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
	for (int z = -300; z <= 300; z += 100)
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

	for (int x = -300; x <= 300; x += 100)
	{
		start.x = x;
		end.x = x;
		DrawLine3D(start, end, 0xffff00);
	}

	DrawString(  0,   0, "3D�̕׋�", 0xffffff);	// X,Y���W�łǂ��ɕ\�����Ă��邩
//	DrawString(128,   0, "3D�̕׋�", 0xffffff);
//	DrawString(  0, 128, "3D�̕׋�", 0xffffff);
}

