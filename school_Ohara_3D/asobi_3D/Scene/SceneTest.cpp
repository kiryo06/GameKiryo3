#include "DxLib.h"
#include "game.h"
#include "SceneTest.h"

namespace
{

}

void SceneTest::init()
{
	SetCameraPositionAndTarget_UpVecY(VGet(0,200, -720), VGet(0, 200, 0));
	SetupCamera_Perspective(DX_PI_F / 3);
	SetCameraNearFar(10.0f, 1800.0f);

	m_model = MV1LoadModel("Data/Character2.mv1");

	m_modelPos = VGet(0, 0, 0);
	isHitX = false;
	isHitZ = false;
	m_model2 = MV1DuplicateModel(m_model);

	m_modelRot = VGet(0, 0, 0);
}

void SceneTest::end()
{
	MV1DeleteModel(m_model);
	MV1DeleteModel(m_model2);
}

SceneBase* SceneTest::update()
{
	// モデルを移動させる
	if (!isHitX && m_modelPos.x > 300)
	{
		isHitX = true;
	}
	if (isHitX && m_modelPos.x < -300)
	{
		isHitX = false;
	}
	if (isHitX)
	{
		m_modelPos.x -= 10.0f;
	}
	else
	{
		m_modelPos.x += 10.0f;
	}

	if (!isHitZ && m_modelPos.z > 300)
	{
		isHitZ = true;
	}
	if (isHitZ && m_modelPos.z < -300)
	{
		isHitZ = false;
	}

	if (isHitX)
	{
		m_modelPos.x -= 10.0f;
	}
	else
	{
		m_modelPos.x += 10.0f;
	}
	if (isHitZ)
	{
		m_modelPos.z -= 10.0f;
	}
	else
	{
		m_modelPos.z += 10.0f;
	}
	MV1SetPosition(m_model, m_modelPos);


	// モデルを回転させる
	m_modelRot.y += 0.5f;
	MV1SetRotationXYZ(m_model, m_modelRot);
	MV1SetRotationXYZ(m_model2, m_modelRot);
	return this;
}

void SceneTest::draw()
{
	//　グリッド  X
	for (int x = -300; x <= 300; x += 100)
	{
		DrawLine3D(VGet(x, 0, -300), VGet(x, 0, 300), 0xff0000);
	}
	//　グリッド  Y
	DrawLine3D(VGet(0, -600, 0), VGet(0, 600, 0), 0x00ffff);

	//　グリッド  Z
	for (int z = -300; z <= 300; z += 100)
	{
		DrawLine3D(VGet(-300, 0, z), VGet(300, 0, z), 0xffff00);
	}

	MV1DrawModel(m_model);
	//MV1DrawModel(m_model2);
#ifdef _DEBUG
	DrawString(0, 0, "3Dの遊び", 0xffffff);
#endif // _DEBUG
}

