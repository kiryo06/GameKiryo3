#pragma once
#include "Vec2.h"
#include <vector>
class Uti;
class Sound;

class Handle;

class Window
{
public:
	Window();
	~Window();
	void Init(const Handle& handle);
	void Open();
	void Close();
	void WindowDraw(const Handle& handle);

	// ウインドウの種類
	void Pause(bool flag);
	void Setting();
	void Credit();
	void Maker();

	void CursorUpdate();

	bool GetBackTitle()const { return m_isTitle; }
	bool GetPause()const { return m_isPause; }
	bool GetMakerFlag() const { return m_isMaker; }
	bool GetGoMakeFlag()const { return m_isGoMake; }
	int GetMakeNum() const { return m_stageNum; }
	bool GetSettingFlag() const { return m_isSetting; }
	bool GetCreditFlag() const { return m_isCredit; }


	int GetBGM() const { return m_BGMSet; }
	void SetSetting(int BGM, int SE, int light);
	int GetSE() const { return m_SESet; }
	int GetLight() const { return m_lightSet; }

private:
	// ウインドウ画面サイズ
	int m_menuWidth;
	int m_menuHeight;

	// 各ウインドウの表示状況
	bool m_isWindow;
	// ポーズ
	bool m_isPause;
	// 設定
	bool m_isSetting;
	// クレジット
	bool m_isCredit;
	// ステージメーカー
	bool m_isMaker;
	bool m_isGoMake;
	int m_goTimer;
	bool m_isSelect;
	int m_stageNum;

	// 文字列の開始点（x座標）
	Vec2 m_stringPos;
	float m_BackWidth;
	// 文字列表示フラグ
	bool m_isAppString;

	// ポーズからタイトルへ戻るフラグ
	bool m_isTitle;
	int m_keyTimer;

	bool m_isRastHit;

	// BGM音量( 1 ～ 5 )
	bool m_isBGM;
	int m_BGMSet;

	// SE音量( 1 ～ 5 )
	bool m_isSE;
	int m_SESet;

	// 光量( 1 ～ 5 )
	bool m_islight;
	int m_lightSet;

	// カーソル位置
	Vec2 m_cursorPos;
	// カーソル箇所(0:タイムアタック　1:選択スタート　2:設定　3:ゲーム終了　4:権利表記)
	int m_menuNum;

	// サウンド
	std::vector<Sound*> m_pSound;
};

