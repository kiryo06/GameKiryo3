#include "../Application.h"
#include "../Input.h"
#include "KeyConfigScene.h"
#include "PauseScene.h"
#include "SceneController.h"
#include "TitleScene.h"
#include <DxLib.h>

namespace
{
	constexpr int appear_interval = 20;
	constexpr int frame_margin = 10; // ゲーム画面からポーズ画面までの幅
	constexpr int menu_text_start_y = 150; // メニュー画面のテキストが表示される初期y座標
	constexpr int menu_text_left = 250; // メニューのX座標のオフセット
	constexpr int menu_row_height = 50; // メニュー一項目当たりの高さ
	constexpr int menu_selector_left = 20;
}

void PauseScene::AppearUpdate(Input& input)
{
	++frame_;
	if (frame_ >= appear_interval)
	{
		update_ = &PauseScene::NomalUpdate;
		draw_ = &PauseScene::NomalDraw;
		return;
	}
}

void PauseScene::NomalUpdate(Input& input)
{
	// Pボタンでポーズ画面解除
	if (input.IsTrigger("pause"))
	{
		update_ = &PauseScene::DisappearUpdate;
		draw_ = &PauseScene::ShiftingDraw;
		frame_ = appear_interval;
		return; // 忘れずにreturn
	}
	else if (input.IsTrigger("up"))
	{
		// if文でもできるけど分岐はできるだけ縛る
		// C++11以前は負の数のあまりは未定義だったらしい
		--currentMenuIndex_;
		currentMenuIndex_ = currentMenuIndex_ % menuTexts_.size();
	}
	else if (input.IsTrigger("down"))
	{
		++currentMenuIndex_;
		currentMenuIndex_ = currentMenuIndex_ % menuTexts_.size();
	}
	else if (input.IsTrigger("ok"))
	{
		// mapの中にmap
		(this->*functionTable_.at(menuTexts_.at(currentMenuIndex_)))(input);
	}
}

void PauseScene::DisappearUpdate(Input& input)
{
	--frame_;
	if (frame_ <= 0)
	{
		controller_.PopScene();
		return;
	}
}

void PauseScene::NomalDraw()
{
	const auto& wsize = Application::GetInstance().GetWindowSize();
	// ポーズ画面枠
	DrawBoxAA(10.0f, 10.0f,// 左上
		wsize.w - 10.0f, wsize.h - 10.0f, // 右下
		0xffffff, // 色
		false, // 塗りつぶさない
		3.0f); // 線太い
	// 透過よ
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(10, 10,// 左上
		wsize.w - 10, wsize.h - 10, // 右下
		0xffffff, // 色
		true); // 塗りつぶす
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// メニューの文字を出す
	DrawMenu();
}

void PauseScene::ShiftingDraw()
{
	const auto& wsize = Application::GetInstance().GetWindowSize();
	// ウィジェットの高さを計算する(上下の幅分小さく)
	const int frameHeight = wsize.h - 10 - 10;
	// 上下に広がる感じか
	const int middleY = (10 + wsize.h - 10) / 2; // 真ん中のY座標
	// 0~1
	float rate = static_cast<float>(frame_) / static_cast<float>(appear_interval);
	// frameが進むごとにここは0～frameHeightの半分まで大きくなる
	int halfHeight = static_cast<int>(frameHeight * rate / 2);
	// ここから、topとbottomを計算。
	int top = middleY - halfHeight;
	int bottom = middleY + halfHeight;
	// ポーズ画面枠
	DrawBoxAA(10.0f, static_cast<float>(top),// 左上
		wsize.w - 10.0f, static_cast<float>(bottom), // 右下
		0xffffff, // 色
		false, // 塗りつぶさない
		3.0f); // 線太い
	// 透過よ
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(10, top,// 左上
		wsize.w - 10, bottom, // 右下
		0xffffff, // 色
		true); // 塗りつぶす
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	// 出現演出が終了したら
	if (frame_ > appear_interval)
	{
		// 状態遷移
		update_ = &PauseScene::NomalUpdate;
		draw_ = &PauseScene::NomalDraw;
		return;
	}
}

void PauseScene::DrawMenu()
{
	int y = frame_margin + menu_text_start_y;
	int x = frame_margin + menu_text_left;

	for (int i = 0; i < menuTexts_.size(); ++i)
	{
		int menu_offset = 0;
		unsigned int color = 0x2222ff;
		// 選ばれてたら、強調表示
		if (i == currentMenuIndex_)
		{
			DrawString(x - menu_selector_left + 1, y + 1, "⇒", 0x000000);
			DrawString(x - menu_selector_left, y, "⇒", 0xff0000);
			menu_offset = 10;
			color = 0xff0000;
		}
		// 影
		const auto& text = menuTexts_[i];
		DrawFormatString(menu_offset + x + 1, y + 1, 0x000000, "%s", text.c_str());
		DrawFormatString(menu_offset + x, y, color, "%s", text.c_str());
		y += menu_row_height;
	}
}

void PauseScene::BackGame(Input&)
{
	update_ = &PauseScene::DisappearUpdate;
	draw_ = &PauseScene::ShiftingDraw;
}

void PauseScene::GoKeyConfig(Input& input)
{
	controller_.PushScene(std::make_shared<KeyConfigScene>(controller_, input));
}

void PauseScene::EtcConfig(Input&)
{
}

void PauseScene::BackTitle(Input&)
{
	controller_.ChangeBaseScene(std::make_shared<TitleScene>(controller_));
	controller_.PopScene();
}

PauseScene::PauseScene(SceneController& cont) :
	Scene(cont),
	update_(&PauseScene::AppearUpdate),
	draw_(&PauseScene::ShiftingDraw),
	frame_(0),
	currentMenuIndex_(0)
{
	// メニューを用意
	menuTexts_ =
	{
		"ゲームに戻る",
		"キーコンフィグ",
		"その他設定",
		"タイトルに戻る"
	};
	functionTable_ =
	{
		{"ゲームに戻る", &PauseScene::BackGame},
		{"キーコンフィグ", &PauseScene::GoKeyConfig},
		{"その他設定", &PauseScene::EtcConfig},
		{"タイトルに戻る", &PauseScene::BackTitle},
	};
}

void PauseScene::Update(Input& input)
{
	(this->*update_)(input);
}

void PauseScene::Draw()
{
	(this->*draw_)();
}
