#include "Player.h"
#include <cmath>
#include "DxLib.h"
#include "Map.h"
#include "Camera.h"
#include "Pad.h"

//#include <memory>
//#include "Rect.h"

namespace
{
	const float Gravity = 0.3f;		// キャラに掛かる重力加速度
	const float JumpPower = 9.0f;	// キャラのジャンプ力
	const float Speed = 5.0f;		// キャラの移動スピード
}
Player::Player():
	w(30),
	h(60),
	fallSpeed(0.0f),
	pos(VGet(32.0f + h * 0.5f, 100, 0)),
	dir(VGet(0, 0, 0)),
	velocity(VGet(0, 0, 0)),
	ret(VGet(0, 0, 0)),
	futurePos(VGet(0, 0, 0)),
	checkPos(VGet(0, 0, 0)),
	isGround(false),
	isHitTop(false),
	isHit(false),
	isHitWithMapY(0),
	isHitWithMapX(0)
{
}

Player::~Player()
{
}

void Player::Init()
{
	for (int hChip = 0; hChip < MapDataFile::kChipNumY; hChip++)
	{
		for (int wChip = 0; wChip < MapDataFile::kChipNumX; wChip++)
		{
			isHitWithMapY = hChip;
			isHitWithMapX = wChip;
			PrototypeChipData[isHitWithMapY][isHitWithMapX].chipKind = MapDataFile::mapChipData[hChip][wChip];
			PrototypeChipData[isHitWithMapY][isHitWithMapX].w = MapDataFile::kChipWidth;
			PrototypeChipData[isHitWithMapY][isHitWithMapX].h = MapDataFile::kChipHeight;
			PrototypeChipData[isHitWithMapY][isHitWithMapX].pos.x = wChip * MapDataFile::kChipWidth;
			PrototypeChipData[isHitWithMapY][isHitWithMapX].pos.y = hChip * MapDataFile::kChipHeight;
		}
	}
}

void Player::Update()
{
	// 入力状態を更新
	Pad::Update();
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

	ret = velocity;

	// 当たらなくなるまで繰り返す
	bool loop = true;
	bool isFirstHit = true;	// 初回で当たったか
	while (loop)
	{
		loop = false;

		// 未来のプレイヤーのポジションをまず出す
		futurePos = VAdd(pos, ret);

		for (int hChip = 0; hChip < MapDataFile::kChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < MapDataFile::kChipNumX; wChip++)
			{
				isHitWithMapY = hChip;
				isHitWithMapX = wChip;
				isHit = IsHitPlayerWithMapChip(isHitWithMapY, isHitWithMapX);
				// 初回に当たったとき
				if (isHit && isFirstHit)
				{
					pos.x = floorf(pos.x);
					pos.y = floorf(pos.y);
					ret.x = floorf(ret.x);
					ret.y = floorf(ret.y);
					isFirstHit = false;
					loop = true;	// ループ継続
				}
				// 当たらなくなるまで繰り返す(ループは継続)
				if (isHit && !isFirstHit)
				{
					float absX = fabsf(ret.x);	// velocityのx成分の絶対値
					float absY = fabsf(ret.y);	// velocityのy成分の絶対値

					// x成分を縮め切っていなければx成分を縮める
					bool shrinkX = (absX != 0.0f);	// x成分を縮めるかどうか

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
						loop = false;
						break;
					}
					loop = true;
					break;
				}
				if (isHit)
				{
					break;
				}
				//// 当たらなくなるまで繰り返す(ループは継続)
				//if (isHit && !isFirstHit)
				//{
				//	float absX = fabsf(ret.x);	// velocityのx成分の絶対値
				//	float absY = fabsf(ret.y);	// velocityのy成分の絶対値
				//
				//	// x成分を縮め切っていなければx成分を縮める
				//	bool shrinkX = (absX != 0.0f);	// x成分を縮めるかどうか
				//
				//	if (shrinkX)
				//	{
				//		if (ret.x > 0.0f)
				//		{
				//			ret.x -= 1.0f;
				//		}
				//		else
				//		{
				//			ret.x += 1.0f;
				//		}
				//
				//		// 縮め切ったら消す
				//		if (fabs(ret.x) < 1.0f)
				//		{
				//			ret.x = 0.0f;
				//		}
				//		loop = true;
				//	}
				//	else
				//	{
				//		if (ret.y > 0.0f)
				//		{
				//			ret.y -= 1.0f;
				//		}
				//		else
				//		{
				//			ret.y += 1.0f;
				//		}
				//
				//		// 縮め切ったら消す
				//		if (fabs(ret.y) < 1.0f)
				//		{
				//			ret.y = 0.0f;
				//		}
				//		loop = true;
				//	}
				//	// どちらも締め切ったときにloop解除
				//	if (ret.x == 0.0f && ret.y == 0.0f)
				//	{
				//		loop = false;
				//		break;
				//	}
				//
				//	break;
				//}
				//if (isHit)
				//{
				//	break;
				//}
			}
		}
	}

	// MEMO: 超高速で移動してマップ突き抜けた場合は考慮していない
	// MEMO: 処理負荷を少しでも減らすために、マップチップとプレイヤーの距離でいったん計算除外するとか、色々するのはアリ

	return ret;
}

bool Player::IsHitPlayerWithMapChip(int isHitWithMapY, int isHitWithMapX)
{
	const auto& chip = PrototypeChipData[isHitWithMapY][isHitWithMapX];
	// マップチップが当たらない種類なら早期return
	if (chip.chipKind == 0)
	{
		DrawString(40, 40, "当たっていない", 0xffffff, true);
		return false;
	}

	auto width = std::abs(futurePos.x - chip.pos.x);
	auto height = std::abs(futurePos.y - chip.pos.y);

	auto checkWidth = w * 0.5f + chip.w * 0.5f;
	auto checkHeight = h * 0.5f + chip.h * 0.5f;


	if (width < checkWidth && height < checkHeight)
	{
		DrawString(40, 40, "当たっている", 0xffffff, true);
		return true;
	}
	DrawString(40, 40, "当たっていない", 0xffffff, true);
	return false;


	//// 当たっているかどうか調べる
	//float futurePosLeft = futurePos.x - w * 0.5f;
	//float futurePosRight = futurePos.x + w * 0.5f;
	//float futurePosTop = futurePos.y - h * 0.5f;
	//float futurePosBottom = futurePos.y + h * 0.5f;
	//float targetLeft = PrototypeChipData[isHitWithMapY][isHitWithMapX].pos.x - PrototypeChipData[isHitWithMapY][isHitWithMapX].w * 0.5f;
	//float targetRight = PrototypeChipData[isHitWithMapY][isHitWithMapX].pos.x + PrototypeChipData[isHitWithMapY][isHitWithMapX].w * 0.5f;
	//float targetTop = PrototypeChipData[isHitWithMapY][isHitWithMapX].pos.y - PrototypeChipData[isHitWithMapY][isHitWithMapX].h * 0.5f;
	//float targetBottom = PrototypeChipData[isHitWithMapY][isHitWithMapX].pos.y + PrototypeChipData[isHitWithMapY][isHitWithMapX].h * 0.5f;
	//// 矩形同士の当たり判定
	//if (((targetLeft <= futurePosLeft && futurePosLeft < targetRight) ||
	//	(targetLeft > futurePosLeft && targetLeft < futurePosRight)) &&
	//	((targetTop <= futurePosTop && futurePosTop < targetBottom) ||
	//		(targetTop > futurePosTop && targetTop < futurePosBottom)))
	//{
	//	DrawString(40, 40, "当たっている", 0xffffff, true);
	//	return true;
	//}
	//return false;
}

void Player::CheckIsTopHit()
{
	// 1ドット上にずらして当たれば頭上がぶつかっている （小数点無視）
	checkPos = VGet(pos.x, floorf(pos.y) - 1.0f, pos.z);
	// 全マップチップ分繰り返す
	bool isHit = false;
	for (int hChip = 0; hChip < MapDataFile::kChipNumY; hChip++)
	{
		for (int wChip = 0; wChip < MapDataFile::kChipNumX; wChip++)
		{
			isHit = IsHitPlayerWithMapChip(isHitWithMapY, isHitWithMapX);
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
	checkPos = VGet(pos.x, floorf(pos.y) + 1.0f, pos.z);
	// 全マップチップ分繰り返す
	bool isHit = false;
	for (int hChip = 0; hChip < MapDataFile::kChipNumY; hChip++)
	{
		for (int wChip = 0; wChip < MapDataFile::kChipNumX; wChip++)
		{
			isHit = IsHitPlayerWithMapChip(isHitWithMapY, isHitWithMapX);
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