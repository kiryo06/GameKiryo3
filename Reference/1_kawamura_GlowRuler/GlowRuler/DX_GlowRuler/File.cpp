#include "File.h"
#include "DxLib.h"
#include "Game.h"
#include <cassert>
#include <cerrno>

// 合計回数ランキング
File::File()
{
	Load();
}

File::~File()
{
	Save();
}

// 初期データ作成
void File::CreateData()
{
	for (int i = 0; i < 5; i++)
	{
		m_timeRank[i] = 3000 - (2500 -(i * 500));
	}
}

// 順位の書き換え
void File::ChangeTime(int times)
{
	for (int i = 4; i >= 0; i -= 1)
	{
		if (m_timeRank[i] > times)
		{
			if (i != 4) m_timeRank[i + 1] = m_timeRank[i];
			m_timeRank[i] = times;
		}
	}
	Save();
	Load();
}

// 指定番号番目のタイムを拾う
int File::GetTime(int no)
{
	return m_timeRank[no];
}

// セーブ
void File::Save()
{
	// ファイルの枠作成
	FILE* Writefp = nullptr;

	// == 0　でファイル存在
	if (fopen_s(&Writefp, "TimeData", "wb") == 0)
	{
		for (int i = 0; i < 5; i++)
		{
			if (m_timeRank[i] > 0)
			{
				fwrite(&m_timeRank[i], sizeof(int), 1, Writefp);
			}
		}

		fclose(Writefp);
	}
	else
	{
		assert(false);
		return;
	}
}

// ロード
void File::Load()
{
	FILE* Readfp = nullptr;
	// == 0　でファイル存在
	if (fopen_s(&Readfp, "TimeData", "rb") == 0)
	{
		// 配列個数分のintを入れる
		for (int i = 0; i < 5; i++)
		{
			fread(&m_timeRank[i], sizeof(int), 1, Readfp);
		}
		fclose(Readfp);
	}
	// ファイルが無い(初プレイ)時の初期データ作成
	else
	{
		CreateData();
		Save();
		Load();
		return;
	}

}