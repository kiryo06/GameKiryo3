#pragma once

// ��ʏ���萔��`
// �Ȃ�قǁI�������΂悩�����񂾂��I 

namespace Game
{
	// �萔�ɂ�k��擪�ɕt����
	// m�Ƃ�s�Ƃ�k�Ƃ���擪�ɕt�����
	// �\�����o�₷���ˁI 
	//constexpr int kScreenWidth = 1280;
	//constexpr int kScreenHeight = 720; // 16:9������
	constexpr int kScreenWidth = 640;
	constexpr int kScreenHeight = 480; // �̂̃u���E���ǂ̔䗦�炵�� DXLib�̃f�t�H���g
	//constexpr int kScreenWidth = 1280;
	//constexpr int kScreenHeight = 720; // �l�I�ɐ���
	constexpr int kColorBitNum = 32;

	constexpr bool kDefaultWindowMode = true;
}