#pragma once
#include "Scene.h"

class GameoverScene : public Scene
{
private:
	int frame_ = 60;
	void FadeInUpdate(Input& input);
	void NomalUpdate(Input& input);
	void FadeOutUpdate(Input& input);

	void FadeDraw();
	void NomalDraw();

	using UpdateFunc_t = void (GameoverScene::*)(Input& input);
	using DrawFunc_t = void (GameoverScene::*)();

	UpdateFunc_t update_;
	DrawFunc_t draw_;

	int backH_;
public:
	GameoverScene(SceneController& cont);
	/// <summary>
	/// ”h¶ƒNƒ‰ƒX‚ÅÀ‘•‚ğÀ‘•
	/// </summary>
	virtual void Update(Input& input) override;

	virtual void Draw() override;
};

