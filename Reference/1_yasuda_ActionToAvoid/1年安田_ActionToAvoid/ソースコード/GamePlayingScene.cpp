#include "DxLib.h"
#include "Input.h"
#include "Player.h"

#include "EnemyRun.h"
#include "EnemyJump.h"
#include "EnemyJumpRun.h"

#include "ItemHp.h"
#include "ItemBigHp.h"

#include "Map.h"
#include "Goal.h"
#include "GamePlayingScene.h"
#include "GameOverScene.h"
#include "SceneManager.h"
#include "GameClearScene.h"

#include "Game.h"
#include "Pad.h"
#include <cassert>
#include <memory>
#include <cmath>

namespace
{
	//Hpの個数
	constexpr int kHpNum = 3;
	
	//底の上限
	constexpr int kFallMax = 2000;

	//背景スクロールの速さ
	constexpr int kBgSpeed = 5;

	constexpr float kSinSpeed = 0.05f;

	constexpr float kAnimationSize = 3.0f;

	//一度に登場できる敵の最大数
	constexpr int kEnemyMax = 32;

	//ダメージの無敵時間
	constexpr int kDamageFrame = 50; //2秒

	//１層の地面の高さ
	constexpr int kGroundH01 = 1880;
	//２層の地面の高さ
	constexpr int kGroundH02 = 1200;
	//３層の地面の高さ
	constexpr int kGroundH03 = 600;

	constexpr int kMapWidth = 3840;
	constexpr int kMapHeight = 1920;

}

GamePlayingScene::GamePlayingScene(SceneManager& manager) :Scene(manager)
{
	/* グラフィックをロード */

	//敵のグラフィックをロード
	m_enemyRunHandle = LoadGraph("date/image/EnemyRun.png");
	assert(m_enemyRunHandle >= 0);
	m_enemyJumpHandle = LoadGraph("date/image/EnemyJump.png");
	assert(m_enemyJumpHandle >= 0);
	m_enemyJumpRunHandle = LoadGraph("date/image/EnemyJumpRun.png");
	assert(m_enemyJumpRunHandle >= 0);

	//マップチップのグラフィックをロード
	m_map01Handle = LoadGraph("date/image/MapChip001.png");
	assert(m_map01Handle >= 0);
	m_map02Handle = LoadGraph("date/image/MapChip002.png");
	assert(m_map02Handle >= 0);

	//アイテムのグラフィックをロード
	m_itemHandleHp = LoadGraph("date/image/Item02.png");
	assert(m_itemHandleHp >= 0);
	m_itemHandleBigHp = LoadGraph("date/image/Item01.png");
	assert(m_itemHandleBigHp >= 0);

	//ゴールのグラフィックをロード
	m_goalHandle = LoadGraph("date/image/Goal.png");
	assert(m_goalHandle >= 0);

	m_handle = LoadGraph("date/image/Bg004.png");


	//BGMをロード
	m_bgmHandle = LoadSoundMem("date/sound/bgm/GamePlayBgm.mp3");

	//SEロード
	m_seHandle001 = LoadSoundMem("date/sound/se/damageSe.wav");	  //ダメージ音
	m_seHandle002 = LoadSoundMem("date/sound/se/damageSe02.wav"); //ダメージ音２
	m_seHandle003 = LoadSoundMem("date/sound/se/itemSe.wav"); //アイテム音
	m_seHandle004 = LoadSoundMem("date/sound/se/goalSe.wav"); //ゴール音
	m_seHandle005 = LoadSoundMem("date/sound/se/cliffFallSe.wav"); //崖から落ちた音
	


	//BGMを流す
	PlaySoundMem(m_bgmHandle, DX_PLAYTYPE_LOOP);

	pPlayer = std::make_shared<Player>();
	
	//pEnemy = std::make_shared<EnemyBase>();
	RT_ = MakeScreen(Game::kScreenWidth, Game::kScreenHeight);

	//敵の数
	pEnemy.resize(68);


	//初期コース
	CreateEnemyRun(1850, kGroundH01);
	CreateEnemyRun(1600, kGroundH01);
	CreateEnemyRun(1200, kGroundH01);
	CreateEnemyRun(300, kGroundH01);

	//落ちたら死ぬコース
	CreateEnemyRun(2100, 1700);
	CreateEnemyRun(2330, 1700);
	CreateEnemyRun(2500, 1700);
	//CreateEnemyRun(2700, 1700);
	CreateEnemyRun(3200, 1700);
	CreateEnemyRun(3350, 1700);
	CreateEnemyRun(3550, 1700);

	//二層目の最初コース
	CreateEnemyJump(2100, kGroundH02);
	CreateEnemyJump(2330, kGroundH02);
	CreateEnemyJump(2500, kGroundH02);
	CreateEnemyJump(2700, kGroundH02);
	CreateEnemyJump(2900, kGroundH02);
	CreateEnemyJump(3120, kGroundH02);
	CreateEnemyJump(3340, kGroundH02);
	CreateEnemyJump(3570, kGroundH02);

	//三層目最初
	CreateEnemyJump(2330, kGroundH03);
	CreateEnemyJump(2074, kGroundH03);
	CreateEnemyJump(1818, kGroundH03);
	CreateEnemyJump(1562, kGroundH03);
	CreateEnemyJump(1350, kGroundH03);

	//ゴール前
	CreateEnemyRun(2900, kGroundH03);
	CreateEnemyJump(3000, kGroundH03);
	CreateEnemyRun(3100, kGroundH03);
	CreateEnemyJump(3200, kGroundH03);
	CreateEnemyRun(3300, kGroundH03);
	CreateEnemyJump(3400, kGroundH03);
	CreateEnemyRun(3500, kGroundH03);
	CreateEnemyJump(3600, kGroundH03);
	CreateEnemyRun(3700, kGroundH03);
	CreateEnemyRun(3800, kGroundH03);

	CreateEnemyJumpRun(2900, kGroundH03);
	CreateEnemyJumpRun(3000, kGroundH03);
	CreateEnemyJumpRun(3100, kGroundH03);
	CreateEnemyJumpRun(3200, kGroundH03);

	CreateEnemyRun(1600, kGroundH03);
	CreateEnemyRun(1400, kGroundH03);

	//蛇コースの敵
	CreateEnemyRun(500, 750);
	CreateEnemyRun(600, 850);
	CreateEnemyRun(900, 950);
	CreateEnemyRun(700, 1100);
	CreateEnemyRun(500,kGroundH02);

	//パタパタ敵を生成
	CreateEnemyJumpRun(1200, kGroundH03);
	CreateEnemyJumpRun(1000, kGroundH03);
	CreateEnemyJumpRun(800, kGroundH03);

	pItem.resize(20);

	CreateItemHp(1345, 1400);
	CreateItemHp(1800, 1400);
	CreateItemHp(1000, kGroundH03 - 96);
	CreateItemHp(600, kGroundH01 - 100);
	CreateItemHp(300, kGroundH02 + 30);


	CreateItemBigHp(3780, 750);
	CreateItemBigHp(3780, 750);
	CreateItemBigHp(3780, 750);
	
	CreateItemBigHp(1000, 50);
	CreateItemBigHp(1000, 50);
	CreateItemBigHp(1000, 50);

	CreateItemBigHp(3670, kGroundH01 - 200);
	CreateItemBigHp(3670, kGroundH01 - 200);
	CreateItemBigHp(3670, kGroundH01 - 200);



	pMap = std::make_shared<Map>();
	pMap->SetHandle(m_map01Handle);
	pMap->SetHandle02(m_map02Handle);

	pGoal = std::make_shared<Goal>();
	pGoal->SetHandle(m_goalHandle);

	//マップの情報を参照できるようポインタを渡す
	pPlayer->SetMap(pMap);
	for (int i = 0; i < pEnemy.size(); i++)
	{
		if (pEnemy[i])
		{
			pEnemy[i]->SetMap(pMap);
		}
	}
	//pEnemy->SetMap(pMap);
	pGoal->SetMap(pMap);

	for (int i = 0; i < pItem.size(); i++)
	{
		if (pItem[i])
		{
			pItem[i]->SetMap(pMap);
		}
	}

	//プレイヤーの情報を参照できるようポインタを渡す
	pMap->SetPlayer(pPlayer);

	m_frame = 60;
	updateFunc_ = &GamePlayingScene::FadeInUpdate;
	drawFunc_ = &GamePlayingScene::FadeDraw;
}

GamePlayingScene::~GamePlayingScene()
{
	DeleteGraph(m_handle);
	DeleteGraph(m_enemyRunHandle);
	DeleteGraph(m_map01Handle);
	DeleteGraph(m_map02Handle);
	DeleteGraph(m_itemHandleHp);
	DeleteGraph(m_itemHandleBigHp);
	DeleteGraph(m_goalHandle);
	DeleteGraph(m_tutorial001Handle);

	//BGMを削除
	DeleteSoundMem(m_bgmHandle);

	//SE削除
	DeleteSoundMem(m_seHandle001);
	DeleteSoundMem(m_seHandle002);
	DeleteSoundMem(m_seHandle003);
	DeleteSoundMem(m_seHandle004);
	DeleteSoundMem(m_seHandle005);
}

void GamePlayingScene::FadeInUpdate(Input&)
{
	ChangeVolumeSoundMem(128, m_bgmHandle);
	ChangeVolumeSoundMem(128, m_seHandle001);
	ChangeVolumeSoundMem(128, m_seHandle002);
	ChangeVolumeSoundMem(128, m_seHandle003);
	ChangeVolumeSoundMem(128, m_seHandle004);
	ChangeVolumeSoundMem(128, m_seHandle005);


	m_frame--;
	if (m_frame <= 0) {
		updateFunc_ = &GamePlayingScene::NormalUpdate;
		drawFunc_ = &GamePlayingScene::NormalDraw;
	}
}

void GamePlayingScene::NormalUpdate(Input&)
{
	m_isGoalHit = pGoal->GetHitPlayerFlag(pPlayer);

	ChangeVolumeSoundMem(128, m_bgmHandle);
	ChangeVolumeSoundMem(128, m_seHandle001);
	ChangeVolumeSoundMem(128, m_seHandle002);
	ChangeVolumeSoundMem(128, m_seHandle003);
	ChangeVolumeSoundMem(128, m_seHandle004);
	ChangeVolumeSoundMem(128, m_seHandle005);

	//プレイヤーがY座標の上限に達したら
	if (pPlayer->GetY() > kFallMax)
	{
		m_shakeFrame = 60;
		m_amp = 15;
		m_hp -= 1;
		PlaySoundMem(m_seHandle002, DX_PLAYTYPE_BACK, true);//ダメージ音２
		StartJoypadVibration(DX_INPUT_PAD1, 800, 500, -1);

		pPlayer->FallRestart();

		if (m_hp <= 0)
		{
			m_isGameOverFade = true;
			updateFunc_ = &GamePlayingScene::FadeOutUpdateGameOver;
			drawFunc_ = &GamePlayingScene::FadeDraw;
			m_frame = 0;
			pPlayer->CommandOff();
			StopSoundMem(m_bgmHandle);
			PlaySoundMem(m_seHandle005, DX_PLAYTYPE_BACK, true);
		}
	}

	if (m_shakeFrame > 0)
	{
		m_shakeFrame--;
		m_shakeVec.x = m_amp * GetRand(2) - 1;
		m_shakeVec.y = m_amp * GetRand(2) - 1;
		m_amp *= 0.95f;
	}
	else
	{
		m_shakeVec = {};
	}

	//当たり判定の無敵時間
	if (m_isDamage)
	{
		m_damageFrame++;
		if (m_damageFrame > kDamageFrame)
		{
			m_isDamage = false;
			m_damageFrame = 0;
		}
	}
	

	//ゴールバーに当たったら
	if (m_isGoalHit) {
		PlaySoundMem(m_seHandle004, DX_PLAYTYPE_BACK, true);//ゴール音
		StopSoundMem(m_bgmHandle);
		updateFunc_ = &GamePlayingScene::FadeOutUpdateGameClear;
		drawFunc_ = &GamePlayingScene::FadeDraw;
		pPlayer->CommandOff();
		m_frame = 0;
		m_isGoalFade = true;
		m_isGoalHit = true;
	}
}

void GamePlayingScene::FadeOutUpdateGameOver(Input&)
{

	m_frame++;
	if (m_frame >= 180)
	{
		manager_.ChangeScene(new GameOverScene(manager_));//ゲームオーバーシーンに移行する
	}
	
}

void GamePlayingScene::FadeOutUpdateGameClear(Input&)
{
	m_frame++;
	m_isGoalHit = pGoal->GetHitPlayerFlag(pPlayer);
	if (m_frame >= 60)
	{
		if (m_isGoalHit)
		{
			//ゲームクリアシーンに移行する
			manager_.ChangeScene(new GameClearScene(manager_));
		}
	}
}

void GamePlayingScene::FadeDraw()
{
	//背景
	int scrollX = GetScrollX();
	int scrollY = GetScrollY();

	int posX = -scrollX;
	int posY = -scrollY;

	DrawGraph(posX, posY, m_handle, false);


	pPlayer->Draw();
	for (int i = 0; i < pEnemy.size(); i++)
	{
		if (pEnemy[i])
		{
			pEnemy[i]->Draw();
		}
	}

	for (int i = 0; i < pItem.size(); i++)
	{
		if (pItem[i])
		{
			pItem[i]->Draw();
		}
	}

	pGoal->Draw();
	pMap->Draw();


	for (int i = 1; i <= m_hp; i++)
	{
		DrawExtendGraph(40 * i, 16 + m_animationHeight, 40 * i + 32, 48 , m_itemHandleHp, true);
	}

	//フェード暗幕
	if (m_isGameOverFade)
	{
		int alpha = 255 * (float)m_frame / 180.0f;
		SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
		DrawBox(0, 0, 1280, 720, 0x000000, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	if (m_isGoalFade)
	{
		int alpha = 255 * (float)m_frame / 60.0f;
		SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
		DrawBox(0, 0, 1280, 720, 0x000000, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

void GamePlayingScene::NormalDraw()
{
}

void GamePlayingScene::CreateEnemyRun(float x, float y)
{
	for (int i = 0; i < pEnemy.size(); i++)
	{
		if (!pEnemy[i])
		{
			pEnemy[i] = new EnemyRun;
			pEnemy[i]->Start(x, y);
			pEnemy[i]->SetHandle(m_enemyRunHandle);
			return;
		}
	}
}

void GamePlayingScene::CreateEnemyJump(float x , float y)
{
	for (int i = 0; i < pEnemy.size(); i++)
	{
		if (!pEnemy[i])
		{
			pEnemy[i] = new EnemyJump;
			pEnemy[i]->Start(x, y);
			pEnemy[i]->SetHandle(m_enemyJumpHandle);
			return;
		}
	}
}

void GamePlayingScene::CreateEnemyJumpRun(float x, float y)
{
	for (int i = 0; i < pEnemy.size(); i++)
	{
		if (!pEnemy[i])
		{
			pEnemy[i] = new EnemyJumpRun;
			pEnemy[i]->Start(x, y);
			pEnemy[i]->SetHandle(m_enemyJumpRunHandle);
			return;
		}
	}
}

void GamePlayingScene::CreateItemHp(float x, float y)
{
	for (int i = 0; i < pItem.size(); i++)
	{
		if (!pItem[i])
		{
			pItem[i] = new ItemHp;
			pItem[i]->Start(x, y);
			pItem[i]->SetHandle(m_itemHandleHp);
			return;
		}
	}
}

void GamePlayingScene::CreateItemBigHp(float x, float y)
{
	for (int i = 0; i < pItem.size(); i++)
	{
		if (!pItem[i])
		{
			pItem[i] = new ItemBigHp;
			pItem[i]->Start(x, y);
			pItem[i]->SetHandle(m_itemHandleBigHp);
			return;
		}
	}
}



void GamePlayingScene::Init()
{
	


}

void GamePlayingScene::Update(Input& input)
{
	ChangeVolumeSoundMem(128, m_bgmHandle);
	ChangeVolumeSoundMem(128, m_seHandle001);
	ChangeVolumeSoundMem(128, m_seHandle002);
	ChangeVolumeSoundMem(128, m_seHandle003);
	ChangeVolumeSoundMem(128, m_seHandle004);
	ChangeVolumeSoundMem(128, m_seHandle005);

	// 左右キーで背景移動
	bool isBgFlag = false;

	static float SinCount = 0;
	SinCount += kSinSpeed;
	m_animationHeight = sinf(SinCount) * kAnimationSize;
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);


	//左に背景がスクロールする
	if (pad & PAD_INPUT_LEFT)
	{
		m_areaX -= kBgSpeed;

		if (m_areaX < 0)
		{
			m_areaX = Game::kScreenWidth;
		}
	}
	//右に背景がスクロールする
	if (pad & PAD_INPUT_RIGHT)
	{
		m_areaX += kBgSpeed;
		if (m_areaX > Game::kScreenWidth)
		{
			m_areaX = 0;
		}
	}

	pPlayer->Update();
	for (int i = 0; i < pEnemy.size(); i++)
	{
		if (pEnemy[i])
		{
			pEnemy[i]->Update();

			//プレイヤーと敵が当たった場合
			if (!m_isDamage)
			{
				m_isPlayerHit = pEnemy[i]->GetHitPlayerFlag(pPlayer);

				if (!m_isGoalHit)
				{
					if (m_isPlayerHit)
					{
						StartJoypadVibration(DX_INPUT_PAD1, 500, 200, -1);
						PlaySoundMem(m_seHandle002, DX_PLAYTYPE_BACK, true);//ダメージ音

						m_isDamage = true;

						pPlayer->Damage();
						m_hp = m_hp - 1;

						m_shakeFrame = 30;
						m_amp = 15;

						delete pEnemy[i];
						pEnemy[i] = nullptr;

						if (m_hp <= 0)
						{
							PlaySoundMem(m_seHandle005, DX_PLAYTYPE_BACK, true);
							StopSoundMem(m_bgmHandle);
							updateFunc_ = &GamePlayingScene::FadeOutUpdateGameOver;
							drawFunc_ = &GamePlayingScene::FadeDraw;
							m_frame = 0;
							pPlayer->CommandOff();
							m_isGameOverFade = true;
						}
					}
				}
			}
		}
	}

	if (m_shakeFrame > 0)
	{
		m_shakeFrame--;
		m_shakeVec.x = m_amp * GetRand(2) - 1;
		m_shakeVec.y = m_amp * GetRand(2) - 1;
		m_amp *= 0.95f;
	}
	else
	{
		m_shakeVec = {};
	}

	pMap->Update();
	pGoal->Update();

	for (int i = 0; i < pItem.size(); i++)
	{
		if (pItem[i])
		{
			pItem[i]->Update();

				//アイテムに当たったら
				if (pItem[i]->GetHitPlayerFlag(pPlayer)) {
					m_hp += 1;
					PlaySoundMem(m_seHandle003, DX_PLAYTYPE_BACK, true);//アイテム音
					pItem[i]->ItemLost();

					delete pItem[i];
					pItem[i] = nullptr;
				}
		}
	}
	

	

	(this->*updateFunc_)(input);
}

void GamePlayingScene::Draw()
{
	int scrollX = GetScrollX();
	int scrollY = GetScrollY();

	int posX = -scrollX;
	int posY = -scrollY;

	SetDrawScreen(RT_);
	//背景
	//BackScroll(m_areaX, m_handle, Game::kScreenWidth, Game::kScreenHeight);
	DrawGraph(posX, posY, m_handle, false);




	pPlayer->Draw();
	for (int i = 0; i < pEnemy.size(); i++)
	{
		if (pEnemy[i])
		{
			pEnemy[i]->Draw();
		}
	}

	for (int i = 0; i < pItem.size(); i++)
	{
		if (pItem[i])
		{
			pItem[i]->Draw();
		}
	}

	pMap->Draw();
	pGoal->Draw();

	for (int i = 1; i <= m_hp; i++)
	{
		DrawExtendGraph(40 * i, 16 + m_animationHeight, 40 * i + 32, 48 , m_itemHandleHp, true);
	}

	(this->*drawFunc_)();
	SetDrawScreen(DX_SCREEN_BACK);
	DrawGraph(m_shakeVec.x, m_shakeVec.y, RT_, false);

}

void GamePlayingScene::BackScroll(const int areaX, const int handle, const int width, const int height)
{
	//最初に画面に表示される背景
	DrawRectGraph(0, 0, 0, 0, width, height, handle, false);
	//スクロールした分、画面に表示される背景
	DrawRectGraph(width - areaX, 0, 0, 0, areaX, height, handle, false);
}

int GamePlayingScene::GetScrollX()
{
	int result = static_cast<int>(pPlayer->GetX() - Game::kScreenWidth * 0.5);
	result = max(0, result);	//最小値
	result = min(kMapWidth - Game::kScreenWidth, result);	//最大値
	return result;
}

int GamePlayingScene::GetScrollY()
{
	int result = static_cast<int>(pPlayer->GetY() - Game::kScreenHeight * 0.5);
	if (result < 0)
	{
		result = 0;
	}
	if (result > kMapHeight - Game::kScreenHeight)
	{
		result = kMapHeight - Game::kScreenHeight;
	}
	return result;
}