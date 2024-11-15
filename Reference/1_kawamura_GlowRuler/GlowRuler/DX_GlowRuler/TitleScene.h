#pragma once
#include "Vec2.h"
#include <vector>

class Window;
class Sound;
class Handle;

struct bg
{
	// タイトルBg
	Vec2 m_bgPos = { 0,0 };
	int m_bgColor = 0;

	Vec2 m_wavePos = { 0,0 };
	bool m_isWave = 0;
	int m_waveDir = 0;

	bool m_isLight = 0;
	Vec2 m_bgLightMove = {0,0};
	int m_moveTimer = 0;
	int m_bgCoolTimer = 0;
};

class TitleScene
{
public:
	TitleScene();
	~TitleScene();

	void Init(int light, int BGM, int SE, const Handle& handle);
	void Update();
	void Draw(const Handle& handle);

	bool GetTransFlag() const { return m_isTransScene; }
	int GetStartNum() const { return m_startNum; }
	int GetMode() const { return m_gameMode; }
	bool GetEndFlag() const { return m_isEnd; }

	int GetLight() const;
	int GetBGM() const;
	int GetSE() const;
	void SetUti(int BGM, int SE, int light);

private:
	// int m_handle;
	// タイトル位置
	Vec2 m_pos;
	// タイトルサイズ(Width)
	int m_titleWidth;
	int m_startWidth;
	int m_selectWidth;
	// 透過度アルファ
	int m_alpha;
	bool m_isAlpha;
	// pressの点滅時間
	int m_appStartTimer;
	int m_appSelectTimer;
	// シーン遷移フラグ
	bool m_isKey;
	bool m_isTransScene;
	// ゲームの開始点
	int m_startNum;
	// 直前フレームでキーが押されていたか
	bool m_isRastHit;
	// カーソル位置
	Vec2 m_cursorPos;
	// カーソル箇所(0:タイムアタック　1:選択スタート　2:設定　3:ゲーム終了　4:権利表記)
	int m_menuNum;
	int m_cursorMove;
	int m_cursorMoveVec;
	// ゲームモードの選択　０：タイムアタック　１：選択スタート
	int m_gameMode;
	// ゲーム終了フラグ
	bool m_isEnd;

	Window* m_pWindow;
	bool m_isMaker;
	bool m_isSetting;
	bool m_isCredit;

	bool m_isWindow;

	// サウンド
	std::vector<Sound*> m_pSound;

	// タイトルBg
	std::vector<bg> m_bg;
};

