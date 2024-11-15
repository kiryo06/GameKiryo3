#include "DxLib.h"
#include "Game.h"
#include "SceneManager.h"

// スクリーンサイズ
#define SCREEN_W 1280
#define SCREEN_H 720


// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// アイコン変更
	SetWindowIconID(111);

	// システムバータイトル
	SetWindowTextA("Glow Ruler");

	// 画面モードの設定
	SetGraphMode(SCREEN_W, SCREEN_H, Game::kColorDepth);		// 解像度をSCREEN_W*SCREEN_H、colorを16bitに設定.
	
	// ウインドウモード
	ChangeWindowMode(true);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	// 裏画面に描画を行う
	SetDrawScreen(DX_SCREEN_BACK);

	// Scene開始
	SceneManager* manager = new SceneManager;
	manager->Init();

	// ゲームループ
	while (ProcessMessage() != -1)
	{
		// フレーム開始時刻を覚えておく
		LONGLONG start = GetNowHiPerformanceCount();

		// 描画を行う前に画面をクリアにする
		ClearDrawScreen();

		// ゲームの処理
		manager->Update();
		manager->Draw();
		manager->SceneMove();
		// ChangeFontFromHandle(fontHandle_32);

		// 画面が切り替わるのを待つ
		ScreenFlip();

		// end処理
		if (manager->End())
		{
			// メモリの解放
			delete manager;
			manager = nullptr;
			break;
		}


		// FPSを60に固定
		while (GetNowHiPerformanceCount() - start < 16667)
		{
			// 16,66ミリ秒(16667マイクロ秒)経過まで待つ
		}
	}
	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}