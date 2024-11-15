#pragma once
#include "Vec2.h"


// class GameBg;
class Map;
class GameUI;
class Window;
class Handle;

class File;

class GameScene
{
public:
	GameScene();
	~GameScene();


	void Init(int stageNum, int gameMode, int light, int BGM, int SE, const Handle& handle);
	void StageUpdate(const Handle& handle);
	void Update();
	void Draw(const Handle& handle);

	bool GetTransFlag() const { return m_isTransScene; }
	int GetTime() const { return m_time; }
	int GetSumTime() const { return m_sumTime; }
	bool GetBackFlag() const { return m_isBackScene; }

	int GetBGM() const;
	int GetSE() const;
	int GetLight() const;
	void SetUti(int BGM, int SE, int light);

private:
	// ゲーム本体
	Map* m_pMap;
	int m_stageNum;
	// UI
	GameUI* m_pUI;
	bool m_isPause;
	bool m_isSetting;
	// ポーズ
	Window* m_pWindow;
	bool m_isBackScene;
	// シーン全般
	// シーン遷移フラグ
	bool m_isTransScene;
	// 開始とクリア時の明暗
	int m_alpha;

	// スコア表記
	Vec2 m_timePos;
	int m_time;
	int m_timeWidth;
	int m_sumTime;

	// ゲームモード
	int m_isTimeAttack;

	// 直前フレームのキー入力
	bool m_isRastHit;

	// キー入力のクールタイム
	int m_keyTimer;

	// 記録更新時の点滅用
	int m_UpdateTimer;

	// おまけ煽り文章の位置
	Vec2 m_incitePos;
};

