#include "../Application.h"
#include "../Input.h"
#include "DxLib.h"
#include "GameScene.h"
#include "SceneController.h"
#include "TitleScene.h"
#include <cassert>

namespace
{
	// スネークケースとは…
	constexpr int fade_interval = 60;
}

void TitleScene::FadeInUpdate(Input&)
{
	--frame_;
	// これがトリガーか
	if (frame_ <= 0)
	{
		update_ = &TitleScene::NormalUpdate;
		draw_ = &TitleScene::NormalDraw;
	}
}

void TitleScene::FadeOutUpdate(Input&)
{
	++frame_;

	// つまりこの後にシーン遷移がしたいってことね
	if (frame_ >= 60)
	{
		controller_.ChangeScene(std::make_shared<GameScene>(controller_));
		// 自分を殺すのなんかあれだな、エモいな()
		// 今は実装がないが、この後の処理を無効にする(もう死ぬので)
		return;
	}
	// 何かあった場合、returnがなければ持ち主が死んでいるので
	// 何かゾンビ処理をすることになる←いろいろまずいことになる
}

void TitleScene::NormalUpdate(Input& input)
{
	// エンターキーが推されるまで何もしないぃ
	if (input.IsTrigger("next"))
	{
		update_ = &TitleScene::FadeOutUpdate;
		draw_ = &TitleScene::FadeDraw;
	}
}

void TitleScene::FadeDraw()
{
	// 画面の中心出してるだけ
	const Size& wsize = Application::GetInstance().GetWindowSize();

	// おなじみ透過描画を超速で実装
	// まずフェード割合の計算
	float rate = static_cast<float>(frame_) / static_cast<float>(fade_interval);
	// この書き方なら引数のパラメータを0~1にできるらしい
	SetDrawBlendMode(DX_BLENDMODE_MULA, static_cast<int>(255 * rate));
	DrawBox(0, 0, wsize.w, wsize.h, 0x000000, true);
	// BlendModeを使用した後はNoblendを忘れない
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void TitleScene::NormalDraw()
{
	DrawString(10, 10, "Title Scene", 0xffffff);
}

// 
TitleScene::TitleScene(SceneController& cont) :
	Scene(cont),
	update_(&TitleScene::FadeInUpdate),
	draw_(&TitleScene::FadeDraw),
	frame_(fade_interval)
{
	// ロード
	 backH_ = LoadGraph("image/halloween_mark_pumpkin.png");
	 assert(backH_ != -1);
}

void TitleScene::Update(Input& input)
{
	(this->*update_) (input);
}

void TitleScene::Draw()
{
	// 画面の中心出してるだけ
	const Size& wsize = Application::GetInstance().GetWindowSize();
	Position2 center = { static_cast<float>(wsize.w) * 0.5f, static_cast<float>(wsize.h) * 0.5f };
	// 背景の表示
	DrawRotaGraph(static_cast<int>(center.x), static_cast<int>(center.y), 1.0, 0.0f, backH_, true);
	// 実行
	// これは画面効果とかの描画に使ったらいいかも
	(this->*draw_) ();
}
