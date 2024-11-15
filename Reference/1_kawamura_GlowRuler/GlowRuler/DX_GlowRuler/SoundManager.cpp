#include "SoundManager.h"
#include "DxLib.h"

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
}

void SoundManager::UpdateVol(std::string name, int vol)
{
	// 音量設定
	//if (m_num == 0 && m_volPow * 51 != m_volume)
	//{
	//	m_volume = m_volPow * 51;
	//	if (this->ChackPlaying(name))
	//	{
	//		if (m_volPow == 0)
	//		{
	//			this->Stop();
	//		}
	//	}
	//	else
	//	{
	//		if (m_volPow != 0)
	//			this->LoopPlay();
	//	}
	//	
	//}
	ChangeVolumeSoundMem(m_sound[name].vol, m_sound[name].handle);
}

void SoundManager::OnePlay(std::string name)
{
	if (m_sound[name].vol != 0)
		PlaySoundMem(m_sound[name].handle, DX_PLAYTYPE_BACK, true);
}

void SoundManager::LoopPlay(std::string name)
{
	if (m_sound[name].vol != 0)
		PlaySoundMem(m_sound[name].handle, DX_PLAYTYPE_LOOP, true);
}

void SoundManager::Stop(std::string name)
{
	StopSoundMem(m_sound[name].handle);
	StopSoundMem(m_sound[name].handle);
}

bool SoundManager::ChackPlaying(std::string name)
{
	return CheckSoundMem(m_sound[name].handle);
}

int SoundManager::GetVol(std::string name)
{
	return m_sound[name].vol;
}
