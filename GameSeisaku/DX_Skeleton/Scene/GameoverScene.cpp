#include "../Application.h"
#include"../Input.h" // ←入力を取る
#include "GameoverScene.h"
#include "SceneController.h" // ←遷移するために
#include "TitleScene.h" // ←遷移したいシーン
#include <cassert>
#include <DxLib.h>

namespace
{
	constexpr int fade_interval = 60;
}

void GameoverScene::FadeInUpdate(Input& input)
{
	--frame_;
	if (frame_ <= 0)
	{
		update_ = &GameoverScene::NomalUpdate;
		draw_ = &GameoverScene::NomalDraw;
	}
}

void GameoverScene::NomalUpdate(Input& input)
{
	if (input.IsTrigger("next"))
	{
		update_ = &GameoverScene::FadeOutUpdate;
		draw_ = &GameoverScene::FadeDraw;
		frame_ = 0;
	}
}

void GameoverScene::FadeOutUpdate(Input& input)
{
	++frame_;
	if (frame_ >= fade_interval)
	{
		controller_.ChangeScene(std::make_shared<TitleScene>(controller_));
		return;
	}
}

void GameoverScene::FadeDraw()
{
	// 画面の中心出してるだけ
	const Size& wsize = Application::GetInstance().GetWindowSize();
	Position2 center = { static_cast<float>(wsize.w) * 0.5f, static_cast<float>(wsize.h) * 0.5f };
	DrawRotaGraph(static_cast<int>(center.x), static_cast<int>(center.y), 1.0f, 0.0f, backH_, true);
	auto rate = static_cast<float>(frame_) / static_cast<float>(fade_interval);
	SetDrawBlendMode(DX_BLENDMODE_MULA, static_cast<int>(255 * rate));
	DrawBox(0, 0, wsize.w, wsize.h, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void GameoverScene::NomalDraw()
{
	// 画面の中心出してるだけ
	const Size& wsize = Application::GetInstance().GetWindowSize();
	Position2 center = { static_cast<float>(wsize.w) * 0.5f, static_cast<float>(wsize.h) * 0.5f };
	DrawString(10, 10, "GameoverScene", 0xffffff);
	DrawRotaGraph(static_cast<int>(center.x), static_cast<int>(center.y), 1.0f, 0.0f, backH_, true);
}

GameoverScene::GameoverScene(SceneController& cont) :
	Scene(cont),
	update_(&GameoverScene::FadeInUpdate),
	draw_(&GameoverScene::FadeDraw),
	frame_(fade_interval),
	backH_(-1)
{
	backH_ = LoadGraph("image/snake.png");
	assert(backH_ != -1);
}

void GameoverScene::Update(Input& input)
{
	(this->*update_)(input);
}

void GameoverScene::Draw()
{
	(this->*draw_)();
}
