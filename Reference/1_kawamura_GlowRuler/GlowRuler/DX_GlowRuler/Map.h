#pragma once
#include "Game.h"
#include "Rect.h"
#include "DxLib.h"
#include "MapData.h"
#include <vector>
using namespace std;


namespace
{
	// 表示させるギミックの種類
	constexpr int kGimmickNum = 6;

	// チップを置く場所の開始点
	constexpr int kMapStartPosX = (Game::kScreenWidth - (kChipNumX * kChipWidth)) / 2;
	constexpr int kMapStartPosY = (Game::kScreenHeight - (kChipNumY * kChipHeight)) / 2;
}

class Wall;
class Player;
class PlayerLight;
class InColorFloor;
class OutColorFloor;
class DirWall;
class GoalPoint;

class Handle;

class EfectColor;

class Sound;

class GameBg;

class FileQuickTime;

class pColorBg;

class Map
{
public:
	Map();
	~Map();

	void Init(int mode, int mapNum, int BGM, int SE, const Handle& handle);
	void Update(bool isPause);
	void Draw(const Handle& handle);
	void Reset();

	void GoalDraw(const Handle& handle);

	bool GetTransFlag() const { return m_isTransScene; }
	int GetTime() const { return m_timer; }

	int GetAlpha() const { return m_alpha; }

	void SetSound(int BGM, int SE);

	bool GetUpdateFlag() const { return m_isUpdateTime; }

private:

	// ゲームモード
	int m_mode;
	// ステージを読み込む箱
	int chipData[kChipNumY][kChipNumX];
	//int m_chipHandle[kGimmickNum];
	// プレイヤー
	Player* m_pPlayer;
	PlayerLight* m_pLight;
	// 壁
	vector<Wall*> m_pWall;
	int m_wallCount;
	// 色変更床
	vector<InColorFloor*> m_pInColor;
	int m_inColorCount;
	// 着色床
	vector<OutColorFloor*> m_pOutColor;
	int m_outColorCount;
	// 一方通行壁
	vector<DirWall*> m_pDirWall;
	int m_dirWallCount;
	// ゴール
	GoalPoint* m_pGoal;
	int m_paintCount;
	bool m_isClear;
	// シーン遷移フラグ
	bool m_isTransScene;
	// 遷移時のアルファ値
	int m_alpha;
	// タイムアタック用
	bool m_timeAttack;
	int m_timer;

	vector<EfectColor*> m_pEfect;

	// サウンド
	std::vector<Sound*> m_pSound;
	int m_BGM;
	int m_SE;

	// バックグラウンド
	vector<GameBg*> m_pBg;
	int m_clearBgColor;

	// 最短回数
	FileQuickTime* m_pData;
	int m_mapNum;
	// 記録更新
	bool m_isUpdateTime;

	pColorBg* m_pColorBg;
	int m_stringTimer;

	// クリア表記
	int m_clearWindowTimer;
	Vec2 m_clearPos;
	int m_clearWindowY;

	// リセット
	bool m_isReset;
	
};