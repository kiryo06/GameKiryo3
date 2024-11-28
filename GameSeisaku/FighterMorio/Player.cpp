#include "Player.h"
#include <cmath>
#include "DxLib.h"
#include "Map.h"
#include "Camera.h"

//#include <memory>
//#include "Rect.h"

namespace
{
	const float Gravity = 0.3f;		// キャラに掛かる重力加速度
	const float JumpPower = 9.0f;	// キャラのジャンプ力
	const float Speed = 5.0f;		// キャラの移動スピード
}
Player::Player():
	m_camera(),
	m_map(),
	w(30),
	h(60),
	fallSpeed(0.0f),
	pos(VGet(32.0f + h * 0.5f, 0, 0)),
	dir(VGet(0, 0, 0)),
	velocity(VGet(0, 0, 0)),
	isGround(false),
	isHitTop(false)
{
}

Player::~Player()
{
}

void Player::Init(int mapNumber)
{
	switch (mapNumber)
	{
	case 0:
		for (int hChip = 0; hChip < MapDataFile::kChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < MapDataFile::kChipNumX; wChip++)
			{
				PrototypeChipData[hChip][wChip].chipKind = MapDataFile::mapChipData[hChip][wChip];
				PrototypeChipData[hChip][wChip].w = MapDataFile::kChipWidth;
				PrototypeChipData[hChip][wChip].h = MapDataFile::kChipHeight;
				PrototypeChipData[hChip][wChip].pos.x = wChip * MapDataFile::kChipWidth;
				PrototypeChipData[hChip][wChip].pos.y = hChip * MapDataFile::kChipHeight;
			}
		}
		break;
	case 1:
		for (int hChip = 0; hChip < MapDataFile::kChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < MapDataFile::kChipNumX; wChip++)
			{
				PrototypeChipData[hChip][wChip].chipKind = MapDataFile::mapChipData1[hChip][wChip];
				PrototypeChipData[hChip][wChip].w = MapDataFile::kChipWidth;
				PrototypeChipData[hChip][wChip].h = MapDataFile::kChipHeight;
				PrototypeChipData[hChip][wChip].pos.x = wChip * MapDataFile::kChipWidth;
				PrototypeChipData[hChip][wChip].pos.y = hChip * MapDataFile::kChipHeight;
			}
		}
		break;
	case 2:

		break;
	}
}

void Player::Update()
{
	// 入力状態を更新
	auto input = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	// プレイヤーの移動処理
	dir = VGet(0, 0, 0);
	if (input & PAD_INPUT_LEFT)
	{
		dir = VAdd(dir, VGet(-1, 0, 0));
	}

	if (input & PAD_INPUT_RIGHT)
	{
		dir = VAdd(dir, VGet(1, 0, 0));
	}

	// 正規化
	if (VSquareSize(dir) > 0)
	{
		dir = VNorm(dir);
	}

	// 移動量を出す
	velocity = VScale(dir, Speed);

	// 落下速度を更新
	fallSpeed += Gravity;

	// HACK: 先に設定判定をすることでfallSpeed修正＋接地フラグ更新
	CheckIsTopHit();
	CheckIsGround();

	// 地に足が着いている場合のみジャンプボタン(ボタン１ or Ｚキー)を見る
	if (isGround && !isHitTop && input & PAD_INPUT_B)
	{
		fallSpeed = -JumpPower;	// ジャンプボタンを押したら即座に上方向の力に代わる
		isGround = false;
	}
	// 落下速度を移動量に加える
	auto fallVelocity = VGet(0, fallSpeed, 0);	// 落下をベクトルに。y座標しか変化しないので最後にベクトルにする
	velocity = VAdd(velocity, fallVelocity);

	// 当たり判定をして、壁にめり込まないようにvelocityを操作する
	velocity = CheckPlayerHitWithMap();

	// 移動
	pos = VAdd(pos, velocity);
}

VECTOR Player::CheckPlayerHitWithMap()
{
	// サイズが最初から0なら動かさず早期return
	if (VSize(velocity) == 0)
	{
		return velocity;
	}

	VECTOR ret = velocity;

	// 当たらなくなるまで繰り返す
	bool loop = true;
	bool isFirstHit = true;	// 初回で当たったか
	while (loop)
	{
		loop = false;

		// 未来のプレイヤーのポジションをまず出す
		VECTOR futurePos = VAdd(pos, ret);

		for (int hChip = 0; hChip < MapDataFile::kChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < MapDataFile::kChipNumX; wChip++)
			{
				bool isHit = IsHitPlayerWithMapChip(futurePos, hChip, wChip);

				// 当たらなくなるまで繰り返す(ループは継続)
				if (isHit && !isFirstHit)
				{
					float absX = fabsf(ret.x);	// velocityのx成分の絶対値
					float absY = fabsf(ret.y);	// velocityのy成分の絶対値
				
					// x成分を縮め切っていなければx成分を縮める
					bool shrinkX = (absX != 0.0f);	// x成分を縮めるかどうか
				
					if (shrinkX)
					{
						if (ret.x > 0.0f)
						{
							ret.x -= 1.0f;
						}
						else
						{
							ret.x += 1.0f;
						}
				
						// 縮め切ったら消す
						if (fabs(ret.x) < 1.0f)
						{
							ret.x = 0.0f;
						}
						loop = true;
					}
					else
					{
						if (ret.y > 0.0f)
						{
							ret.y -= 1.0f;
						}
						else
						{
							ret.y += 1.0f;
						}
				
						// 縮め切ったら消す
						if (fabs(ret.y) < 1.0f)
						{
							ret.y = 0.0f;
						}
						loop = true;
					}
					// どちらも締め切ったときにloop解除
					if (ret.x == 0.0f && ret.y == 0.0f)
					{
						loop = false;
						break;
					}
				
					break;
				}
				if (isHit)
				{
					break;
				}
			}
		}
	}

	// MEMO: 超高速で移動してマップ突き抜けた場合は考慮していない
	// MEMO: 処理負荷を少しでも減らすために、マップチップとプレイヤーの距離でいったん計算除外するとか、色々するのはアリ

	return ret;
}

bool Player::IsHitPlayerWithMapChip(const VECTOR& checkPos, int hChip, int wChip)
{
	const auto& chip = PrototypeChipData[hChip][wChip];

	// マップチップが当たらない種類なら早期return
	if (chip.chipKind == 0)
	{
		return false;
	}

	// 当たっているかどうか調べる
	float futurePosLeft = checkPos.x - w * 0.5f;
	float futurePosRight = checkPos.x + w * 0.5f;
	float futurePosTop = checkPos.y - h * 0.5f;
	float futurePosBottom = checkPos.y + h * 0.5f;
	float targetLeft = chip.pos.x - chip.w * 0.5f;
	float targetRight = chip.pos.x + chip.w * 0.5f;
	float targetTop = chip.pos.y - chip.h * 0.5f;
	float targetBottom = chip.pos.y + chip.h * 0.5f;
	// 矩形同士の当たり判定
	if (((targetLeft <= futurePosLeft && futurePosLeft < targetRight) ||
		(targetLeft > futurePosLeft && targetLeft < futurePosRight)) &&
		((targetTop <= futurePosTop && futurePosTop < targetBottom) ||
			(targetTop > futurePosTop && targetTop < futurePosBottom)))
	{
		return true;
	}
	return false;
}

void Player::CheckIsTopHit()
{
	// 1ドット上にずらして当たれば頭上がぶつかっている （小数点無視）
	VECTOR checkPos = VGet(pos.x, floorf(pos.y) - 1.0f, pos.z);
	// 全マップチップ分繰り返す
	bool isHit = false;
	for (int hChip = 0; hChip < MapDataFile::kChipNumY; hChip++)
	{
		for (int wChip = 0; wChip < MapDataFile::kChipNumX; wChip++)
		{
			isHit = IsHitPlayerWithMapChip(checkPos, hChip, wChip);
			if (isHit)
			{
				break;
			}
		}
		if (isHit)
		{
			break;
		}
		if (isHit)
		{
			// 以前ぶつかっていないのにぶつかるならfallSpeedをゼロにし、即落下するように
			if (!isHitTop)
			{
				isHitTop = true;
				fallSpeed = 0.0f;

				// 後々の雑計算に響くので、y座標の小数点を消し飛ばす
				pos.y = floorf(pos.y);
			}
		}
		else
		{
			isHitTop = false;
		}
	}
}

void Player::CheckIsGround()
{
	// 1ドット下にずらして当たれば地面に足がぶつかっている （小数点無視）
	VECTOR checkPos = VGet(pos.x, floorf(pos.y) + 1.0f, pos.z);
	// 全マップチップ分繰り返す
	bool isHit = false;
	for (int hChip = 0; hChip < MapDataFile::kChipNumY; hChip++)
	{
		for (int wChip = 0; wChip < MapDataFile::kChipNumX; wChip++)
		{
			isHit = IsHitPlayerWithMapChip(checkPos, hChip, wChip);
			if (isHit)
			{
				break;
			}
		}
		if (isHit)
		{
			break;
		}
	}
	if (isHit)
	{
		isGround = true;
		// fallSpeedをゼロにし、急激な落下を防ぐ
		fallSpeed = 0.0f;

		// 後々の雑計算に響くので、y座標の小数点を消し飛ばす
		pos.y = floorf(pos.y);	// ちょうど地面に付く位置に
	}
	else
	{
		isGround = false;
	}
}


void Player::Draw(Camera*camera)
{
	// キャラクタの描画
	auto leftTop = static_cast<int>(pos.x - w * 0.5f);
	auto leftBottom = static_cast<int>(pos.y - h * 0.5f);
	auto rightTop = static_cast<int>(pos.x + w * 0.5f);
	auto rightBottom = static_cast<int>(pos.y + h * 0.5f);
	DrawBox(
		leftTop + static_cast<int>(camera->GetCameraDrawOffset().x),
		leftBottom + static_cast<int>(camera->GetCameraDrawOffset().y),
		rightTop + static_cast<int>(camera->GetCameraDrawOffset().x),
		rightBottom + static_cast<int>(camera->GetCameraDrawOffset().y),
		GetColor(255, 0, 0), TRUE);
}