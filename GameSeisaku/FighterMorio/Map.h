#pragma once/
#include "Game.h"
#include "Rect.h"
#include "DxLib.h"
#include "MapDate.h"
#include <vector>
#include <memory>
using namespace std;
/*
namespace
{
//	constexpr int stageSizeY = 10;
//	constexpr int stageSizeX = 10;
}

class BaseMapChip;
class Map
{
public:
	Map();
	~Map();

	void Init(int mapNum);
	void Update();
	void Draw();
//	void Init(int mode, int mapNum, int BGM, int SE, const Handle& handle);
//	void Update(bool isPause);
//	void Draw(const Handle& handle);
//	void Reset();

//	void GoalDraw(const Handle& handle);

//	bool GetTransFlag() const { return m_isTransScene; }
//	int GetTime() const { return m_timer; }

//	int GetAlpha() const { return m_alpha; }

//	void SetSound(int BGM, int SE);

//	bool GetUpdateFlag() const { return m_isUpdateTime; }

private:
	// ○○配列
//	std::vector<std::vector<std::shared_ptr<BaseMapChip>>>m_chipData;
 
//	std::shared_ptr<BaseMapChip> m_data[stageSizeY][stageSizeX];
//	int m_stageNum;
	// ゲームモード
//	int m_mode;
	// ステージを読み込む箱
	int chipData[kChipNumY][kChipNumX];
	//int m_chipHandle[kGimmickNum];
	// プレイヤー
//	Player* m_pPlayer;
//	PlayerLight* m_pLight;
	// 壁
//	vector<Wall*> m_pWall;
//	int m_wallCount;
	// 色変更床
//	vector<InColorFloor*> m_pInColor;
//	int m_inColorCount;
	// 着色床
//	vector<OutColorFloor*> m_pOutColor;
//	int m_outColorCount;
	// 一方通行壁
//	vector<DirWall*> m_pDirWall;
//	int m_dirWallCount;
	// ゴール
//	GoalPoint* m_pGoal;
//	int m_paintCount;
//	bool m_isClear;
	// シーン遷移フラグ
//	bool m_isTransScene;
	// 遷移時のアルファ値
//	int m_alpha;
	// タイムアタック用
//	bool m_timeAttack;
//	int m_timer;

//	vector<EfectColor*> m_pEfect;

	// サウンド
//	std::vector<Sound*> m_pSound;
//	int m_BGM;
//	int m_SE;

	// バックグラウンド
//	vector<GameBg*> m_pBg;
//	int m_clearBgColor;

	// 最短回数
//	FileQuickTime* m_pData;
//	int m_mapNum;
	// 記録更新
//	bool m_isUpdateTime;

//	pColorBg* m_pColorBg;
//	int m_stringTimer;

	// クリア表記
//	int m_clearWindowTimer;
//	Vec2 m_clearPos;
//	int m_clearWindowY;

	// リセット
//	bool m_isReset;

};
*/


//-----------------------------------------------------------------------------
// 2024 Takeru Yui All Rights Reserved.
//-----------------------------------------------------------------------------

#pragma once

//-----------------------------------------//
// 定数
//-----------------------------------------//
const int MapChipSize = 32;                           // 一つのチップのサイズ
const int MapWidth = 640 / MapChipSize + (10);    // マップの横幅
const int MapHeight = 480 / MapChipSize;   // マップの縦幅

/// <summary>
/// マップチップ構造体
/// </summary>
struct MapChip
{
	VECTOR pos;	// 座標
	float w, h;	// 幅、高さ
	int chipKind;
};

/// <summary>
/// マップ構造体
/// </summary>
struct Map
{
	MapChip mapChips[MapWidth][MapHeight];
};

//-----------------------------------------//
// プロトタイプ宣言
//-----------------------------------------//
struct Camera;
void InitMap(Map& map);
void DrawMap(const Map& map, const Camera& camera);
