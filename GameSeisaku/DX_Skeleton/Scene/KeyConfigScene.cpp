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
	constexpr int frame_margin = 10; // �Q�[����ʂ���|�[�Y��ʂ܂ł̕�
	constexpr int config_text_start_y = 50; // �L�[�R���t�B�O��ʂ̃e�L�X�g���\������鏉��y���W
	constexpr int config_text_left = 150; // �L�[�R���t�B�O��X���W�̃I�t�Z�b�g
	constexpr int config_row_height = 30; // �L�[�R���t�B�O�ꍀ�ړ�����̍���
	constexpr int arrow_offset = 100; // �L�[�ȊO
	constexpr int config_selector_left = 20;
	constexpr unsigned int base_color = 0xaaffaa; // ���邢�� �L�[�R���t�B�O�̃J���[
	constexpr unsigned int bg_alpha = 220; // �قڕs����
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
	// ���Ƃ̃L�[�̐�+�߂�A�m���p��
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
		// �L�[���̗v�f���N���b�N������
		if (currentSelectorIndex_ < input.orderForDisplay.size())
		{
			// �����ҏW
			update_ = &KeyConfigScene::EdittintUpdate;
		}
		else
		{
			// �L�[�ȊO��(�m��A�߂�Ȃ�)
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
		// �ҏW���m�肵�Ė߂�
		update_ = &KeyConfigScene::NomalUpdate;
	}
	else
	{
		// ���ݕҏW���̃{�^�����擾
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
	// �|�[�Y��ʘg
	DrawBoxAA(static_cast<float>(frame_margin), static_cast<float>(frame_margin),// ����
		static_cast<float>(wsize.w - frame_margin), static_cast<float>(wsize.h - frame_margin), // �E��
		0xffffff, // �F
		false, // �h��Ԃ��Ȃ�
		3.0f); // ������
	// ���߂�
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, bg_alpha);
	DrawBox(frame_margin, frame_margin,// ����
		wsize.w - frame_margin, wsize.h - frame_margin, // �E��
		base_color, // �F
		true); // �h��Ԃ�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawFormatString(30, 30, 0xffffff, "KeyConfigScene");
	DrawInputInfo();
}

void KeyConfigScene::ShiftingDraw()
{
	const auto& wsize = Application::GetInstance().GetWindowSize();
	// �E�B�W�F�b�g�̍������v�Z����(�㉺�̕���������)
	const int frameHeight = wsize.h - frame_margin - frame_margin;
	// �㉺�ɍL���銴����
	const int middleY = (frame_margin + wsize.h - frame_margin) / 2; // �^�񒆂�Y���W
	// 0~1
	float rate = static_cast<float>(frame_) / static_cast<float>(appear_interval);
	// frame���i�ނ��Ƃɂ�����0�`frameHeight�̔����܂ő傫���Ȃ�
	int halfHeight = static_cast<int>(frameHeight * rate / 2);
	// ��������Atop��bottom���v�Z�B
	int top = middleY - halfHeight;
	int bottom = middleY + halfHeight;
	// �|�[�Y��ʘg
	DrawBoxAA(static_cast<float>(frame_margin), static_cast<float>(top),// ����
		static_cast<float>(wsize.w - frame_margin), static_cast<float>(bottom), // �E��
		base_color, // �F
		false, // �h��Ԃ��Ȃ�
		3.0f); // ������
	// ���߂�
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, bg_alpha);
	DrawBox(frame_margin, top,// ����
		wsize.w - frame_margin, bottom, // �E��
		base_color, // �F
		true); // �h��Ԃ�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	// �o�����o���I��������
	if (frame_ > appear_interval)
	{
		// ��ԑJ��
		update_ = &KeyConfigScene::NomalUpdate;
		draw_ = &KeyConfigScene::NomalDraw;
		return;
	}
}

void KeyConfigScene::DrawInputInfo()
{
	int y = frame_margin + config_text_start_y;
	int x = frame_margin + config_text_left;

	// �C�x���g����ǂꂮ�炢���ɂ��炵�ē��̓R�[�h���o����
	constexpr int actual_id_margin = 80;
	// ��
	constexpr int actual_id_width = 150;

	// �}�W�ŃA�N�Z�X�ł��邶���
	for (int index = 0; const auto& inputRow : input_.orderForDisplay)
	{
		x = frame_margin + config_text_left; // X�����Z�b�g
		int selectOffset = 0;
		// �Z���N�^�[��\���Ȃ�
		if (index == currentSelectorIndex_)
		{
			DrawStringWithShadow(x - config_selector_left, y, "��", 0xff0000);
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
		// �C�x���g����\��
		DrawFormatString(x + 1 + selectOffset, y + 1, 0x000000, "%s", text.c_str());
		DrawFormatString(x + selectOffset, y, textColor, "%s", text.c_str());
		// ���͐M����\��
		// inputTable���̓���̃C�x���g�ɂ��������ID�z�����
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
			// ���ɂ��炷
			x += actual_id_width;
		}
		++index;
		y += config_row_height;
	}
	const auto& wsize = Application::GetInstance().GetWindowSize();
	x = wsize.w / 2; // �^�񒆁H
	y += config_row_height;
	y += config_row_height;

	const int eventSize = static_cast<int>(input_.orderForDisplay.size());
	int menuIndex = 0;
	for (auto& str : menuString_)
	{
		int selectOffset = 0;
		// �L�[�ȊO�̃��j���[���������
		if (currentSelectorIndex_ == eventSize + menuIndex)
		{
			DrawStringWithShadow(x - arrow_offset, y, "��", 0xff0000);
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
		{KEY_INPUT_A, "�`�L�["},
		{KEY_INPUT_B, "�a�L�["},
		{KEY_INPUT_C, "�b�L�["},
		{KEY_INPUT_D, "�c�L�["},
		{KEY_INPUT_E, "�d�L�["},
		{KEY_INPUT_F, "�e�L�["},
		{KEY_INPUT_G, "�f�L�["},
		{KEY_INPUT_H, "�g�L�["},
		{KEY_INPUT_I, "�h�L�["},
		{KEY_INPUT_J, "�i�L�["},
		{KEY_INPUT_K, "�j�L�["},
		{KEY_INPUT_L, "�k�L�["},
		{KEY_INPUT_M, "�l�L�["},
		{KEY_INPUT_N, "�m�L�["},
		{KEY_INPUT_O, "�n�L�["},
		{KEY_INPUT_P, "�o�L�["},
		{KEY_INPUT_Q, "�p�L�["},
		{KEY_INPUT_R, "�q�L�["},
		{KEY_INPUT_S, "�r�L�["},
		{KEY_INPUT_T, "�s�L�["},
		{KEY_INPUT_U, "�t�L�["},
		{KEY_INPUT_V, "�u�L�["},
		{KEY_INPUT_W, "�v�L�["},
		{KEY_INPUT_X, "�w�L�["},
		{KEY_INPUT_Y, "�x�L�["},
		{KEY_INPUT_Z, "�y�L�["},

		{KEY_INPUT_0 , "�O�L�["},
		{KEY_INPUT_1, "�P�L�["},
		{KEY_INPUT_2, "�Q�L�["},
		{KEY_INPUT_3, "�R�L�["},
		{KEY_INPUT_4, "�S�L�["},
		{KEY_INPUT_5, "�T�L�["},
		{KEY_INPUT_6, "�U�L�["},
		{KEY_INPUT_7, "�V�L�["},
		{KEY_INPUT_8, "�W�L�["},
		{KEY_INPUT_9, "�X�L�["},

		{ KEY_INPUT_BACK,"BackSpace�L�["},
		{ KEY_INPUT_TAB,"Tab�L�["},
		{ KEY_INPUT_RETURN,"Enter�L�["},
		{ KEY_INPUT_LSHIFT,"��Shift�L�["},
		{ KEY_INPUT_RSHIFT,"�EShift�L�["},
		{ KEY_INPUT_LCONTROL,"��Ctrl�L�["},
		{ KEY_INPUT_RCONTROL,"�ECtrl�L�["},
		{ KEY_INPUT_ESCAPE,"Esc�L�["},
		{ KEY_INPUT_SPACE,"�X�y�[�X�L�["},
		{ KEY_INPUT_PGUP,"PageUp�L�["},
		{ KEY_INPUT_PGDN,"PageDown�L�["},
		{ KEY_INPUT_END,"End�L�["},
		{ KEY_INPUT_HOME,"Home�L�["},
		{ KEY_INPUT_LEFT,"���L�["},
		{ KEY_INPUT_UP,"��L�["},
		{ KEY_INPUT_RIGHT,"�E�L�["},
		{ KEY_INPUT_DOWN,"���L�["},
		{ KEY_INPUT_INSERT,"Insert�L�["},
		{ KEY_INPUT_DELETE,"Delete�L�["},
		{ KEY_INPUT_MINUS,"�|�L�["},
		{ KEY_INPUT_YEN,"���L�["},
		{ KEY_INPUT_PREVTRACK,"�O�L�["},
		{ KEY_INPUT_PERIOD,"�D�L�["},
		{ KEY_INPUT_SLASH,"�^�L�["},
		{ KEY_INPUT_LALT,"��Alt�L�["},
		{ KEY_INPUT_RALT,"�EAlt�L�["},
		{ KEY_INPUT_SCROLL,"ScrollLock�L�["},
		{ KEY_INPUT_SEMICOLON,"�G�L�["},
		{ KEY_INPUT_COLON,"�F�L�["},
		{ KEY_INPUT_LBRACKET,"�m�L�["},
		{ KEY_INPUT_RBRACKET,"�n�L�["},
		{ KEY_INPUT_AT,"���L�["},
		{ KEY_INPUT_BACKSLASH,"�_�L�["},
		{ KEY_INPUT_COMMA,"�C�L�["},
		{ KEY_INPUT_KANJI,"�����L�["},
		{ KEY_INPUT_CONVERT,"�ϊ��L�["},
		{ KEY_INPUT_NOCONVERT,"���ϊ��L�["},
		{ KEY_INPUT_KANA,"�J�i�L�["},
		{ KEY_INPUT_APPS,"�A�v���P�[�V�������j���[�L�["},
		{ KEY_INPUT_CAPSLOCK,"CaspLock�L�["},
		{ KEY_INPUT_SYSRQ,"PrintScreen�L�["},
		{ KEY_INPUT_PAUSE,"PauseBreak�L�["},
		{ KEY_INPUT_LWIN,"��Win�L�["},
		{ KEY_INPUT_RWIN,"�EWin�L�["},
		{ KEY_INPUT_NUMLOCK,"�e���L�[NumLock�L�["},
		{ KEY_INPUT_NUMPAD0,"�e���L�[�O"},
		{ KEY_INPUT_NUMPAD1,"�e���L�[�P"},
		{ KEY_INPUT_NUMPAD2,"�e���L�[�Q"},
		{ KEY_INPUT_NUMPAD3,"�e���L�[�R"},
		{ KEY_INPUT_NUMPAD4,"�e���L�[�S"},
		{ KEY_INPUT_NUMPAD5,"�e���L�[�T"},
		{ KEY_INPUT_NUMPAD6,"�e���L�[�U"},
		{ KEY_INPUT_NUMPAD7,"�e���L�[�V"},
		{ KEY_INPUT_NUMPAD8,"�e���L�[�W"},
		{ KEY_INPUT_NUMPAD9,"�e���L�[�X"},
		{ KEY_INPUT_MULTIPLY,"�e���L�[���L�["},
		{ KEY_INPUT_ADD,"�e���L�[�{�L�["},
		{ KEY_INPUT_SUBTRACT,"�e���L�[�|�L�["},
		{ KEY_INPUT_DECIMAL,"�e���L�[�D�L�["},
		{ KEY_INPUT_DIVIDE,"�e���L�[�^�L�["},
		{ KEY_INPUT_NUMPADENTER,"�e���L�[�̃G���^�[�L�["},
		{ KEY_INPUT_F1,"�e�P�L�["},
		{ KEY_INPUT_F2,"�e�Q�L�["},
		{ KEY_INPUT_F3,"�e�R�L�["},
		{ KEY_INPUT_F4,"�e�S�L�["},
		{ KEY_INPUT_F5,"�e�T�L�["},
		{ KEY_INPUT_F6,"�e�U�L�["},
		{ KEY_INPUT_F7,"�e�V�L�["},
		{ KEY_INPUT_F8,"�e�W�L�["},
		{ KEY_INPUT_F9,"�e�X�L�["},
		{ KEY_INPUT_F10,"�e�P�O�L�["},
		{ KEY_INPUT_F11,"�e�P�P�L�["},
		{ KEY_INPUT_F12,"�e�P�Q�L�["},

	}; 

	padNameTable_[PAD_INPUT_A] = " �`�{�^��";
	padNameTable_[PAD_INPUT_B] = " �a�{�^��";
	padNameTable_[PAD_INPUT_C] = " �w�{�^��";
	padNameTable_[PAD_INPUT_X] = " �x�{�^��";
	padNameTable_[PAD_INPUT_Y] = " �k�P�{�^��";
	padNameTable_[PAD_INPUT_Z] = " �q�P�{�^��";
	padNameTable_[PAD_INPUT_L] = " �r�d�k�d�b�s�{�^��";
	padNameTable_[PAD_INPUT_R] = " �r�s�`�q�s�{�^��";
	padNameTable_[PAD_INPUT_START] = " �k�R�{�^��";
	padNameTable_[PAD_INPUT_M] = " �q�R�{�^��";

	menuString_ =
	{
		"�߂�",
		"�m��",
		"�L�����Z��",
		"�f�t�H���g�ɖ߂�",
	};

	menuFuncTable_ =
	{
		{"�߂�",        &KeyConfigScene::CloseKeyConfig},
		{"�m��",        &KeyConfigScene::CommitAndClose},
		{"�L�����Z��",      &KeyConfigScene::CancelEdit},
		{"�f�t�H���g�ɖ߂�", &KeyConfigScene::SetDefault},
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
