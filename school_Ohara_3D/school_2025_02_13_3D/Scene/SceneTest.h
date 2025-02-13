#pragma once
#include "SceneBase.h"
#include "DxLib.h"

class SceneTest : public SceneBase
{
public:
	SceneTest();
	virtual ~SceneTest() {}



	virtual void init() override;
	virtual void end() override;

	virtual SceneBase* update() override;
	virtual void draw() override;

private:
	// �J�����̈ʒu
	VECTOR m_cameraPos;
	// �J�����̒����_(���Ă���ꏊ)
	VECTOR m_cameraTarget;
	// �J�����̎���p
	float m_viewAngle;
	// 
	float m_cameraMoveAngle;
};