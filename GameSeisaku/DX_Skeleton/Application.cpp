#include "Application.h"
#include "DxLib.h"
#include "game.h"
#include "Input.h"
#include "Scene/SceneController.h"
#include <cassert>
#include <string>

Application::Application() :
	windowSize_({ 640, 480 })
{

}

Application& Application::GetInstance()
{
	// この時点でメモリが確保されてアプリ終了まで残る
	static Application app;
	return app;
}

bool Application::Init()
{
	// フルスクリーンでなく、ウィンドウモードで開くようにする
	// こういった関数はウィンドウが開く前(DXLib_Init()の前)に処理しておく必要がある
	ChangeWindowMode(Game::kDefaultWindowMode);

	// 画面のサイズを変更する
	// 第三引数は色に使う情報量(ビット)
	SetGraphMode(windowSize_.w, windowSize_.h, Game::kColorBitNum);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return false;			// エラーが起きたら直ちに終了
	}

	// 描画先を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);

	return true;
}

void Application::Run()
{
	SceneController sceneController;
	Input input;
	// ゲームループ
	constexpr uint64_t frame_milliseconds = 16;
	auto lastTime = 0;
	while (ProcessMessage() == 0) // Windowsが行う処理を受け取る関数をWhileのループごとに走らせている。
		// このWhile文はフレームの処理を行っているから毎フレーム走らせていることになる。
		// その戻り値でWhileの判定。異常(大抵ウィンドウが閉じられた時)が出たらループを抜けてプログラム終了。
	{
		// フレーム開始の時間
		LONGLONG startTime = GetNowHiPerformanceCount();

		// 画面全体をクリアする
		ClearDrawScreen();

		input.Update();

		// ここにゲームの処理を書く
		// このinputをシーン間で受け渡し続けている感じか
		sceneController.Update(input);
		sceneController.Draw();

		DrawFormatString(0, 0, 0xffffff, "fps = %2.2f", GetFPS());

		// 画面の切り替わりを待つ
		ScreenFlip();

		// 待ちを行う
		while (GetNowHiPerformanceCount() - startTime < 16667);
	}
}

void Application::Terminate()
{
	DxLib_End();				// ＤＸライブラリ使用の終了処理
}

const Size& Application::GetWindowSize() const
{
	return windowSize_;
}
