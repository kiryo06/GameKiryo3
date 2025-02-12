#pragma once
#include <map>
#include <string>
#include <vector>

class KeyConfigScene;

/// <summary>
/// ���͌n�������ǂ�N���X
/// </summary>
class Input
{
	friend KeyConfigScene; // KeyConfigScene�����F�B�F��cprivate�ł�protected�ł��A�N�Z�X�\
private:
	/// <summary>
	/// ���Ӌ@����
	/// </summary>
	enum class PeripheralType
	{
		keybd, // �L�[�{�[�h
		pad1 // �p�b�h1
	};
	// ���͏���`�p
	struct InputState
	{
		PeripheralType type;
		int id; // ���͂�ID
	};

	using InputTable_t = std::map < std::string, std::vector<InputState>>;
	using InputRecord_t = std::map < std::string, bool>;

	// ���O�Ǝ��ۂ̓��͂̑Ή��\
	InputTable_t inputTable_;
	InputTable_t tempInputTable_;

	// �؂藣���čė��p�ł���悤��
	void SetDefault();
	// �L�[�R���t�B�O�b�菈���p
	void SetTempDefault();
	// �L�[�R���t�B�O�p�̈ꎞ�e�[�u����{�e�[�u���ɔ��f
	void CommitEdittedInputTable();
	// �ꎞ�e�[�u�������ɖ߂�
	void RollbackEdittedInputTable();

	// �����ꂽ���ǂ������L�^���Ă�������
	InputRecord_t current_;
	InputRecord_t last_;
	
	std::vector<std::string> orderForDisplay;

	// ���߂̓��̓R�[�h��Ԃ��֐�
	// friend��KeyConfig�ɑ���֐�
	int GetLastKeyboadState();
	// Pad��
	int GetLastPadState();

	void SaveInputTable();
	// ���̓e�[�u���̔��f�܂ł��
	void LoadInputTable();

	// �L�[�R���p
	int currentRawPadState_;
	int lastRawPadState_;

	char currentRawKeybdState_[256];
	char lastRawKeybdState_[256];
public:
	Input();

	/// <summary>
	/// ���͏�Ԃ��X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �������u�Ԃ����o
	/// </summary>
	/// <param name="id">���̓R�[�h</param>
	/// <returns>true:�������u�� false:�����ĂȂ�or�������ςȂ�</returns>
	bool IsTrigger(std::string key) const;

	bool IsPressed(const char* key) const;
};

