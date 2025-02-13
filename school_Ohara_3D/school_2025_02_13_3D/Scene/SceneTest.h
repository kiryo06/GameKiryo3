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
	// カメラの位置
	VECTOR m_cameraPos;
	// カメラの注視点(見ている場所)
	VECTOR m_cameraTarget;
	// カメラの視野角
	float m_viewAngle;
	// 
	float m_cameraMoveAngle;
};