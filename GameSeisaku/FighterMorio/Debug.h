#pragma once
#include "DxLib.h"

namespace
{
	constexpr int kTransparency = 160;	//�����x		����{0} �` ����{255}   
}

// �������̐ݒ�
#define DEBUG_TRANSPARENCY	SetDrawBlendMode(DX_BLENDMODE_ALPHA, kTransparency);
// ���ɖ߂�
#define DEBUG_RESET	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);