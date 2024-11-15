#include "Pad.h"
#include "DxLib.h"

namespace
{
	// ���݂̃t���[���̃p�b�h����
	int padInput = 0;
	// �ЂƂO�̃t���[���̃p�b�h����
	int lastInput = 0;
}

namespace Pad
{
	void Update()
	{
		// �O�̃t���[���ɉ�����Ă����{�^���̏����o���Ă���
		lastInput = padInput;
		// ���̃t���[���ɉ�����Ă���{�^���̏����擾����
		padInput = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	}

#if false

	// Press����̎擾
	// �߂�l:������Ă�����true,������Ă��Ȃ�������false
	// ����:������s�������{�^��
	bool IsPress(int button)
	{
		if (padInput & button)
		{
			return true;
		}
		else
		{
			return false;
		}
	}


	// Trigger����̎擾
	bool IsTrigger(int button)
	{
		// ������Ă��Ȃ������炻���false
		if (!(padInput & button))
		{
			return false;
		}

		// �O�̃t���[���Ƀ{�^����������Ă��Ȃ���Ή����ꂽ�u�Ԃ��Ɣ���ł���
		// �O�̃t���[���ɉ�����Ă���Ȃ炻���false
		if (lastInput & button)
		{
			return false;
		}
		else
		{
			// ���I���ꂽTrigger�����͂�
			return true;
		}
	}

#else
	// Press����̎擾
	// �߂�l:������Ă�����true,������Ă��Ȃ�������false
	// ����:������s�������{�^��
	bool IsPress(int button)
	{
		// ������Ă���true�Ŗ߂�l��true�����炱��ł������
		return (padInput & button);
	}

	// Trigger����̎擾
	bool IsTrigger(int button)
	{
		// ������Ă����true�����łȂ��Ȃ�false
		// ������ƕ�����₷��
		bool isNow = (padInput & button);
		bool isLast = (lastInput & button);
		return (isNow && !isLast);
	}
#endif
}