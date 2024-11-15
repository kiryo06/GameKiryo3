#pragma once
#include <array>

class Input
{
private:
	std::array<char, 256> m_keyState;
	std::array<char, 256> m_lastKeyState;

public:
	/// <summary>
	/// ���͏����X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �w��̃R�}���h�������ꂽ�u�ԂȂ̂�
	/// </summary>
	/// <param name="command">�R�}���h������</param>
	/// <returns>true:�����ꂽ�u�� / false:������ĂȂ�����������</returns>
	bool IsTriggered(const char* command) const;
};

