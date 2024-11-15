#include "EnemyRun.h"
#include "DxLib.h"
#include "Map.h"

namespace
{
	//敵のサイズ
	constexpr int kWidth = 30;
	constexpr int kHeight = 30;

	//敵の描画サイズ
	constexpr int kDrawWidth = 32;
	constexpr int kDrawHeight = 32;

	//速度
	constexpr float kSpeed = 2.5f;
	//重力
	constexpr float kGravity = 0.5f;

	constexpr float kSinSpeed = 0.1f;
	constexpr float kAnimationSize = 3.0f;

	/* アニメーション */

	//キャラクターのアニメーション
	constexpr int kUseFrame[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
	//アニメーション１コマのフレーム数
	constexpr int kAnimFrameNum = 4;
	//アニメーションの１サイクルのフレーム数
	constexpr int kAnimFrameCycle = _countof(kUseFrame) * kAnimFrameNum;
}

EnemyRun::EnemyRun():
	m_moveX(0.0f),
	m_moveY(0.0f),
	m_animationHeight(0.0f),
	m_isturnFlag(false),
	m_isAnimLeft(false),
	m_isAnimRight(false),
	m_animationFrame(0),
	m_animFrame(0),
	m_animCount(0),
	m_dir(kRunRight)
{
}

void EnemyRun::Update()
{
	bool isMove = false;

	//毎フレーム下方向に加速する(重力の影響を受ける)
	m_moveY += kGravity;

	if (m_isturnFlag == false)
	{
		m_moveX = kSpeed; //右方向
		m_isAnimRight = true;
		isMove = true;
		m_dir = kRunRight;
	}
	if (m_isturnFlag == true)
	{
		m_moveX = -kSpeed; //左方向
		m_isAnimLeft = true;
		isMove = true;
		m_dir = kRunLeft;
	}

	if (isMove)
	{
		//アニメーション
		m_animFrame++;
		if (m_animFrame >= kAnimFrameCycle) m_animFrame = 0;
	}

	//画面端から出ていかない
	if (m_posX < 15) m_isturnFlag = false;
	if (m_posX > 3840 - 15) m_isturnFlag = true;

	m_posX += m_moveX;
	Rect chipRect;	//当たったマップチップの矩形
	//横から当たったかをチェックする
	if (m_pMap->IsCol(getRect(), chipRect))
	{
		if (m_moveX > 0.0f)//敵が右方向に移動している
		{
			m_posX = chipRect.left - kWidth * 0.5 - 1; //マップチップの左側にぶつからない位置に補正
			m_isturnFlag = true;
		}
		else if (m_moveX < 0.0f)
		{
			m_posX = chipRect.right + kWidth * 0.5 + 1; //　上に同じ
			m_isturnFlag = false;
		}
	}

	m_posY += m_moveY;
	//縦から当たったかをチェックする
	if (m_pMap->IsCol(getRect(), chipRect))
	{
		if (m_moveY > 0.0f)//敵が上下方向に移動している
		{
			//地面に立っている場合は何もしない
			m_posY = chipRect.top - 1;
			m_moveY = 0.0f;
		}
		else if (m_moveY < 0.0f)
		{
			m_posY = chipRect.bottom + kHeight + 1; //　上に同じ
		}
	}
}

void EnemyRun::Draw()
{
	//足元座標を左上座標に変換
	int x = static_cast<int>(m_posX - kWidth * 0.5);
	int y = static_cast<int>(m_posY - kHeight);

	//スクロール量を反映
	x -= m_pMap->GetScrollX();
	y -= m_pMap->GetScrollY();

	int animFrame = m_animFrame / kAnimFrameNum;

	int srcX = kUseFrame[animFrame] * kDrawWidth;
	int srcY = kDrawHeight * m_dir;

	//x = 210;
	//y = 650;
	DrawRectRotaGraph(x + 16, y + 16, srcX, srcY, kDrawWidth, kDrawHeight, 1.0, 0.0, m_handle, true, false);
	//DrawFormatString(0, 32, 0x00ff00, "%d", x + 16);
	//DrawFormatString(0, 48, 0x00ff00, "%d", y + 16);
}
