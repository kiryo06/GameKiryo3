#include "MapData.h"



MapData::MapData()
{
}

MapData::~MapData()
{
}

int MapData::SetMap(int stageNum, int y, int x)
{
	return kStage[stageNum][y][x];
}