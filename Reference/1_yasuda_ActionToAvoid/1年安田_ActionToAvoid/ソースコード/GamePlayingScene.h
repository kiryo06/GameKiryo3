#pragma once
#include "Scene.h"
#include "Vec2.h"
#include <vector>
#include <memory>

class Player;
class EnemyBase;
class ItemBase;
class Map;
class Goal;

/// <summary>
/// ゲームプレイシーンクラス
/// </summary>
class GamePlayingScene : public Scene
{
private:
	int m_handle;
	int m_playerHandle;
	int m_enemyRunHandle;
	int m_enemyJumpHandle;
	int m_enemyJumpRunHandle;
	int m_map01Handle;
	int m_map02Handle;
	int m_itemHandleHp;
	int m_itemHandleBigHp;
	int m_goalHandle;
	int m_hpHandle;
	int m_tutorial001Handle;
	int m_tutorial002Handle;
	int m_tutorial003Handle;

	//BGMハンドル
	int m_bgmHandle;

	//SEハンドル
	int m_seHandle001; //ダメージ音
	int m_seHandle002; //ダメージ音(下に落ちた時の音)
	int m_seHandle003; //アイテム音
	int m_seHandle004; //ゴール音
	int m_seHandle005; //崖に落ちた時の音

	int m_frame = 0;//フェードするタイミングのフレーム
	int m_damageFrame = 0;//ダメージを受けた際の無敵時間の間隔フレーム

	bool m_isPlayerHit = false;
	bool m_isItemHit = false;
	bool m_isGoalHit = false;
	

	bool m_isGameOverFade = false;
	bool m_isGoalFade = false;

	//プレイヤーのHP
	int m_hp = 3;

	//背景のX座標
	int m_areaX;
	

	//アイテムのY座標
	float m_animationHeight;

	//アイテムの当たり判定をなくすフラグ
	bool m_isExist;
	//プレイヤーの当たり判定をなくすフラグ
	bool m_isDamage;

	Vec2 m_shakeVec = {};//画面揺れの移動ベクトル
	int m_shakeFrame = 0;//画面揺れの時間
	float m_amp = 10.0f;//画面揺れの振れ幅
	int RT_;//画面の状況を記録

	//プレイヤーのメモリ確保
	std::shared_ptr<Player> pPlayer;
	//敵のメモリ確保
	std::vector<EnemyBase*> pEnemy;
	//マップのメモリ確保
	std::shared_ptr<Map> pMap;
	//ゴールのメモリ確保
	std::shared_ptr<Goal> pGoal;
	//アイテムのメモリ確保
	std::vector<ItemBase*> pItem;

	//更新メンバ関数
	void (GamePlayingScene::* updateFunc_)(Input& input);
	//描画メンバ関数ポインタ
	using DrawFunc_t = void(GamePlayingScene::*)();
	DrawFunc_t drawFunc_;

	//更新関数
	void FadeInUpdate(Input&); //フェードイン状態
	void NormalUpdate(Input&); //通常状態
	void FadeOutUpdateGameOver(Input&); //フェードアウト状態
	void FadeOutUpdateGameClear(Input&); //フェードアウト状態

	//描画関数
	void FadeDraw();//フェード中描画
	void NormalDraw();//非フェード描画

	void CreateEnemyRun(float x, float y); //走る敵を生成する関数
	void CreateEnemyJump(float x, float y); //ジャンプする敵を生成する関数
	void CreateEnemyJumpRun(float x , float y);//走ってジャンプする敵を生成する関数

	void CreateItemHp(float x, float y); //HPを１回復してくれるアイテムの生成
	void CreateItemBigHp(float x, float y);//HPを３回復してくれるアイテムの生成

	void BackScroll(const int areaX, const int handle, const int width, const int height);//スクロールする描画

public:
	GamePlayingScene(SceneManager& manager);//コンストラクタ
	~GamePlayingScene();//デストラクタ

	void Init();//初期化
	void Update(Input& input);//アップデート処理
	void Draw();//描画処理

	int GetScrollX();//Xのスクロール
	int GetScrollY();//Yのスクロール
};

