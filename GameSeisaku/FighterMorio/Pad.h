#pragma once

namespace Pad
{
	// �v���g�^�C�v�錾

	// ///���֐��̏�œ��͂���Ɗe�v�f�̐�������������̂̃e���v���[�g���o��

	/// <summary>
	/// �p�b�h�̓��͏�ԍX�V����
	/// 1�t���[����1��̂݌Ăяo��
	/// </summary>
	void Update();

	/// <summary>
	/// Press����̎擾
	/// �p�b�h��1�̏ꍇ�̂ݑΉ�
	/// </summary>
	/// <param name="button">������s�������{�^��</param>
	/// <returns>������Ă�����true,������Ă��Ȃ�������false</returns>
	bool IsPress(int button);

	/// <summary>
	/// Trigger����(�����ꂽ�u��)�̎擾
	/// �p�b�h��1�̏ꍇ�̂ݑΉ�
	/// </summary>
	/// <param name="button">������s�������{�^��</param>
	/// <returns>�����ꂽ�u�ԂȂ�true,����ȊO��false</returns>
	bool IsTrigger(int button);
}