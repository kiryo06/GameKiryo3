#pragma once
#include "Scene.h"
#include "Game.h"
#include "Pad.h"



/// <summary>
/// ゲームオーバーシーンクラス
/// </summary>
class GameOverScene :
    public Scene
{
private:
	//カーソル選択
	enum Select
	{
		Retry,	//ド級のリトライ
		Title, //タイトル画面へ
	};

	enum Dir
	{
		kNutralRight, //通常状態 0
		kNutralLeft, //通常状態 1
		kWalkRight,	 //右歩き状態 2
		kWalkLeft,	 //左歩き状態 3
	};

	int m_handle;
	int m_playerHandle;

	int m_pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	

	//キャラの表示座標
	float m_playerPosX = Game::kScreenWidth * 0.5;
	float m_playerPosY = 420;

	//動き
	float m_moveX = 0.0f;
	float m_moveY = 0.0f;

	int m_frame = 0;
	int m_animFrame = 0;

	//選択ボタン
	int nowButton = Retry;
	
	//セレクト画面
	int m_retryHandle01;
	int m_titleHandle01;

	//セレクトされているハンドル
	int m_retryHandle02;
	int m_titleHandle02;


	//BGMハンドル
	int m_bgmHandle;
	//SEハンドル
	int m_seHandle001; //決定音
	int m_seHandle002; //選択音


	Dir m_dir = kNutralRight;
	bool m_isTurn = false;
	bool m_isActionR = false;
	bool m_isActionL = false;


	//更新メンバ関数
	void (GameOverScene::* updateFunc_)(Input& input);
	//描画メンバ関数ポインタ
	using DrawFunc_t = void(GameOverScene::*)();
	DrawFunc_t drawFunc_;

	//更新関数
	void FadeInUpdate(Input&); //フェードイン状態
	void NormalUpdate(Input&); //通常状態
	void FadeOutUpdate(Input&); //フェードアウト状態

	//描画関数
	void FadeDraw();//フェード中描画
	void NormalDraw();//非フェード描画

public:
	GameOverScene(SceneManager& manager);
	~GameOverScene();
	void Update(Input& input);
	void Draw();
};

