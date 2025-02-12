#include "../Application.h"
#include "../Game/Player.h"
#include "../Input.h"
#include "DxLib.h"
#include "GameoverScene.h"
#include "GameScene.h"
#include "PauseScene.h"
#include "SceneController.h"
#include <cmath>

namespace
{
	constexpr int fade_interval = 60;
	/*constexpr */
}

void GameScene::FadeInUpdate(Input& input)
{
	--frame_;
	if (frame_ <= 0)
	{
		update_ = &GameScene::NomalUpdate;
		draw_ = &GameScene::NomalDraw;
	}
}

void GameScene::NomalUpdate(Input& input)
{
	angle_ += 0.1f;

	// エンターキーが推されるまで何もしないぃ
	if (input.IsTrigger("next"))
	{
		update_ = &GameScene::FadeOutUpdate;
		draw_ = &GameScene::FadeDraw;
	}
	if (input.IsTrigger("pause"))
	{
		// Pキーが押されたら、ポーズシーンを乗っける
		controller_.PushScene(std::make_shared<PauseScene>(controller_));
	}
}

void GameScene::FadeOutUpdate(Input& input)
{
	++frame_;
	if (frame_ >= fade_interval)
	{
		controller_.ChangeScene(std::make_shared<GameoverScene>(controller_));
		return;
	}
}

void GameScene::FadeDraw()
{
	for (const auto& actor : actors_)
	{
		actor->Draw();
	}

	// 画面の中心出してるだけ
	const Size& wsize = Application::GetInstance().GetWindowSize();
	Position2 center = { static_cast<float>(wsize.w) * 0.5f, static_cast<float>(wsize.h) * 0.5f };
	auto rate = static_cast<float>(frame_) / static_cast<float>(fade_interval);
	SetDrawBlendMode(DX_BLENDMODE_MULA, static_cast<int>(255 * rate));
	DrawBox(0, 0, wsize.w, wsize.h, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void GameScene::NomalDraw()
{
	constexpr float scale = 3.0f;
	constexpr int chip_size = 16;
	constexpr int ground_idx_x = 192 / 16;
	constexpr int ground_idx_y = 0;
	for (int j = 0; j < 10; ++j)
	{
		for (int i = 0; i < 10; ++i)
		{
			DrawRectRotaGraphF((i * chip_size * scale) + (chip_size * scale / 2),
				(j * chip_size * scale) + (chip_size * scale / 2),
				ground_idx_x * chip_size, ground_idx_y * chip_size,
				chip_size, chip_size,
				scale, 0.0f,
				backH_, true);
		}
	}

	for (const auto& actor : actors_)
	{
		actor->Draw();
	}
}

void GameScene::DrawGround()
{
}

void GameScene::CheckHit()
{
	for (auto& actA : actors_)
	{
		for (auto& actB : actors_)
		{
			if (actA == actB)
			{
				continue;
			}
		}
	}
}

void GameScene::IsHit(const Rect& rcA, const Rect& rcB) const
{
	return !(fabsf(rcA.conter.x - rcB.conter.x) > (rcA.size.w - rcB.size.w))
}

// 派生クラスで基底クラスの初期化をする
GameScene::GameScene(SceneController& cont) :
	Scene(cont),
	frame_(fade_interval),
	update_(&GameScene::FadeInUpdate),
	draw_(&GameScene::FadeDraw),
	backH_(-1),
	angle_(0)
{
	backH_ = LoadGraph("image/texture.png");
	actors_.push_back(std::make_shared<Player>(*this));
}

void GameScene::Update(Input& input)
{
	for (auto& actor : actors_)
	{
		actor->Update(input);
	}

	(this->*update_)(input);
}

void GameScene::Draw()
{
	(this->*draw_)();
}
