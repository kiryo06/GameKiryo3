#pragma once
#include "Scene.h"
#include "Game.h"



/// <summary>
/// タイトルシーンクラス
/// </summary>
class TitleScene : public Scene
{
public:
	TitleScene(SceneManager& manager);
	virtual ~TitleScene();

	void Init();
	void Update(Input& input);
	void Draw();

	void BackScroll(const int areaX, const int handle, const int width, const int height);

private:
	//カーソル選択
	enum Select
	{
		Start,		//スタート
		Explation,	//説明
		End,	//終了
	};

	enum Dir
	{
		kNutralRight, //通常状態 0
		kNutralLeft, //通常状態 1
		kWalkRight,	 //右歩き状態 2
		kWalkLeft,	 //左歩き状態 3
	};

	//選択ボタン
	int m_nowButton;

	//グラフィックハンドル
	int m_TitleLogHandle;
	int m_bgHandle;
	int m_playerHandle;

	//セレクト画面
	int m_startHandle01;
	int m_explationHandle01;
	int m_optionHandle01;
	int m_endHandle01;

	//セレクトされている時のハンドル
	int m_startHandle02;
	int m_explationHandle02;
	int m_optionHandle02;
	int m_endHandle02;

	//ボタンのハンドル
	int m_decisionHandle;
	int m_buttonHandle;

	//BGMハンドル
	int m_bgmHandle;
	//SEハンドル
	int m_seHandle001; //決定音
	int m_seHandle002; //選択音
	int m_seHandle003; //キャンセル音

	//フレーム
	int m_frame = 0;
	int m_animFrame = 0;
	int m_buttonAnimFrame = 0;

	//表示位置
	float m_posX = Game::kScreenWidth * 0.25;
	float m_posY = 100.0f;

	float m_playerPosX = 0;
	float m_playerPosY = 690;

	bool m_isAction = false;

	bool m_isStartFade = false;
	bool m_isFade = false;
	bool m_isHalfFade = false;

	//動き
	float m_moveX = 0.0f;
	float m_moveY = 0.0f;

	Dir m_dir = kWalkRight;

	//背景のX座標
	int m_areaX;

	//更新メンバ関数
	void (TitleScene::* m_updateFunc)(Input& input);
	//描画メンバ関数ポインタ
	using DrawFunc_t = void(TitleScene::*)();
	DrawFunc_t m_drawFunc;

	//更新関数
	void FadeInUpdate(Input&); //フェードイン状態
	void NormalUpdate(Input&); //通常状態
	void FadeOutUpdate(Input&); //フェードアウト状態
	void FadeOutUpdateStart(Input&);//スタートを押した場合のフェードアウト状態
	void NoFadeOutUpdate(Input&);//フェードアウトをしない場合の関数

	//描画関数
	void FadeDraw();//フェード中描画
	void NormalDraw();//非フェード描画

};

