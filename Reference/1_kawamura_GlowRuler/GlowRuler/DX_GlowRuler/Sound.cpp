#include "Sound.h"
#include "DxLib.h"
#include "Handle.h"

Sound::Sound() :
	m_num(0),
	m_handle(0),
	m_volume(0),
	m_volPow(0)
{
}

Sound::~Sound()
{
	m_handle = 0;
}

// BGMのハンドルセット
void Sound::InitBGM(const int& handle)
{
	m_handle = handle;
	m_num = 0;
}

// SEのハンドルセット
void Sound::InitSE(const int& handle)
{
	m_handle = handle;
	m_num = 1;
}

// BGM音量設定
void Sound::UpdateBGM(int BGMvol)
{
	m_volPow = BGMvol;
	// 音量設定
	if (m_num == 0 && m_volPow * 51 != m_volume)
	{
		m_volume = m_volPow * 51;
		if (this->ChackPlaying())
		{
			if (m_volPow == 0)
			{
				this->Stop();
			}
		}
		else
		{
			if(m_volPow != 0)
				this->LoopPlay();
		}
		ChangeVolumeSoundMem(m_volume, m_handle);
	}
}

// SE音量設定
void Sound::UpdateSE(int SEvol)
{
	m_volPow = SEvol;
	// 音量設定
	if (m_num == 1 && m_volPow * 51 != m_volume)
	{
		m_volume = m_volPow * 51;
 		ChangeVolumeSoundMem(m_volume, m_handle);
	}
}

// 一回のみ再生
void Sound::OnePlay()
{
	if(m_volPow != 0)
		PlaySoundMem(m_handle, DX_PLAYTYPE_BACK, true);
}

// ループ再生
void Sound::LoopPlay()
{
	if (m_volPow != 0)
		PlaySoundMem(m_handle, DX_PLAYTYPE_LOOP, true);
}

// サウンド停止
void Sound::Stop()
{
	StopSoundMem(m_handle);
}

// 現在音が流れているか
bool Sound::ChackPlaying() const
{
	return CheckSoundMem(m_handle);
}
