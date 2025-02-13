#pragma once
#include "SceneBase.h"

#include "DxLib.h"

class SceneTest : public SceneBase
{
public:
	SceneTest() 
	{
	}
	virtual ~SceneTest() {}


	virtual void init() override;
	virtual void end() override;

	virtual SceneBase* update() override;
	virtual void draw() override;

private:
	// ƒ‚ƒfƒ‹ƒnƒ“ƒhƒ‹
	int m_model;
	VECTOR m_modelPos;
	bool isHitX;
	bool isHitZ;
	int m_model2;
	VECTOR m_modelRot;
};