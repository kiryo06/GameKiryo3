#pragma once
#include "Vec2.h"
#include "Game.h"
#include <vector>

struct Rank
{
	int time_1;
	int time_2;
	int time_3;
	int time_4;
	int time_5;

};

class Sound;

class Handle;

class EndingScene
{
public:
	EndingScene();
	~EndingScene();

	void Init(int time, int gameMode,int BGM,int SE, const Rank& timeRank, const Handle& handle);
	void Update();
	void Draw(const Handle& handle);

	bool GetTransFlag() const { return m_isTransScene; }

private:
	// int m_handle;
	// タイトル位置
	Vec2 m_pos;
	// タイトルサイズ(Width)
	int m_clearWidth;
	int m_startWidth;
	int m_timeWidth;
	// 透過度アルファ
	int m_alpha;
	bool m_isAlpha;
	// pressの点滅時間
	int m_appStartTimer;
	// シーン遷移フラグ
	bool m_isKey;
	bool m_isTransScene;

	int m_gameMode;
	int m_resultTime;
	Rank m_RankResult;

	// サウンド
	std::vector<Sound*> m_pSound;

	// エフェクト
	int m_efectDir;
	int m_FadeAlpha;

	// ランキング
	int m_rankPosMove[Game::kRankNum];
	int m_flashTimer;
	bool m_isUpdateSound;
};

