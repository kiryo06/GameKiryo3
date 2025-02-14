#pragma once
#include "SceneBase.h"
#include "DxLib.h"
class ScenePolygon : 
	public SceneBase
{
public:
	ScenePolygon();
	virtual ~ScenePolygon() {}


	virtual void init() override;
	virtual void end() override;

	virtual SceneBase* update() override;
	virtual void draw() override;

private:

};

