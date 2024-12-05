#include "DxLib.h"
#include "game.h"
#include "SceneManager.h"
#include "Application.h"
// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	/*�R���\�[��Debug�p*/
#ifdef _DEBUG
	AllocConsole();        // �R���\�[��
	FILE* out = 0; 
	freopen_s(&out, "CON", "w", stdout); // stdout
	FILE* in = 0; 
	freopen_s(&in, "CON", "r", stdin);   // stdin
#endif
	// �t���X�N���[���łȂ��A�E�B���h�E���[�h�ŊJ���悤�ɂ���
	ChangeWindowMode(Game::kDefaultWindowMode);

	// ��ʂ̃T�C�Y��ύX����B��O�����͐F�Ɏg������(�r�b�g)
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

		//���t���b�V������(-1�Ȃ�G���[)
		if (ProcessMessage() < 0) { break; }

		//Debug.
#ifdef _DEBUG

		printf("ssa\n"); 

#endif // DEBUG
		//���[�v�I������
		if (CheckHitKey(KEY_INPUT_ESCAPE)) { break; }

		// 60FPS�ɌŒ�
		while (GetNowHiPerformanceCount() - time < 16667);
	}

	WaitKey();				// �L�[���͑҂�

		/*�I������*/
	DxLib_End();//Dxlib�I������
#ifdef _DEBUG//�R���\�[��Debug�p
	fclose(out); fclose(in); FreeConsole();//�R���\�[�����
#endif
	return 0;//�v���O�����I��
}