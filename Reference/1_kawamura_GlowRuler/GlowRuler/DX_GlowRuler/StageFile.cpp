#include "StageFile.h"
#include "DxLib.h"
#include <cassert>

StageFile::StageFile()
{
	
	Load();
}

StageFile::~StageFile()
{
	Save();
}

void StageFile::CreateData()
{
	for (int i = 0; i < 10; i++)
	{
		for (int y = 0; y < 14; y++)
		{
			for (int x = 0; x < 19; x++)
			{
				if(y == 0 || y == 13 || x == 0 || x == 18)
					m_createData[i].stage[y][x] = 1;
				else
					m_createData[i].stage[y][x] = 0;
			}
		}
	}
}

void StageFile::ChangeData(int no, Data stage)
{
	m_createData[no] = stage;
	Save();
}

// マップの書き出し
Data StageFile::GetMapData(int no)
{
	return m_createData[no];
}

void StageFile::Save()
{
	FILE* fp = nullptr;
	if (fopen_s(&fp, "StageData", "wb") == 0)
	{
		for (int i = 0; i < 10; i++)
		{
			for (int y = 0; y < 14; y++)
			{
				for (int x = 0; x < 19; x++)
				{
					if (m_createData[i].stage[y][x] >= 0)
					{
						fwrite(&m_createData[i].stage[y][x], sizeof(int), 1, fp);
					}
				}
			}
		}
		fclose(fp);
	}
	else
	{
		assert(false);
		return;
	}
}

void StageFile::Load()
{
	FILE* fp = nullptr;
	if (fopen_s(&fp, "StageData", "rb") == 0)
	{
		for (int i = 0; i < 10; i++)
		{
			for (int y = 0; y < 14; y++)
			{
				for (int x = 0; x < 19; x++)
				{
					fread(&m_createData[i].stage[y][x], sizeof(int), 1, fp);
				}
			}
		}
		fclose(fp);
	}
	else
	{
		CreateData();
		Save();
		Load();
		return;
	}
}
