#pragma once
#include "Vec2.h"
#include "MapData.h"

class Map;

class Wall;
class Player;
class PlayerLight;
class InColorFloor;
class OutColorFloor;
class DirWall;
class GoalPoint;
class Handle;

class Window;
class StageFile;

struct MapChip
{
	int stageData[kChipNumY][kChipNumX];
};

class StageMakerScene
{
public:
	StageMakerScene();
	~StageMakerScene();


	void Init(int gameMode);
	void Update();
	void ChipInit(int chipNum);
	void Draw(const Handle& handle);

	// 作ったステージデータの引き渡し
	MapChip GetChip() const { return m_stage; }

	bool GetBackFlag()const { return m_isBack; }


private:
	// ステージデータ
	MapChip m_stage;
	// ステージ選択
	Window* m_pWindow;

	// チップデータ
	Wall* m_pWall;
	Player* m_pPlayer;
	PlayerLight* m_pLight;
	InColorFloor* m_pInColor;
	OutColorFloor* m_pOutColor;
	DirWall* m_pDirWall;
	GoalPoint* m_pGoal;
	// ステージデータファイルポインタ
	StageFile* m_pFile;

	// プレイヤーの配置状況
	bool m_isPlayer;
	// ゴールの配置状況
	bool m_isGoal;
	// ステージ番号
	int m_stageNum;
	// ゴール色
	int m_goalColor;
	int m_R;
	int m_G;
	int m_B;

	// ステージ作成モード
	bool m_isMake;
	// チップ選択
	bool m_isSelect;
	// ステージ保存の為のクリアチェック
	bool m_isClear;
	
	// 選択カーソル位置
	Vec2 m_cursorPos;
	// モード選択
	int m_mode;
	//　マス目
	int m_X;
	int m_Y;
	int m_animaTimer;
	float m_triMove;

	// 素材名のstring長さ
	int m_stringWidth;

	// プレイ部分
	Map* m_pMap;

	// 直前フレームのキー入力状況
	bool m_isLastHitKey;

	// タイトルバックフラグ
	bool m_isBack;
};

