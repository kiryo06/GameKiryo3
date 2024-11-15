#include "Application.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "Input.h"
#include "Player.h"
#include "Map.h"

#include "Game.h"
#include "DxLib.h"
#include <cassert>
#include <memory>

int MyLoadGraph(const TCHAR* path) {
	int handle = LoadGraph(path);
	assert(handle > 0);
	return handle;
}

void Application::Terminate()
{
	DxLib_End();				// ＤＸライブラリ使用の終了処理
}

bool Application::Init()
{
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);
	// 一部の関数はDxLib_Init()の前に実行する必要がある
	ChangeWindowMode(false);

	//アイコンのID番号を読み込む
	SetWindowIconID(111);

	SetWindowText("Action To Avoid");
	if (DxLib_Init() == -1) {
		return false;
	}

	SetDrawScreen(DX_SCREEN_BACK);
	return true;
}

void Application::Run()
{

	SceneManager manager;
	manager.ChangeScene(new TitleScene(manager));
	Input input;
	// ゲームループ
	while (ProcessMessage() != -1)
	{
		// このフレームの開始時刻を覚えておく
		LONGLONG start = GetNowHiPerformanceCount();

		// 描画を行う前に画面をクリアする
		ClearDrawScreen();
		input.Update();
		manager.Update(input);
		manager.Draw();

		// 画面が切り替わるのを待つ
		ScreenFlip();

		// FPS60に固定する
		while (GetNowHiPerformanceCount() - start < 16667)
		{
			// 16.66ミリ秒(16667マイクロ秒)経過するまで待つ
		}
	}
	Terminate();
}
