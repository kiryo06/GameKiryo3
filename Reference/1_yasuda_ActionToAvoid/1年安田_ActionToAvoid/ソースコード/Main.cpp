#include "Application.h"
#include <DxLib.h>


// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Application& application = Application::GetInstance();
	if (!application.Init()) {
		return -1;//���̃A�v���͕s���I�����܂���
	}
	application.Run();
	return 0;//���̃A�v���͏I�����܂���
}