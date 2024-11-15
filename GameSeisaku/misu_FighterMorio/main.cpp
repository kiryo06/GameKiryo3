#include "DxLib.h"
#include "game.h"
#include "SceneManager.h"
// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	
	// フルスクリーンでなく、ウィンドウモードで開くようにする
	// こういった関数はウィンドウが開く前(DXLib_Init()の前)に処理しておく
	ChangeWindowMode(Game::kDefaulWindowMode);

	// 画面のサイズを変更する
	// 第三引数は色に使う情報量(ビット)
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kScreenBitNum);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	// 描画先を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);

	SceneManager* pSceneManager = new SceneManager();
	pSceneManager->Init();
	// ゲームループ
	while (ProcessMessage() == 0) // Windowsが行う処理を待つ必要がある
	{
		// 今回のループが始まった時間を覚えておく
		LONGLONG time = GetNowHiPerformanceCount();

		// 画面全体をクリアする
		ClearDrawScreen();

		// ここにゲームの処理を書く
		pSceneManager->Update();
		pSceneManager->Draw();

		// 画面の切り替わりを待つ
		ScreenFlip();

		// 60FPSに固定
		while (GetNowHiPerformanceCount() - time < 16667);
	}

	WaitKey();				// キー入力待ち

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}


#ifdef DEBUG
// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// フルスクリーンでなく、ウィンドウモードで開くようにする
	// こういった関数はウィンドウが開く前(DXLib_Init()の前)に処理しておく
	ChangeWindowMode(Game::kDefaulWindowMode);

	// 画面のサイズを変更する
	// 第三引数は色に使う情報量(ビット)
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kScreenBitNum);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	// 描画先を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);

	//素材をグラフィックにメモリをロード
	int handle = LoadGraph("player.bmp");

	// ゲームループ
	while (ProcessMessage() == 0) // Windowsが行う処理を待つ必要がある
	{
		// 今回のループが始まった時間を覚えておく
		LONGLONG time = GetNowHiPerformanceCount();

		// 画面全体をクリアする
		ClearDrawScreen();

		// ここにゲームの処理を書く
		DrawGraph(240, 120, handle, true);

		// 画面の切り替わりを待つ
		ScreenFlip();

		// 60FPSに固定
		while (GetNowHiPerformanceCount() - time < 16667);
	}

	WaitKey();				// キー入力待ち

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}
#endif // DEBUG