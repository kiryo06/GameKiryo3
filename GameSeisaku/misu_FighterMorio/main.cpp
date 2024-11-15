#include "DxLib.h"
#include "game.h"
#include "SceneManager.h"
// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	
	// �t���X�N���[���łȂ��A�E�B���h�E���[�h�ŊJ���悤�ɂ���
	// �����������֐��̓E�B���h�E���J���O(DXLib_Init()�̑O)�ɏ������Ă���
	ChangeWindowMode(Game::kDefaulWindowMode);

	// ��ʂ̃T�C�Y��ύX����
	// ��O�����͐F�Ɏg������(�r�b�g)
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kScreenBitNum);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	// �`���𗠉�ʂɂ���
	SetDrawScreen(DX_SCREEN_BACK);

	SceneManager* pSceneManager = new SceneManager();
	pSceneManager->Init();
	// �Q�[�����[�v
	while (ProcessMessage() == 0) // Windows���s��������҂K�v������
	{
		// ����̃��[�v���n�܂������Ԃ��o���Ă���
		LONGLONG time = GetNowHiPerformanceCount();

		// ��ʑS�̂��N���A����
		ClearDrawScreen();

		// �����ɃQ�[���̏���������
		pSceneManager->Update();
		pSceneManager->Draw();

		// ��ʂ̐؂�ւ���҂�
		ScreenFlip();

		// 60FPS�ɌŒ�
		while (GetNowHiPerformanceCount() - time < 16667);
	}

	WaitKey();				// �L�[���͑҂�

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}


#ifdef DEBUG
// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �t���X�N���[���łȂ��A�E�B���h�E���[�h�ŊJ���悤�ɂ���
	// �����������֐��̓E�B���h�E���J���O(DXLib_Init()�̑O)�ɏ������Ă���
	ChangeWindowMode(Game::kDefaulWindowMode);

	// ��ʂ̃T�C�Y��ύX����
	// ��O�����͐F�Ɏg������(�r�b�g)
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kScreenBitNum);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	// �`���𗠉�ʂɂ���
	SetDrawScreen(DX_SCREEN_BACK);

	//�f�ނ��O���t�B�b�N�Ƀ����������[�h
	int handle = LoadGraph("player.bmp");

	// �Q�[�����[�v
	while (ProcessMessage() == 0) // Windows���s��������҂K�v������
	{
		// ����̃��[�v���n�܂������Ԃ��o���Ă���
		LONGLONG time = GetNowHiPerformanceCount();

		// ��ʑS�̂��N���A����
		ClearDrawScreen();

		// �����ɃQ�[���̏���������
		DrawGraph(240, 120, handle, true);

		// ��ʂ̐؂�ւ���҂�
		ScreenFlip();

		// 60FPS�ɌŒ�
		while (GetNowHiPerformanceCount() - time < 16667);
	}

	WaitKey();				// �L�[���͑҂�

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}
#endif // DEBUG