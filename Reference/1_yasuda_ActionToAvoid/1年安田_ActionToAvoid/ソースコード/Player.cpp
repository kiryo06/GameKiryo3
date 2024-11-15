#include "Player.h"
#include "DxLib.h"
#include "Map.h"
#include "GamePlayingScene.h"

#include "Rect.h"
#include "Pad.h"

#include "Game.h"
#include <memory>

namespace
{
	//キャラクターサイズ
	constexpr int kWidth = 20; //横サイズ
	constexpr int kHeight = 20;//縦サイズ

	//キャラクターの描画サイズ
	constexpr int kDrawWidth = 32;//横サイズ
	constexpr int kDrawHeight = 32;//縦サイズ

	//当たり判定半径
	constexpr int kRadius = 9;

	//速度
	constexpr float kSpeed = 3.0f;
	//加速
	constexpr float kAccel = 2.0f;

	//重力
	constexpr float kGravity = 0.5f;
	//ジャンプ力
	constexpr float kJumpAcc = -10.0f;


	/* アニメーション */

	//ダメージ演出フレーム数
	constexpr int kDamageFrame = 60;

	//キャラクターのアニメーション
	constexpr int kUseFrame[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
	//アニメーション１コマのフレーム数
	constexpr int kAnimFrameNum = 4;
	//アニメーションの１サイクルのフレーム数
	constexpr int kAnimFrameCycle = _countof(kUseFrame) * kAnimFrameNum;

	//キャラクターのジャンプアニメーション
	constexpr int  kUseJumpFrame[] = { 0 };
	//ジャンプアニメーションの１コマのフレーム数
	constexpr int kJumpAnimFrameNum = 12;
	//アニメーションの１サイクルのフレーム数



	constexpr int kVolume = 128;
	constexpr int kPlayerHalfWidth = 15;
	constexpr int kDamageCount = 60;
	constexpr int kFallRestartX = 40;
	constexpr int kFallRestartY = 1880;

	constexpr int kPlayerAdjustmentX = 9;
	constexpr int kPlayerAdjustmentY = 6;

	constexpr float kHalf = 0.5f;
}

Player::Player() :
	m_isJump			(false),
	m_isRight			(false),
	m_isLeft			(false),
	m_moveX				(0.0f),
	m_moveY				(0.0f),
	m_posY				(1800.0f),
	m_posX				(40.0f),
	m_dir				(kNutral),
	m_animationFrame	(0),
	m_animFrame			(0),
	m_animCount			(0),
	m_damageFrame		(0),
	m_isAnimJump		(false),
	m_isCommand			(false),
	m_isAnimTurn		(false)
{
	//キャラクターのロード
	m_playerHandle01 = LoadGraph("date/image/Player001.png");
	m_playerHandle02 = LoadGraph("date/image/PlayerJump.png");

	//SEロード
	m_seHandle001 = LoadSoundMem("date/sound/se/jumpSe.wav");


}

Player::~Player()
{
	//グラフの削除
	DeleteGraph(m_playerHandle01);
	DeleteGraph(m_playerHandle02);

	//SE削除
	DeleteSoundMem(m_seHandle001);

}

void Player::Init()
{
	
}

void Player::Update()
{
	// 上下左右キーでプレイヤー移動
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	bool isMove = false;
	ChangeVolumeSoundMem(kVolume, m_seHandle001);

	Pad::Update();

	m_dir = kNutral;

	m_moveX = 0.0f;

	if (!m_isCommand)
	{

		if (pad & PAD_INPUT_LEFT)
		{
			m_moveX -= kSpeed;
			m_isLeft = true;
			m_isAnimTurn = true;
			m_dir = kWalk;
		}
		else
		{
			m_isLeft = false;
		}

		if (pad & PAD_INPUT_RIGHT)
		{
			m_moveX += kSpeed;
			m_isRight = true;
			m_isAnimTurn = false;
			m_dir = kWalk;
		}
		else
		{
			m_isRight = false;
		}

		//ダッシュ処理
		if (pad & PAD_INPUT_3 && m_isRight)
		{
			m_moveX += kAccel;
			m_dir = kWalk;
			m_isAnimTurn = false;
		}

		if (pad & PAD_INPUT_3 && m_isLeft)
		{
			m_moveX -= kAccel;
			m_dir = kWalk;
			m_isAnimTurn = true;
		}
	}


	//ダメージの点滅時間
	if (m_isDamage)
	{
		m_damageFrame++;
		if (m_damageFrame > kDamageCount)
		{
			m_isDamage = false;
			m_damageFrame = 0;
		}
	}

	//アニメーション処理
	m_animFrame++;
	if (m_animFrame >= kAnimFrameCycle) m_animFrame = 0;
	

	//画面端から出ていかない
	if (m_posX < kPlayerHalfWidth) m_posX = kPlayerHalfWidth;
	if (m_posX > Game::kStageWidth - kPlayerHalfWidth) m_posX = Game::kStageWidth - kPlayerHalfWidth;

	
	if (m_isJump) //ジャンプをしている場合
	{
		/* 空中にいる場合の処理 */

		//毎フレーム下方向に加速する
		m_moveY += kGravity;

		m_posX += m_moveX;
		//横から当たったかをチェックする
		Rect chipRect;	//当たったマップチップの矩形
		if (m_pMap->IsCol(getRect(),chipRect))
		{
			//横からぶつかった場合の処理
			//左右どちらから当たったかをデバッグ表示
			if (m_moveX > 0.0f)//プレイヤーが右方向に移動している
			{
				//printfDx("プレイヤーの右側がマップにぶつかった\n");
				m_posX = chipRect.left - kWidth * kHalf - 1; //マップチップの左側ちょうどぶつからない位置に補正
			}
			else if (m_moveX < 0.0f)
			{
				//printfDx("プレイヤーの左側がマップにぶつかった\n");
				m_posX = chipRect.right + kWidth * kHalf + 1; //マップチップの右側ちょうどぶつからない位置に補正
			}
		}

		m_posY += m_moveY;
		//縦からあたったかをチェックする
		if (m_pMap->IsCol(getRect(), chipRect))
		{

			//上下どちらから当たったかをデバッグ表示
			if (m_moveY > 0.0f)//プレイヤーが上下方向に移動している
			{
				//着地
				m_posY -= m_moveY;
				m_moveY = 0.0f;
				m_isJump = false;
				m_isAnimJump = false;

			}
			else if (m_moveY < 0.0f)
			{
				m_posY = chipRect.bottom + kHeight + 1;		//めり込まない位置に戻す
				m_moveY *= -1.0f; //上方向への加速を下方向に変換
			}
		}
		
	}
	else /* 地面についている場合 */
	{
		if (!m_isCommand)
		{
			//ジャンプ処理
			if (pad & PAD_INPUT_1 && m_isJump == false)
			{
				m_isJump = true;
				m_jumpCount++;
				
			}
			else m_jumpCount = 0;

			if (m_jumpCount == 1 && m_isJump)
			{
				PlaySoundMem(m_seHandle001, DX_PLAYTYPE_BACK, true);//ジャンプ音
				m_moveY = kJumpAcc;
				m_isAnimJump = true;

			}
			else m_isJump = false;
		}
		

		m_posX += m_moveX;
		Rect chipRect; //当たったマップチップの矩形
		//横から当たったかをチェックする
		if (m_pMap->IsCol(getRect(), chipRect))
		{
			//横からぶつかった場合の処理
			//左右どちらから当たったかをデバッグ表示
			if (m_moveX > 0.0f)//プレイヤーが右方向に移動している
			{
				//printfDx("プレイヤーの右側がマップにぶつかった\n");
				m_posX = chipRect.left - kWidth * kHalf -1; //マップチップの左側ちょうどぶつからない位置に補正
			}
			else if (m_moveX < 0.0f)
			{
				//printfDx("プレイヤーの左側がマップにぶつかった\n");
				m_posX = chipRect.right + kWidth * kHalf + 1; //マップチップの右側ちょうどぶつからない位置に補正
			}
		}

		m_posY += m_moveY;
		//縦からあたったかをチェックする
		if (m_pMap->IsCol(getRect(), chipRect))
		{

			//上下どちらから当たったかをデバッグ表示
			if (m_moveY > 0.0f)//プレイヤーが上下方向に移動している
			{
				//地面に立っている何もしない
				m_posY = chipRect.top - 1;
				m_isJump = false; //地面についているからfalse
				m_isAnimJump = false;

			}
			else if (m_moveY < 0.0f)
			{
				m_posY = chipRect.bottom + kHeight + 1;		//めり込まない位置に戻す
				m_moveY *= -1.0f; //上方向への加速を下方向に変換
			}
		}
		else
		{
			//地面にすらぶつかっていない
			m_isJump = true;
		}

	}
}

void Player::Draw()
{
	

	// ダメージ演出  2フレーム間隔で表示非表示切り替え
	// 0: 表示される
	// 1: 表示される
	// 2: 非表示
	// 3: 非表示
	// 4: 表示される	...
	// % 4 することで012301230123... に変換する
	if (m_damageFrame % 4 >= 2) return;

	//足元座標を左上座標に変換
	int x = static_cast<int>(m_posX - kWidth * kHalf);
	int y = static_cast<int>(m_posY - kHeight);

	//スクロール量を反映
	x -= m_pMap->GetScrollX();
	y -= m_pMap->GetScrollY();

	//プレイヤーのアニメフレーム
	int animFrame = m_animFrame / kAnimFrameNum;

	//プレイヤーの切り取り座標
	int srcX = kUseFrame[animFrame] * kDrawWidth;
	int srcY = kDrawHeight * m_dir;

	//ジャンプするときのアニメフレーム
	int jumpAnimFrame = m_animFrame / kJumpAnimFrameNum;

	//プレイヤージャンプの切り取り座標
	int JsrcX = kUseJumpFrame[jumpAnimFrame] * kDrawWidth;
	int JsrcY = 0;
	
	if (m_isAnimJump) //ジャンプした場合
	{
		DrawRectRotaGraph(x + kPlayerAdjustmentX, y + kPlayerAdjustmentY, JsrcX, JsrcY, kDrawWidth, kDrawHeight, 1.0, 0.0, m_playerHandle02, true, m_isAnimTurn);
	}
	else
	{
		DrawRectRotaGraph(x + kPlayerAdjustmentX, y + kPlayerAdjustmentY, srcX, srcY, kDrawWidth, kDrawHeight, 1.0, 0.0, m_playerHandle01, true, m_isAnimTurn);
	}
}

float Player::GetRadius()
{
	return kRadius;
}

void Player::Damage()
{
	m_isDamage = true;
}

float Player::GetLeft()
{

	return m_posX - kWidth * kHalf;
}

float Player::GetRight()
{
	return m_posX + kWidth * kHalf;
}

float Player::GetTop()
{
	return m_posY - kHeight;
}

float Player::GetBottom()
{
	return m_posY;
}

void Player::CommandOff()
{
	m_isCommand = true;
}

void Player::FallRestart()
{
	m_posX = kFallRestartX;
	m_posY = kFallRestartY;
}

Rect Player::getRect()
{
	//プレイヤーの当たり判定矩形情報を作成
	Rect rect;
	rect.top = GetTop();
	rect.bottom = GetBottom();
	rect.left = GetLeft();
	rect.right = GetRight();
	return rect;
}
