#pragma once
#include <array>

class Input
{
private:
	std::array<char, 256> m_keyState;
	std::array<char, 256> m_lastKeyState;

public:
	/// <summary>
	/// 入力情報を更新する
	/// </summary>
	void Update();

	/// <summary>
	/// 指定のコマンドが押された瞬間なのか
	/// </summary>
	/// <param name="command">コマンド文字列</param>
	/// <returns>true:押された瞬間 / false:押されてないか押しっぱ</returns>
	bool IsTriggered(const char* command) const;
};

