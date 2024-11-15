#pragma once
#include "Game.h"

class FileQuickTime
{
public:
	FileQuickTime();
	~FileQuickTime();

	void CreateData();
	void ChangeTime(int no, int time);
	int GetTime(int no);


private:

	void Save();
	void Load();

	// 各ステージデータ
	int m_stageTime[Game::kStageNum];
};

