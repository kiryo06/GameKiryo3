#pragma once
#include "Scene.h"
#include "Game.h"

/// <summary>
/// 操作説明シーンクラス
/// </summary>
class OperationScene : public Scene
{
private:

	enum Dir
	{
		kNutral, //通常状態 0
		kWalk,	 //歩き状態 1
		kJump,	 //ジャンプ状態 2
		kFall,   //落ちる状態 3
		kHit,	//当たった状態 4
	};

	//操作説明のハンドル
	int m_explationHandle;
	int m_frame;
	int m_animFrame;
	int m_buttonAnimFrame;



	int m_buttonHandle;

	int m_playerHandle01;
	int m_playerHandle02;

	//プレイヤーの表示座標
	float m_playerPosX;
	float m_playerPosY;

	//プレイヤーの移動量
	float m_moveX;
	float m_moveY;

	bool m_isJump;
	bool m_isLeft;
	bool m_isRight;
	bool m_isAnimJump;

	Dir m_dir;
	bool m_isAnimTurn;

	int m_animCount;
	int m_jumpCount;

	//BGMハンドル
	int m_bgmHandle;
	//SEハンドル
	int m_seHandle001; //ジャンプ音
	int m_seHandle002; //キャンセル音


	//更新メンバ関数
	void (OperationScene::* m_updateFunc)(Input& input);
	//描画メンバ関数ポインタ
	using DrawFunc_t = void(OperationScene::*)();
	DrawFunc_t m_drawFunc;

	//更新関数
	void FadeInUpdate(Input&); //フェードイン状態
	void NormalUpdate(Input&); //通常状態
	void FadeOutUpdate(Input&); //フェードアウト状態

	//描画関数
	void FadeDraw();//フェード中描画
	void NormalDraw();//非フェード描画

public:
	OperationScene(SceneManager& manager);
	virtual ~OperationScene();

	void Init();
	void Update(Input& input);
	void Draw();


};

