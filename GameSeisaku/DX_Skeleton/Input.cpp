#include "Input.h"
#include <cassert>
#include <DxLib.h>

namespace 
{
	const char* key_config_signature = "kcfg";
	const char* key_config_filemane = "keyconfig.dat";
}

void Input::SetDefault()
{
	inputTable_["next"] =
	{
		{PeripheralType::keybd, KEY_INPUT_RETURN},
		{PeripheralType::pad1, PAD_INPUT_1} // A
	}; 
	inputTable_["pause"] = 
	{
		{PeripheralType::keybd, KEY_INPUT_P},
		{PeripheralType::pad1, PAD_INPUT_8} // START
	}; 
	inputTable_["up"] = 
	{
		{PeripheralType::keybd, KEY_INPUT_UP},
		{PeripheralType::pad1, PAD_INPUT_UP}
	};
	inputTable_["down"] = 
	{
		{PeripheralType::keybd, KEY_INPUT_DOWN},
		{PeripheralType::pad1, PAD_INPUT_DOWN}
	};
	inputTable_["left"] = 
	{
		{PeripheralType::keybd, KEY_INPUT_LEFT},
		{PeripheralType::pad1, PAD_INPUT_LEFT}
	};
	inputTable_["right"] = 
	{
		{PeripheralType::keybd, KEY_INPUT_RIGHT},
		{PeripheralType::pad1, PAD_INPUT_RIGHT}
	};
	// �Q�[�����̃{�^���e�[�u��
	inputTable_["action"] =
	{
		{PeripheralType::keybd, KEY_INPUT_Z},
		{PeripheralType::pad1, PAD_INPUT_3}
	};
	inputTable_["ok"] =
	{	// next�Ɠ���
		{PeripheralType::keybd, KEY_INPUT_RETURN},
		{PeripheralType::pad1, PAD_INPUT_1}
	};
	inputTable_["jump"] =
	{
		{PeripheralType::keybd, KEY_INPUT_X},
		{PeripheralType::pad1, PAD_INPUT_3}
	};
}

void Input::SetTempDefault()
{
	tempInputTable_["next"] =
	{
		{PeripheralType::keybd, KEY_INPUT_RETURN},
		{PeripheralType::pad1, PAD_INPUT_1} // A
	};
	tempInputTable_["pause"] =
	{
		{PeripheralType::keybd, KEY_INPUT_P},
		{PeripheralType::pad1, PAD_INPUT_8} // START
	};
	tempInputTable_["up"] =
	{
		{PeripheralType::keybd, KEY_INPUT_UP},
		{PeripheralType::pad1, PAD_INPUT_UP}
	};
	tempInputTable_["down"] =
	{
		{PeripheralType::keybd, KEY_INPUT_DOWN},
		{PeripheralType::pad1, PAD_INPUT_DOWN}
	};
	tempInputTable_["left"] =
	{
		{PeripheralType::keybd, KEY_INPUT_LEFT},
		{PeripheralType::pad1, PAD_INPUT_LEFT}
	};
	tempInputTable_["right"] =
	{
		{PeripheralType::keybd, KEY_INPUT_RIGHT},
		{PeripheralType::pad1, PAD_INPUT_RIGHT}
	};
	// �Q�[�����̃{�^���e�[�u��
	tempInputTable_["action"] =
	{
		{PeripheralType::keybd, KEY_INPUT_Z},
		{PeripheralType::pad1, PAD_INPUT_3}
	};
	tempInputTable_["ok"] =
	{	// next�Ɠ���
		{PeripheralType::keybd, KEY_INPUT_RETURN},
		{PeripheralType::pad1, PAD_INPUT_1}
	};
	tempInputTable_["jump"] =
	{
		{PeripheralType::keybd, KEY_INPUT_X},
		{PeripheralType::pad1, PAD_INPUT_3}
	};
}

void Input::CommitEdittedInputTable()
{
	inputTable_ = tempInputTable_;
}

void Input::RollbackEdittedInputTable()
{
	tempInputTable_ = inputTable_;
}

int Input::GetLastKeyboadState()
{
	for (int i = 0; i < _countof(currentRawKeybdState_); ++i)
	{
		if (currentRawKeybdState_[i] && !lastRawKeybdState_[i])
		{
			return i;
		}
	}
	return -1;
}

int Input::GetLastPadState()
{
	uint32_t bit = 1;
	for (int i = 0; i < 32; ++i)
	{
		int inputId = bit << i;
		if ((inputId & currentRawPadState_) && !(inputId & lastRawPadState_))
		{
			return inputId;
		}
	}

	return -1;
}

void Input::SaveInputTable()
{
	FILE* fp = nullptr;
	fopen_s(&fp, key_config_filemane, "wb"); // �o�C�i���ŏ������ݗp�ɊJ��
	// �V�O�l�`��
	std::string signature = key_config_signature;
	fwrite(signature.data(), signature.size(), 1, fp);
	// �o�[�W����
	float version = 1.0f;
	fwrite(&version, sizeof(version), 1, fp);
	// �f�[�^�T�C�Y
	size_t size = inputTable_.size();
	fwrite(&size, sizeof(size), 1, fp);
	// �f�[�^
	for (const auto& record : inputTable_)
	{
		// �L�[�̏�������
		byte nameSize = static_cast<byte>(record.first.length());
		fwrite(&nameSize, sizeof(nameSize), 1, fp);
		fwrite(record.first.data(), record.first.size(), 1, fp);
		// �l(InputState)�̏�������
		// �܂��v�f���̋L�^
		byte inputDataSize = static_cast<byte>(record.second.size());
		fwrite(&inputDataSize, sizeof(inputDataSize), 1, fp);
		// InputState�̃T�C�Y��8�o�C�g�Ȃ̂ŁA8*�v�f���������߂΂���
		fwrite(record.second.data(), // �������ގ��f�[�^�̐擪�A�h���X
			sizeof(record.second[0]), // �������ރf�[�^�̃T�C�Y
			record.second.size(), // �������ރf�[�^��
			fp);
	}

	fclose(fp);
}

void Input::LoadInputTable()
{
	std::string filename = key_config_filemane;

	int handle = FileRead_open(filename.c_str());
	assert(handle && "�L�[�ݒ�̓ǂݍ��݂Ɏ��s���܂���");

	struct Header
	{
		char signature[4]; // �V�O�l�`��
		float varsion; // �o�[�W����
		size_t dataNum; // �f�[�^��
	};
	Header header = {}; // �w�b�_�[�̓ǂݍ���
	FileRead_read(&header, sizeof(header), handle);

	// �f�[�^�̐������ǂ�ł���
	for (int i = 0; i < header.dataNum; ++i)
	{
		// �f�[�^�͂܂��A�C�x���g����ǂݍ���
		byte nameSize = 0;
		FileRead_read(&nameSize, sizeof(nameSize), handle);
		// �L�[�����擾
		std::string strEventName;
		strEventName.resize(nameSize);
		FileRead_read(strEventName.data(), nameSize * sizeof(char), handle);
		// ���f�[�^
		byte inputDataNum = 0;
		FileRead_read(&inputDataNum, sizeof(inputDataNum), handle);
		std::vector<InputState> inputStates;
		inputStates.resize(inputDataNum);
		// ����List����ł��Ȃ��񂾂낤��
		FileRead_read(inputStates.data(), sizeof(inputStates[0])* inputDataNum, handle);
		inputTable_[strEventName] = inputStates;
	}

	// temp�ɂ����f
	tempInputTable_ = inputTable_;

	FileRead_close(handle);
}

// �J�b�R�ɉ��������ĂȂ��Ƃ���0�ŏ���������Ă�
Input::Input()
{
	// ���͂Ɩ��O�̑Ή��\�����
	SetDefault();

	LoadInputTable();

	// �L�[�R���t�B�O�ɏo�Ă��鏇�Ԃ�����
	// �L�[�R������Ă������������
	orderForDisplay =
	{
		"ok",
		"next",
		"action",
		"jump",
	};
}

void Input::Update()
{
	// �O��̃t���[���̓��͂�����Ă���
	last_ = current_;

	std::copy(std::begin(currentRawKeybdState_), std::end(currentRawKeybdState_), std::begin(lastRawKeybdState_));
	currentRawPadState_ = GetJoypadInputState(DX_INPUT_PAD1);
	// ���͂��Ƃ�
	GetHitKeyStateAll(currentRawKeybdState_);
	// �e�[�u���ɋL�����ꂽ���ׂĂ̓��͂��`�F�b�N����
	for (const auto& keyValue : inputTable_)
	{
		// �o�Ă����L�[�C�x���g�ɑ΂��A
		const auto& key = keyValue.first;
		current_[key] = false;
		// ���ꂼ��̓��͌`���Ń`�F�b�N����
		for (const auto& input : keyValue.second)
		{
			switch (input.type)
			{
			case PeripheralType::keybd:
				current_[keyValue.first] = current_[key] || currentRawKeybdState_[input.id];
				break;
			case PeripheralType::pad1:
				current_[keyValue.first] = current_[key] || (input.id & currentRawPadState_);
				break;
			default:
				break;
			}
		}
	}
}

bool Input::IsTrigger(std::string key) const
{
	// id���O�񉟂���Ă��Ȃ��āA���݉�����Ă��鎞��true��Ԃ�
	// []���Z�q�ł͂Ȃ��Aat(key)���g�����ƁI�I�I�I�I
	return (current_.at(key) && !last_.at(key));
}

bool Input::IsPressed(const char* key) const
{
	// ���񉟂��ꂽ���͂������Ȃ�
	return current_.at(key);
}
