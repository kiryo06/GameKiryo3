#pragma once
#include "Scene.h"

/// <summary>
/// タイトルシーン
/// </summary>
class TitleScene : public Scene
{
private:
	int frame_ = 0;
	// 背景
	int backH_ = -1;

	using UpdateFunc_t = void (TitleScene::*) (Input&);
	using DrawFunc_t = void (TitleScene::*) ();

	UpdateFunc_t update_;
	DrawFunc_t draw_;

	// フェードイン時のUpdate
	void FadeInUpdate(Input&);
	// とか
	void FadeOutUpdate(Input&);
	// そうでなかったり
	void NormalUpdate(Input&);

	// 描画
	void FadeDraw();
	void NormalDraw();

public:
	TitleScene(SceneController& cont);
	/// <summary>
	/// 派生クラスで実装を実装
	/// virtual はこれを継承するかもしれないから、
	/// overrideは明示的にオーバーライドをエディタに示すため
	/// </summary>
	virtual void Update(Input& input) override;

	virtual void Draw() override;
};

