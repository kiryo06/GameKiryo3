#pragma once
#include "Scene.h"
#include "Game.h"
/// <summary>
/// ゲームオーバーシーンクラス
/// </summary>
class GameClearScene :
	public Scene
{
private:
	//カーソル選択
	enum Select
	{
		Title,	//ド級のリトライ
	};

	enum Dir
	{
		kNutralRight, //通常状態 0
		kNutralLeft, //通常状態 1
		kWalkRight,	 //右歩き状態 2
		kWalkLeft,	 //左歩き状態 3
	};

	//グラフィックハンドル
	int m_handle;
	int m_playerHandle;
	int m_bgHandle;
	int m_goalHandle;

	//フレーム
	int m_frame;
	int m_animFrame;
	int m_clearFrame;
	int m_goalFrame;

		//キャラの表示座標
	float m_playerPosX;
	float m_playerPosY;
	
	int m_goalPosX;
	int m_goalPosY;

	//動き
	float m_moveX;
	float m_moveY;

	Dir m_dir;
	bool m_isTurn;
	bool m_isAction;
	bool m_isClear;

	int nowButton = Title;
	int m_pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);


	//グラフィックハンドル
	int m_titleHandle01;
	//BGMハンドル
	int m_bgmHandle;
	//SEハンドル
	int m_seHandle001; //決定音
	int m_seHandle002; //選択音

	//更新メンバ関数
	void (GameClearScene::* updateFunc_)(Input& input);
	//描画メンバ関数ポインタ
	using DrawFunc_t = void(GameClearScene::*)();
	DrawFunc_t drawFunc_;

	//更新関数
	void FadeInUpdate(Input&); //フェードイン状態
	void NormalUpdate(Input&); //通常状態
	void FadeOutUpdate(Input&); //フェードアウト状態

	//描画関数
	void FadeDraw();//フェード中描画
	void NormalDraw();//非フェード描画

public:
	GameClearScene(SceneManager& manager);
	~GameClearScene();
	void Update(Input& input);
	void Draw();
};

