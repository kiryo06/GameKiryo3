#pragma once
#include "Scene.h"
class ContinueScene :
    public Scene
{
public:
	ContinueScene(SceneController& cont);
	/// <summary>
	/// �h���N���X�Ŏ���������
	/// </summary>
	virtual void Update(Input& input) override;

	virtual void Draw() override;
};

