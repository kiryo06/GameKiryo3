#include "../Application.h"
#include "../Input.h"
#include "KeyConfigScene.h"
#include "SceneController.h"
#include <DxLib.h>
#include <map>
#include <string>
#include <vector>

namespace
{
	constexpr int appear_interval = 20;
	constexpr int frame_margin = 10; // ゲーム画面からポーズ画面までの幅
	constexpr int config_text_start_y = 50; // キーコンフィグ画面のテキストが表示される初期y座標
	constexpr int config_text_left = 150; // キーコンフィグのX座標のオフセット
	constexpr int config_row_height = 30; // キーコンフィグ一項目当たりの高さ
	constexpr int arrow_offset = 100; // キー以外
	constexpr int config_selector_left = 20;
	constexpr unsigned int base_color = 0xaaffaa; // 明るい緑 キーコンフィグのカラー
	constexpr unsigned int bg_alpha = 220; // ほぼ不透明
}

void KeyConfigScene::AppearUpdate(Input& input)
{
	++frame_;
	if (frame_ >= appear_interval)
	{
		update_ = &KeyConfigScene::NomalUpdate;
		draw_ = &KeyConfigScene::NomalDraw;
		return;
	}
}

void KeyConfigScene::NomalUpdate(Input& input)
{
	// もとのキーの数+戻る、確定を用意
	const int itemCount = static_cast<int>(input.orderForDisplay.size() + menuString_.size());

	if (input.IsTrigger("pause"))
	{
		CloseKeyConfig(input);
	}
	else if (input.IsTrigger("up"))
	{
		currentSelectorIndex_ = (currentSelectorIndex_ + itemCount - 1) % itemCount;
	}
	else if (input.IsTrigger("down"))
	{
		currentSelectorIndex_ = (currentSelectorIndex_ + 1) % itemCount;
	}
	else if (input.IsTrigger("ok"))
	{
		// キー婚の要素をクリックしたら
		if (currentSelectorIndex_ < input.orderForDisplay.size())
		{
			// それを編集
			update_ = &KeyConfigScene::EdittintUpdate;
		}
		else
		{
			// キー以外の(確定、戻るなど)
			auto menuIndex = currentSelectorIndex_ - input.orderForDisplay.size();
			auto menuStr = menuString_[menuIndex];
			(this->*menuFuncTable_[menuStr])(input);
		}
	}
}

void KeyConfigScene::EdittintUpdate(Input& input)
{
	if (input.IsTrigger("ok"))
	{
		// 編集を確定して戻る
		update_ = &KeyConfigScene::NomalUpdate;
	}
	else
	{
		// 現在編集中のボタンを取得
		std::string edittingEventName = input.orderForDisplay[currentSelectorIndex_];
		for (auto& row : input.tempInputTable_[edittingEventName])
		{
			if (row.type == Input::PeripheralType::keybd)
			{
				int keystate = input.GetLastKeyboadState();
				if (keystate != -1)
				{
					row.id = keystate;
				}
			}
			else if (row.type == Input::PeripheralType::pad1)
			{
				int padState = input.GetLastPadState();
				if (padState != -1)
				{
					row.id = padState;
				}
			}
		}
	}
}

void KeyConfigScene::DisappearUpdate(Input& input)
{
	--frame_;
	if (frame_ <= 0)
	{
		controller_.PopScene();
		return;
	}
}

void KeyConfigScene::NomalDraw()
{
	const auto& wsize = Application::GetInstance().GetWindowSize();
	// ポーズ画面枠
	DrawBoxAA(static_cast<float>(frame_margin), static_cast<float>(frame_margin),// 左上
		static_cast<float>(wsize.w - frame_margin), static_cast<float>(wsize.h - frame_margin), // 右下
		0xffffff, // 色
		false, // 塗りつぶさない
		3.0f); // 線太い
	// 透過よ
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, bg_alpha);
	DrawBox(frame_margin, frame_margin,// 左上
		wsize.w - frame_margin, wsize.h - frame_margin, // 右下
		base_color, // 色
		true); // 塗りつぶす
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawFormatString(30, 30, 0xffffff, "KeyConfigScene");
	DrawInputInfo();
}

void KeyConfigScene::ShiftingDraw()
{
	const auto& wsize = Application::GetInstance().GetWindowSize();
	// ウィジェットの高さを計算する(上下の幅分小さく)
	const int frameHeight = wsize.h - frame_margin - frame_margin;
	// 上下に広がる感じか
	const int middleY = (frame_margin + wsize.h - frame_margin) / 2; // 真ん中のY座標
	// 0~1
	float rate = static_cast<float>(frame_) / static_cast<float>(appear_interval);
	// frameが進むごとにここは0～frameHeightの半分まで大きくなる
	int halfHeight = static_cast<int>(frameHeight * rate / 2);
	// ここから、topとbottomを計算。
	int top = middleY - halfHeight;
	int bottom = middleY + halfHeight;
	// ポーズ画面枠
	DrawBoxAA(static_cast<float>(frame_margin), static_cast<float>(top),// 左上
		static_cast<float>(wsize.w - frame_margin), static_cast<float>(bottom), // 右下
		base_color, // 色
		false, // 塗りつぶさない
		3.0f); // 線太い
	// 透過よ
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, bg_alpha);
	DrawBox(frame_margin, top,// 左上
		wsize.w - frame_margin, bottom, // 右下
		base_color, // 色
		true); // 塗りつぶす
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	// 出現演出が終了したら
	if (frame_ > appear_interval)
	{
		// 状態遷移
		update_ = &KeyConfigScene::NomalUpdate;
		draw_ = &KeyConfigScene::NomalDraw;
		return;
	}
}

void KeyConfigScene::DrawInputInfo()
{
	int y = frame_margin + config_text_start_y;
	int x = frame_margin + config_text_left;

	// イベントからどれぐらい横にずらして入力コードを出すか
	constexpr int actual_id_margin = 80;
	// 幅
	constexpr int actual_id_width = 150;

	// マジでアクセスできるじゃん
	for (int index = 0; const auto& inputRow : input_.orderForDisplay)
	{
		x = frame_margin + config_text_left; // Xをリセット
		int selectOffset = 0;
		// セレクターを表示など
		if (index == currentSelectorIndex_)
		{
			DrawStringWithShadow(x - config_selector_left, y, "⇒", 0xff0000);
			selectOffset = 2;
		}
		const auto& text = inputRow;
		unsigned int textColor = 0x0000ff;
		if (update_ == &KeyConfigScene::EdittintUpdate)
		{
			if (currentSelectorIndex_ == index)
			{
				textColor = 0xff0000;
				selectOffset = 10;
			}
		}
		// イベント名を表示
		DrawFormatString(x + 1 + selectOffset, y + 1, 0x000000, "%s", text.c_str());
		DrawFormatString(x + selectOffset, y, textColor, "%s", text.c_str());
		// 入力信号を表示
		// inputTable内の特定のイベントにおける入力ID配列を回す
		for (const auto& keyValue : input_.tempInputTable_[inputRow])
		{
			std::string periTypeString = "";
			std::string inputStr = "";
			if (keyValue.type == Input::PeripheralType::keybd)
			{
				periTypeString = "keybd";
				inputStr = keyNameTable_[keyValue.id];
			}
			else if (keyValue.type == Input::PeripheralType::pad1)
			{
				periTypeString = "pad1";
				inputStr = padNameTable_[keyValue.id];
			}
			DrawFormatString(x + 1 + actual_id_margin + selectOffset, y + 1, 0x000000, "%s=%s", periTypeString.c_str(), inputStr.c_str());
			DrawFormatString(x + actual_id_margin + selectOffset, y, textColor, "%s=%s", periTypeString.c_str(), inputStr.c_str());
			// 横にずらす
			x += actual_id_width;
		}
		++index;
		y += config_row_height;
	}
	const auto& wsize = Application::GetInstance().GetWindowSize();
	x = wsize.w / 2; // 真ん中？
	y += config_row_height;
	y += config_row_height;

	const int eventSize = static_cast<int>(input_.orderForDisplay.size());
	int menuIndex = 0;
	for (auto& str : menuString_)
	{
		int selectOffset = 0;
		// キー以外のメニュー文字列を回す
		if (currentSelectorIndex_ == eventSize + menuIndex)
		{
			DrawStringWithShadow(x - arrow_offset, y, "⇒", 0xff0000);
			selectOffset = 5;
		}
		int width = GetDrawStringWidth(str.c_str(), static_cast<int>(str.length()));
		DrawStringWithShadow(x - static_cast<int>(width * 0.5f) + selectOffset, y, str.c_str(), 0x555555);
		y += config_row_height;
		++menuIndex;
	}
}

void KeyConfigScene::DrawStringWithShadow(int x, int y, const char* str, uint32_t color)
{
	DrawString(x + 1, y + 1, str, 0x000000);
	DrawString(x, y, str, color);
}

void KeyConfigScene::Close()
{
	update_ = &KeyConfigScene::DisappearUpdate;
	draw_   = &KeyConfigScene::ShiftingDraw;
	frame_  = appear_interval;
}

void KeyConfigScene::CloseKeyConfig(Input& input)
{
	input_.RollbackEdittedInputTable();
	Close();
}

void KeyConfigScene::CommitAndClose(Input& input)
{
	input_.CommitEdittedInputTable();
	input_.SaveInputTable();
	Close();
}

void KeyConfigScene::CancelEdit(Input& input)
{
	input_.RollbackEdittedInputTable();
}

void KeyConfigScene::SetDefault(Input& input)
{
	input_.SetTempDefault();
	//Close();
}

KeyConfigScene::KeyConfigScene(SceneController& cont, Input& input) :
	input_(input),
	Scene(cont),
	frame_(0),
	update_(&KeyConfigScene::AppearUpdate),
	draw_(&KeyConfigScene::ShiftingDraw)
{
	keyNameTable_ =
	{
		{KEY_INPUT_A, "Ａキー"},
		{KEY_INPUT_B, "Ｂキー"},
		{KEY_INPUT_C, "Ｃキー"},
		{KEY_INPUT_D, "Ｄキー"},
		{KEY_INPUT_E, "Ｅキー"},
		{KEY_INPUT_F, "Ｆキー"},
		{KEY_INPUT_G, "Ｇキー"},
		{KEY_INPUT_H, "Ｈキー"},
		{KEY_INPUT_I, "Ｉキー"},
		{KEY_INPUT_J, "Ｊキー"},
		{KEY_INPUT_K, "Ｋキー"},
		{KEY_INPUT_L, "Ｌキー"},
		{KEY_INPUT_M, "Ｍキー"},
		{KEY_INPUT_N, "Ｎキー"},
		{KEY_INPUT_O, "Ｏキー"},
		{KEY_INPUT_P, "Ｐキー"},
		{KEY_INPUT_Q, "Ｑキー"},
		{KEY_INPUT_R, "Ｒキー"},
		{KEY_INPUT_S, "Ｓキー"},
		{KEY_INPUT_T, "Ｔキー"},
		{KEY_INPUT_U, "Ｕキー"},
		{KEY_INPUT_V, "Ｖキー"},
		{KEY_INPUT_W, "Ｗキー"},
		{KEY_INPUT_X, "Ｘキー"},
		{KEY_INPUT_Y, "Ｙキー"},
		{KEY_INPUT_Z, "Ｚキー"},

		{KEY_INPUT_0 , "０キー"},
		{KEY_INPUT_1, "１キー"},
		{KEY_INPUT_2, "２キー"},
		{KEY_INPUT_3, "３キー"},
		{KEY_INPUT_4, "４キー"},
		{KEY_INPUT_5, "５キー"},
		{KEY_INPUT_6, "６キー"},
		{KEY_INPUT_7, "７キー"},
		{KEY_INPUT_8, "８キー"},
		{KEY_INPUT_9, "９キー"},

		{ KEY_INPUT_BACK,"BackSpaceキー"},
		{ KEY_INPUT_TAB,"Tabキー"},
		{ KEY_INPUT_RETURN,"Enterキー"},
		{ KEY_INPUT_LSHIFT,"左Shiftキー"},
		{ KEY_INPUT_RSHIFT,"右Shiftキー"},
		{ KEY_INPUT_LCONTROL,"左Ctrlキー"},
		{ KEY_INPUT_RCONTROL,"右Ctrlキー"},
		{ KEY_INPUT_ESCAPE,"Escキー"},
		{ KEY_INPUT_SPACE,"スペースキー"},
		{ KEY_INPUT_PGUP,"PageUpキー"},
		{ KEY_INPUT_PGDN,"PageDownキー"},
		{ KEY_INPUT_END,"Endキー"},
		{ KEY_INPUT_HOME,"Homeキー"},
		{ KEY_INPUT_LEFT,"左キー"},
		{ KEY_INPUT_UP,"上キー"},
		{ KEY_INPUT_RIGHT,"右キー"},
		{ KEY_INPUT_DOWN,"下キー"},
		{ KEY_INPUT_INSERT,"Insertキー"},
		{ KEY_INPUT_DELETE,"Deleteキー"},
		{ KEY_INPUT_MINUS,"－キー"},
		{ KEY_INPUT_YEN,"￥キー"},
		{ KEY_INPUT_PREVTRACK,"＾キー"},
		{ KEY_INPUT_PERIOD,"．キー"},
		{ KEY_INPUT_SLASH,"／キー"},
		{ KEY_INPUT_LALT,"左Altキー"},
		{ KEY_INPUT_RALT,"右Altキー"},
		{ KEY_INPUT_SCROLL,"ScrollLockキー"},
		{ KEY_INPUT_SEMICOLON,"；キー"},
		{ KEY_INPUT_COLON,"：キー"},
		{ KEY_INPUT_LBRACKET,"［キー"},
		{ KEY_INPUT_RBRACKET,"］キー"},
		{ KEY_INPUT_AT,"＠キー"},
		{ KEY_INPUT_BACKSLASH,"＼キー"},
		{ KEY_INPUT_COMMA,"，キー"},
		{ KEY_INPUT_KANJI,"漢字キー"},
		{ KEY_INPUT_CONVERT,"変換キー"},
		{ KEY_INPUT_NOCONVERT,"無変換キー"},
		{ KEY_INPUT_KANA,"カナキー"},
		{ KEY_INPUT_APPS,"アプリケーションメニューキー"},
		{ KEY_INPUT_CAPSLOCK,"CaspLockキー"},
		{ KEY_INPUT_SYSRQ,"PrintScreenキー"},
		{ KEY_INPUT_PAUSE,"PauseBreakキー"},
		{ KEY_INPUT_LWIN,"左Winキー"},
		{ KEY_INPUT_RWIN,"右Winキー"},
		{ KEY_INPUT_NUMLOCK,"テンキーNumLockキー"},
		{ KEY_INPUT_NUMPAD0,"テンキー０"},
		{ KEY_INPUT_NUMPAD1,"テンキー１"},
		{ KEY_INPUT_NUMPAD2,"テンキー２"},
		{ KEY_INPUT_NUMPAD3,"テンキー３"},
		{ KEY_INPUT_NUMPAD4,"テンキー４"},
		{ KEY_INPUT_NUMPAD5,"テンキー５"},
		{ KEY_INPUT_NUMPAD6,"テンキー６"},
		{ KEY_INPUT_NUMPAD7,"テンキー７"},
		{ KEY_INPUT_NUMPAD8,"テンキー８"},
		{ KEY_INPUT_NUMPAD9,"テンキー９"},
		{ KEY_INPUT_MULTIPLY,"テンキー＊キー"},
		{ KEY_INPUT_ADD,"テンキー＋キー"},
		{ KEY_INPUT_SUBTRACT,"テンキー－キー"},
		{ KEY_INPUT_DECIMAL,"テンキー．キー"},
		{ KEY_INPUT_DIVIDE,"テンキー／キー"},
		{ KEY_INPUT_NUMPADENTER,"テンキーのエンターキー"},
		{ KEY_INPUT_F1,"Ｆ１キー"},
		{ KEY_INPUT_F2,"Ｆ２キー"},
		{ KEY_INPUT_F3,"Ｆ３キー"},
		{ KEY_INPUT_F4,"Ｆ４キー"},
		{ KEY_INPUT_F5,"Ｆ５キー"},
		{ KEY_INPUT_F6,"Ｆ６キー"},
		{ KEY_INPUT_F7,"Ｆ７キー"},
		{ KEY_INPUT_F8,"Ｆ８キー"},
		{ KEY_INPUT_F9,"Ｆ９キー"},
		{ KEY_INPUT_F10,"Ｆ１０キー"},
		{ KEY_INPUT_F11,"Ｆ１１キー"},
		{ KEY_INPUT_F12,"Ｆ１２キー"},

	}; 

	padNameTable_[PAD_INPUT_A] = " Ａボタン";
	padNameTable_[PAD_INPUT_B] = " Ｂボタン";
	padNameTable_[PAD_INPUT_C] = " Ｘボタン";
	padNameTable_[PAD_INPUT_X] = " Ｙボタン";
	padNameTable_[PAD_INPUT_Y] = " Ｌ１ボタン";
	padNameTable_[PAD_INPUT_Z] = " Ｒ１ボタン";
	padNameTable_[PAD_INPUT_L] = " ＳＥＬＥＣＴボタン";
	padNameTable_[PAD_INPUT_R] = " ＳＴＡＲＴボタン";
	padNameTable_[PAD_INPUT_START] = " Ｌ３ボタン";
	padNameTable_[PAD_INPUT_M] = " Ｒ３ボタン";

	menuString_ =
	{
		"戻る",
		"確定",
		"キャンセル",
		"デフォルトに戻す",
	};

	menuFuncTable_ =
	{
		{"戻る",        &KeyConfigScene::CloseKeyConfig},
		{"確定",        &KeyConfigScene::CommitAndClose},
		{"キャンセル",      &KeyConfigScene::CancelEdit},
		{"デフォルトに戻す", &KeyConfigScene::SetDefault},
	};
}

void KeyConfigScene::Update(Input& input)
{
	(this->*update_)(input);
}

void KeyConfigScene::Draw()
{
	(this->*draw_)();
}
