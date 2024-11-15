#include "Input.h"
#include "DxLib.h"

void Input::Update()
{
	m_lastKeyState = m_keyState;//�O�̃t���[���̏�����
	GetHitKeyStateAll(m_keyState.data());//���݂̓��͂��擾
	//GetJoypadInputState(m_keyState.data());
}

bool Input::IsTriggered(const char* command) const
{
	return !m_lastKeyState[KEY_INPUT_RETURN] && m_keyState[KEY_INPUT_RETURN];
}
