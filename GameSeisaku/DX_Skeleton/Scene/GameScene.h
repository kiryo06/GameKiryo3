#pragma once
#include "Scene.h"
#include <vector>
#include <memory>

class Actor;

class GameScene : public Scene
{
private:
	int frame_ = 60;
	float angle_;
	void FadeInUpdate(Input& input);
	void NomalUpdate(Input& input);
	void FadeOutUpdate(Input& input);

	void FadeDraw();
	void NomalDraw();

	using UpdateFunc_t = void (GameScene::*)(Input& input);
	using DrawFunc_t = void (GameScene::*)();

	UpdateFunc_t update_;
	DrawFunc_t draw_;

	int backH_;

	using ActorVector_t = std::vector<std::shared_ptr<Actor>>;
	ActorVector_t actors_;

	void DrawGround();
	void CheckHit();
	void IsHit(const Rect& rcA, const Rect& rcB)const;
public:
	GameScene(SceneController& cont);
	/// <summary>
	/// îhê∂ÉNÉâÉXÇ≈é¿ëïÇé¿ëï
	/// </summary>
	virtual void Update(Input& input) override;

	virtual void Draw() override;
};


