#include "Map.h"

#include "Handle.h"

// プレイヤー
#include "Player.h"
#include "PlayerLight.h"

// ギミック
#include "Wall.h"
#include "InColorFloor.h"
#include "OutColorFloor.h"
#include "DirWall.h"
#include "GoalPoint.h"

// エフェクト
#include "EfectColor.h"

// サウンド
#include "Sound.h"

// BG
#include "GameBg.h"

// ファイルデータ
#include "FileQuickTime.h"

// プレイヤーカラーのBg
#include "pColorBg.h"

#include <cassert>

Map::Map() :
	m_wallCount(0),
	m_inColorCount(0),
	m_outColorCount(0),
	m_dirWallCount(0),
	m_paintCount(0),
	m_isClear(false),
	m_alpha(255),
	m_isTransScene(false),
	m_timeAttack(false),
	m_timer(0),
	m_clearBgColor(0x1f152d),
	m_mapNum(0),
	m_isUpdateTime(false),
	m_mode(0),
	m_stringTimer(0),
	m_clearWindowTimer(0),
	m_clearWindowY(0),
	m_BGM(0),
	m_SE(0),
	m_isReset(false)
{
	for (int i = 0; i < kChipNumY; i++)
	{
		for (int j = 0; j < kChipNumX; j++)
		{
			chipData[i][j] = 0;
		}
	}
	m_pPlayer = new Player;
	m_pLight = new PlayerLight;
	m_pGoal = new GoalPoint;
	
	// サウンド
	m_pSound.resize(9);
	for (int i = 0; i < m_pSound.size(); i++)
	{
		m_pSound[i] = new Sound;
	}

	

	m_clearPos = { Game::kScreenWidth,Game::kScreenHeight * 0.5f };

	// ファイルデータ
	m_pData = new FileQuickTime;

	m_pColorBg = new pColorBg;
}

Map::~Map()
{
	if(!m_isReset)
		m_pSound[0]->Stop();

	delete m_pPlayer;
	m_pPlayer = nullptr;
	delete m_pLight;
	m_pLight = nullptr;
	for (int i = 0; i < m_wallCount; i++)
	{
		delete m_pWall[i];
		m_pWall[i] = nullptr;
	}
	for (int i = 0; i < m_inColorCount; i++)
	{
		delete m_pInColor[i];
		m_pInColor[i] = nullptr;
	}
	for (int i = 0; i < m_outColorCount; i++)
	{
		delete m_pOutColor[i];
		m_pOutColor[i] = nullptr;
		delete m_pEfect[i];
		m_pEfect[i] = nullptr;
	}
	for (int i = 0; i < m_dirWallCount; i++)
	{
		delete m_pDirWall[i];
		m_pDirWall[i] = nullptr;
	}
	delete m_pGoal;
	m_pGoal = nullptr;

	
	for (int i = 0; i < m_pSound.size(); i++)
	{
		delete m_pSound[i];
		m_pSound[i] = nullptr;
	}

	for (int i = 0; i < m_pBg.size(); i++)
	{
		delete m_pBg[i];
		m_pBg[i] = nullptr;
	}
	delete m_pData;
	m_pData = nullptr;

	delete m_pColorBg;
	m_pColorBg = nullptr;
}

void Map::Init(int mode, int mapNum, int BGM, int SE, const Handle& handle)
{
	m_mode = mode;
	m_mapNum = mapNum;
	m_BGM = BGM;
	m_SE = SE;
	for (int y = 0; y < kChipNumY; y++)
	{
		for (int x = 0; x < kChipNumX; x++)
		{
			// マップ情報読み取り
				chipData[y][x] = MapData::SetMap(mapNum, y, x);


			// 使用分の各ギミック確保

			/////////////
			// １ = 壁 //
			/////////////
			if (chipData[y][x] == 1)
			{
				// 要素数の更新(現在個数に＋１)
				m_pWall.resize(m_wallCount + 1);
				// 更新で追加された要素番号を初期化
				m_pWall[m_wallCount] = new Wall;
				m_pWall[m_wallCount]->Init(x, y);
				// 最後に現在個数の更新
				m_wallCount++;
			}

			/////////////////////
			// ２ = プレイヤー //
			/////////////////////
			if (chipData[y][x] == 2)
			{
				m_pPlayer->Init(static_cast<float>(x), static_cast<float>(y));
			}

			///////////////////
			// ３ = 色変更床 //
			///////////////////
			if(chipData[y][x] >= 30 && chipData[y][x] < 40)
			{
				// 要素数の更新(現在個数に＋１)
				m_pInColor.resize(m_inColorCount + 1);
				// 更新で追加された要素番号を初期化
				m_pInColor[m_inColorCount] = new InColorFloor;
				// 色指定
				auto setColor = 0xffffff;
				switch (chipData[y][x] - 30)
				{
				case 0: // 赤
					setColor = 0xff69b4;
					break;
				case 1: // 緑
					setColor = 0x39ff14;
					break;
				case 2: // 青
					setColor = 0x00aeef;
					break;
				case 3: // 黄
					setColor = 0xffd300;
					break;
				default: // 白
					setColor = 0xffffff;
					break;
				}
				m_pInColor[m_inColorCount]->Init(x, y, setColor);
				// 最後に現在個数の更新
				m_inColorCount++;
			}

			/////////////////
			// ４ = 着色床 //
			/////////////////
			if (chipData[y][x] >= 40 && chipData[y][x] < 50)
			{
				// 要素数の更新(現在個数に＋１)
				m_pOutColor.resize(m_outColorCount + 1);
				m_pEfect.resize(m_outColorCount + 1);
				// 更新で追加された要素番号を初期化
				m_pOutColor[m_outColorCount] = new OutColorFloor;
				m_pEfect[m_outColorCount] = new EfectColor;
				// 色指定
				auto setColor = 0xffffff;
				switch (chipData[y][x] - 40)
				{
				case 0:
					setColor = 0xff69b4;
					break;
				case 1:
					setColor = 0x39ff14;
					break;
				case 2:
					setColor = 0x00aeef;
					break;
				case 3:
					setColor = 0xffd300;
					break;
				default:
					setColor = 0xffffff;
					break;
				}
				m_pOutColor[m_outColorCount]->Init(x, y, setColor);

				// Bgの数指定
				m_pBg.resize(m_outColorCount + 1);
				m_pBg[m_outColorCount] = new GameBg;
				m_pBg[m_outColorCount]->Init(m_outColorCount,setColor);

				// 最後に現在個数の更新
				m_outColorCount++;
			}

			/////////////////
			// ５ = 一方壁 //
			/////////////////

				/*任意の方向分けの方法*/
			// ①構造体を使った方向分け（能力アピならこっち）
			// ②チップデータとして４つ作ってしまう（手っ取り早く作るならこっち）
			if (chipData[y][x] >= 50 && chipData[y][x] < 60)
			{
				// 要素数の更新(現在個数に＋１)
				m_pDirWall.resize(m_dirWallCount + 1);
				// 更新で追加された要素番号を初期化
				m_pDirWall[m_dirWallCount] = new DirWall;
				// 方向指定
				int setDir = 0;
				switch (chipData[y][x] - 50)
				{
				case 0:
					setDir = 0;
					break;
				case 1:
					setDir = 1;
					break;
				case 2:
					setDir = 2;
					break;
				default:
					setDir = 3;
					break;
				}
				m_pDirWall[m_dirWallCount]->Init(x, y, setDir);
				// 最後に現在個数の更新
				m_dirWallCount++;
			}

			/////////////////
			// ６ = ゴール //
			/////////////////
			if (chipData[y][x] == 6)
			{
				m_pGoal->Init(x,y);
			}
		}
	}
	// プレイヤーのオーラ光
	m_pLight->Init(m_pPlayer->GetPos());


	// ゲームBGM
	m_pSound[0]->InitBGM(handle.h_data.hm_B_1);
	// 壁ヒット音
	m_pSound[1]->InitSE(handle.h_data.hm_S_04);
	// 色変更音
	m_pSound[2]->InitSE(handle.h_data.hm_S_05);
	// 着色音
	m_pSound[3]->InitSE(handle.h_data.hm_S_06);
	// 全塗り音
	m_pSound[4]->InitSE(handle.h_data.hm_S_07);
	// ポーズ音
	m_pSound[5]->InitSE(handle.h_data.hm_S_01);
	// ゴール音
	m_pSound[6]->InitSE(handle.h_data.hm_S_08);
	// 記録更新音
	m_pSound[7]->InitSE(handle.h_data.hm_S_09);
	// リセット音
	m_pSound[8]->InitSE(handle.h_data.hm_S_10);

	// 音量更新
	for (int i = 0; i < m_pSound.size(); i++)
	{
		if (i == 0) m_pSound[i]->UpdateBGM(BGM);
		else m_pSound[i]->UpdateSE(SE);
	}

	if(!m_pSound[0]->ChackPlaying())
		m_pSound[0]->LoopPlay();
}

void Map::Update(bool isPause)
{
	if (!isPause)
	{
		/////////////////////////////
		// 一方壁の衝突判定 衝突前 //
		/////////////////////////////
		for (int i = 0; i < m_dirWallCount; i++)
		{
			Rect player = m_pPlayer->GetColRect();
			m_pDirWall[i]->Update(player);				// プレイヤー側で衝突判定
		}

		// プレイヤー
		m_pPlayer->Update();

		//////////////////
		// 壁の衝突判定 //
		//////////////////
		for (int i = 0; i < m_wallCount; i++)
		{
			Rect wallRect = m_pWall[i]->GetRect();				// 壁の当たり判定獲得
			m_pPlayer->WallHit(wallRect);						// プレイヤー側で衝突判定
			if (m_pPlayer->GetHitFlag() && !m_pPlayer->GetGoal())
			{
				m_pSound[1]->OnePlay();
				m_pSound[1]->OnePlay();
				m_pSound[1]->OnePlay();
				m_pSound[1]->OnePlay();
			}
		}

		/////////////////////////
		// 壁の衝突判定 衝突後 //
		/////////////////////////
		for (int i = 0; i < m_dirWallCount; i++)
		{
			Rect dirWallRect = m_pDirWall[i]->GetRect();				// dir壁の当たり判定獲得
			bool dirPass = m_pDirWall[i]->GetPass();
			m_pPlayer->DirWallHit(dirWallRect, dirPass);						// プレイヤー側で衝突判定
			if (m_pPlayer->GetHitFlag() && !m_pPlayer->GetGoal())
			{
				m_pSound[1]->OnePlay();
				m_pSound[1]->OnePlay();
				m_pSound[1]->OnePlay();
				m_pSound[1]->OnePlay();
			}
		}

		// 衝突処理後にプレイヤー光のUpdateを行うことでブレをなくす
		m_pLight->Update(m_pPlayer->GetPos());


		////////////////////////////////
		// 色変更床による光の変更判定 //
		////////////////////////////////
		for (int i = 0; i < m_inColorCount; i++)
		{
			m_pInColor[i]->Update();
			Rect inColorRect = m_pInColor[i]->GetRect();		// 色変更床の当たり判定獲得
			int pcolor = m_pLight->GetColor();
			int setcolor = m_pInColor[i]->GetColor();			// 色変更床の色を獲得
			if (pcolor != setcolor && inColorRect.IsPointInRect(m_pLight->GetPos()) != 0 && !m_pPlayer->GetGoal())
			{
				m_pSound[2]->OnePlay();
				m_pLight->InColorEffect();
			}
			m_pLight->ColorFloorHit(inColorRect, setcolor);		// プレイヤー光で色を付与
		}

		//////////////////////////////
		// プレイヤーが色を付与する //
		//////////////////////////////
		for (int i = 0; i < m_outColorCount; i++)
		{
			Rect outColorRect = m_pOutColor[i]->GetRect();		// 着色床の当たり判定獲得
			Rect lightColorRect = m_pLight->GetRect();			// プレイヤー光の当たり判定獲得
			if (outColorRect.IsCollsion(lightColorRect))		// 衝突判定
			{
				int targetColor = m_pOutColor[i]->GetColor();	// 着色床の色を獲得
				int lightColor = m_pLight->GetColor();			// プレイヤー光の色を獲得
				// 色を比較し、同色なら着色
				if (targetColor == lightColor)
				{
					// 同色かつ、チェック前のboolを受け取っておくことで、１回だけカウントされる
					bool isChack = m_pOutColor[i]->GetChack();
					m_pOutColor[i]->Update();

					if (!isChack)
					{
						m_pSound[3]->OnePlay();
						m_pEfect[i]->Init(m_pOutColor[i]->GetPos(), targetColor);
						// ゴール条件のカウント更新
						m_pBg[i]->SetFlag(true);
						m_paintCount++;
						if (m_paintCount >= m_outColorCount) m_pSound[4]->OnePlay();
					}
				}
			}
			if (m_paintCount >= m_outColorCount)
			{
				m_pEfect[i]->ClearChack(i, m_pGoal->GetPos());
			}
			// エフェクトアップデート
			m_pEfect[i]->Update();
		}
		//////////////////////
		// ゴール地点の発生 //
		//////////////////////
		if (m_paintCount >= m_outColorCount)
		{
			m_isClear = true;
		}
		else m_isClear = false;
		m_pGoal->Update(m_isClear);

		// ゴール到着で光を虹色に光らせる
		Rect goalRect = m_pGoal->GetRect();
		int goalColor = m_pGoal->GetColor();
		m_pLight->ClearHit(goalRect);

		////////////
		// ゴール //
		////////////
		if (m_isClear && !m_isReset)
		{
			m_pPlayer->GoalIn(goalRect);
			// 背景を明るく
			if (m_clearBgColor < 0x600060) m_clearBgColor += (256 * 256 * 3 + 3);
		}
		//////////////
		// ゴール後 //
		//////////////
		if (m_pPlayer->GetGoal() && !m_isReset)
		{
			
			// 最短回数のファイル更新
			if (m_alpha == 0)
			{
				m_pSound[6]->OnePlay();
				m_pSound[6]->OnePlay();
				if (m_pData->GetTime(m_mapNum) >= m_timer)
				{
					m_isUpdateTime = true;
					m_pData->ChangeTime(m_mapNum, m_timer);
					m_pSound[7]->OnePlay();
				}
				m_alpha = 3;
			}

			// シーン遷移までのフェードアウト処理
			if (!m_pSound[7]->ChackPlaying() && m_clearWindowTimer > 50)
			{
				if (m_alpha < 255)
				{
					m_alpha += 3;
				}
				else
				{
					m_pSound[0]->Stop();
					m_isTransScene = true;
				}
			}

			// 文字列点滅のタイマー
			if (m_stringTimer < 120)
			{
				m_stringTimer += 12;
			}
			else
			{
				m_stringTimer = 0;
			}

			// ゴール表記
			// ウインドウを開く
			if (m_clearPos.x >= 0 && m_clearWindowY < 20)
			{
				m_clearWindowY++;
			}
			// クリア位置を流す
			else if(m_clearWindowTimer == 0 || m_clearWindowTimer >= 50)
			{
				m_clearPos.x -= 30;
			}

			// ウインドウを閉じる
			if (m_clearPos.x < 0 && m_clearWindowY > 0)
			{
				m_clearWindowY--;
			}

			// クリア表記の停止時間
			if (m_clearPos.x < Game::kScreenWidth * 0.5f - 100)
			{
				if(m_clearWindowTimer < 80)
					m_clearWindowTimer++;
			}

		}
		else if(!m_isReset)
		{
			// 初期フェードイン
			if (m_alpha > 0)
			{
				m_alpha -= 5;
			}
			else
			{
				m_alpha = 0;
			}
		}

		int pad = GetJoypadInputState(DX_INPUT_PAD1);
		int hitZ = CheckHitKey(KEY_INPUT_Z);

		if ((hitZ || pad == PAD_INPUT_3) && !m_pPlayer->GetGoal() && m_mode == 1 && !m_isReset)
		{
			m_pSound[8]->OnePlay();
			m_pSound[8]->OnePlay();
			m_pSound[8]->OnePlay();
			m_isReset = true;
			
		}

		if (m_isReset)
		{
			if (m_alpha < 255)
			{
				m_alpha += 5;
			}
			else
			{
				m_alpha = 255;
				Reset();
			}
		}


		// 回数の更新
		m_timer = m_pPlayer->GetMoveTime();

		for (int i = 0; i < m_pBg.size(); i++)
		{
			// 背景へのクリア可能フラグ受け渡し
			m_pBg[i]->Update();
		}
		m_pColorBg->Update(m_pLight->GetColor());

		
	}
	m_pColorBg->SetisDontMove(isPause);
}

void Map::Draw(const Handle& handle)
{
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, m_clearBgColor, true);

	// エフェクト描写
	for (int i = 0; i < m_outColorCount; i++)
	{
		m_pEfect[i]->Draw();
	}
	// 酔い防止の黒画面
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 70);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);

	for (int i = 0; i < m_pBg.size(); i++)
	{
		m_pBg[i]->Draw();
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	m_pColorBg->Draw();
	// 酔い防止の黒画面m 
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 75);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	

	// ギミック関連
	// 壁
	for (int i = 0; i < m_wallCount; i++)
	{
		m_pWall[i]->Draw(handle);
	}
	// 色変更床
	for (int i = 0; i < m_inColorCount; i++)
	{
		m_pInColor[i]->Draw(handle);
	}
	// 色床描写
	for (int i = 0; i < m_outColorCount; i++)
	{
		m_pOutColor[i]->Draw(handle);
	}
	// 一方通行壁
	for (int i = 0; i < m_dirWallCount; i++)
	{
		m_pDirWall[i]->Draw(handle);
	}
	// ゴール
	m_pGoal->Draw();

	// ゴール時エフェクト
	if (m_pPlayer->GetGoal())
	{
		m_pGoal->GoalEffect();
	}

	// プレイヤー関連
	// 光
	m_pLight->Draw();
	// プレイヤー
	m_pPlayer->Draw();

	// エフェクト描写
	if (m_isClear)
	{
		for (int i = 0; i < m_outColorCount; i++)
		{
			m_pEfect[i]->Draw();
		}
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180); 
	 
	// 回数スコアウインドウ
	DrawExtendGraph(static_cast<int>(Game::kScreenWidth * 0.75f),-25,
		static_cast<int>(Game::kScreenWidth), 250,
		handle.h_data.hi_countWindow, true);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	if (m_isUpdateTime && m_stringTimer > 60)
	{
		DrawStringToHandle(static_cast<int>(Game::kScreenWidth * 0.84f), 50, "Fastest !!!!", 0xffd300,handle.h_data.hf_starry_20);
		DrawFormatStringToHandle(static_cast<int>(Game::kScreenWidth * 0.82f), 160, 0xffd300, handle.h_data.hf_util_20, " 最短回数：%d ", m_pData->GetTime(m_mapNum));
	}
	else
	{
		if (m_isUpdateTime)
			DrawStringToHandle(static_cast<int>(Game::kScreenWidth * 0.84f), 50, "Fastest !!!!", 0xff4e4e, handle.h_data.hf_starry_20);

		DrawFormatStringToHandle(static_cast<int>(Game::kScreenWidth * 0.82f), 160, 0xff4e4e,handle.h_data.hf_util_20, " 最短回数：%d ", m_pData->GetTime(m_mapNum));
	}

	// 色床エフェクト
	for (int i = 0; i < m_outColorCount; i++)
	{
		m_pOutColor[i]->Effect();
	}

	// 色変更床エフェクト
	for (int i = 0; i < m_inColorCount; i++)
	{
		m_pInColor[i]->colorEffect();
	}

	// ゴールエフェクト
	m_pGoal->Effect();

	// プレイヤー現在地エフェクト
	m_pLight->ColorEffect();

	if (m_pPlayer->GetGoal())
	{
		GoalDraw(handle);
	}
}

void Map::Reset()
{
	m_paintCount = 0;
	m_pPlayer->ResetPos();
	m_pLight->ResetColor();
	for (int i = 0; i < m_pOutColor.size(); i++)
	{
		m_pOutColor[i]->Reset();
		m_pBg[i]->Reset();
		m_pEfect[i]->Reset();
	}
	m_clearBgColor = 0x1f152d;
	m_isReset = false;
}


void Map::GoalDraw(const Handle& handle)
{
	if (m_clearWindowY > 0)
	{
		DrawBox(0, static_cast<int>(Game::kScreenHeight * 0.5f) - (m_clearWindowY + 2), Game::kScreenWidth,
			static_cast<int>(Game::kScreenHeight * 0.5f) + (m_clearWindowY + 2), 0xee0000, true);
		DrawBox(0, static_cast<int>(Game::kScreenHeight * 0.5f) - m_clearWindowY, Game::kScreenWidth,
			static_cast<int>(Game::kScreenHeight * 0.5f) + m_clearWindowY, 0xeec000, true);
	}
	DrawStringToHandle(static_cast<int>(m_clearPos.x), static_cast<int>(m_clearPos.y - 15), "STAGE  CLEAR  !!!!", 0xee0000, handle.h_data.hf_starry_32, 0xffffff);
}

void Map::SetSound(int BGM, int SE)
{
	// 音量更新
	for (int i = 0; i < m_pSound.size(); i++)
	{
		if (i == 0) m_pSound[i]->UpdateBGM(BGM);
		else m_pSound[i]->UpdateSE(SE);
	}
}
