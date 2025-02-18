#pragma once
#include "SceneBase.h"
#include "DxLib.h"
class ScenePolygonKiryo :
    public SceneBase
{
public:
	ScenePolygonKiryo();
	virtual ~ScenePolygonKiryo() {}


	virtual void init() override;
	virtual void end() override;

	virtual SceneBase* update() override;
	virtual void draw() override;

private:
	int m_textureHandle;
};