#pragma once
#include "Game.h"

class File
{
public:
	File();
	~File();

	// 全体ランキング
	void CreateData();
	void ChangeTime(int time);
	int GetTime(int no);
	
private:

	void Save();
	void Load();

private:
	// ファイルデータ
	// ランキングデータ
	int m_timeRank[5];

	// 各ステージデータ
	// int m_stageTime[Game::kStageNum];
};