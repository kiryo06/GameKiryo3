#pragma once
#include "Scene.h"
class ContinueScene :
    public Scene
{
public:
	ContinueScene(SceneController& cont);
	/// <summary>
	/// ”h¶ƒNƒ‰ƒX‚ÅÀ‘•‚ğÀ‘•
	/// </summary>
	virtual void Update(Input& input) override;

	virtual void Draw() override;
};

