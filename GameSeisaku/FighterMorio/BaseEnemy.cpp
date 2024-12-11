#include "BaseEnemy.h"
#include <cmath>
#include "DxLib.h"
#include "Camera.h"
#include "Player.h"

namespace
{
	const float Gravity = 0.3f;		// 敵に掛かる重力加速度
	const float JumpPower = 9.0f;	// キャラのジャンプ力
	const float EnemySpeed = 3.0f;	// 仮速度
	const float Speed = 3.0f;		// 敵の移動スピード
}

BaseEnemy::BaseEnemy() :
	m_camera(),
	m_map(),
	w(30),
	h(32),
	fallSpeed(0.0f),
	leftSpeed(0.0f),
	rightSpeed(0.0f),
	pos(VGet(1050.0f + h * 0.5f, 992, 0)),
	dir(VGet(0, 0, 0)),
	velocity(VGet(0, 0, 0)),
	isGround(false),
	isHitTop(false),
	isLeft(false),
	isRight(false),
	mapChip(0),
	HitEnemy(0),
	m_kChipNumY(MapDataFile::kChipNumY),
	m_kChipNumX(MapDataFile::kChipNumX),
	m_k1ChipNumY(MapDataFile::k1ChipNumY),
	m_k1ChipNumX(MapDataFile::k1ChipNumX),
	m_k2ChipNumY(MapDataFile::k2ChipNumY),
	m_k2ChipNumX(MapDataFile::k2ChipNumX)
{
}

BaseEnemy::~BaseEnemy()
{
}

void BaseEnemy::Init(int mapNumber)
{
	switch (mapNumber)
	{
	case 0:
		mapChip = 0;
		break;
	case 1:
		mapChip = 1;
		break;
	case 2:
		mapChip = 2;
		break;
	}

	if (mapChip == 0)
	{
		for (int hChip = 0; hChip < m_kChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < m_kChipNumX; wChip++)
			{
				PrototypeChipData[hChip][wChip].chipKind = MapDataFile::mapChipData[hChip][wChip];	// マップチップの配列
				PrototypeChipData[hChip][wChip].w = MapDataFile::kChipWidth;						// マップチップのサイズW
				PrototypeChipData[hChip][wChip].h = MapDataFile::kChipHeight;						// マップチップのサイズH
				PrototypeChipData[hChip][wChip].pos.x = wChip * MapDataFile::kChipWidth;			// マップチップの位置X
				PrototypeChipData[hChip][wChip].pos.y = hChip * MapDataFile::kChipHeight;			// マップチップの位置Y
			}
		}
	}
	
	if (mapChip == 1)
	{
		for (int hChip = 0; hChip < m_k1ChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < m_k1ChipNumX; wChip++)
			{
				PrototypeChipData[hChip][wChip].chipKind = MapDataFile::mapChipData1[hChip][wChip];	// マップチップの配列
				PrototypeChipData[hChip][wChip].w = MapDataFile::kChipWidth;						// マップチップのサイズW
				PrototypeChipData[hChip][wChip].h = MapDataFile::kChipHeight;						// マップチップのサイズH
				PrototypeChipData[hChip][wChip].pos.x = wChip * MapDataFile::kChipWidth;			// マップチップの位置X
				PrototypeChipData[hChip][wChip].pos.y = hChip * MapDataFile::kChipHeight;			// マップチップの位置Y
			}
		}
	}

	if (mapChip == 2)
	{
		for (int hChip = 0; hChip < m_k2ChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < m_k2ChipNumX; wChip++)
			{
				PrototypeChipData[hChip][wChip].chipKind = MapDataFile::mapChipData2[hChip][wChip];	// マップチップの配列
				PrototypeChipData[hChip][wChip].w = MapDataFile::kChipWidth;						// マップチップのサイズW
				PrototypeChipData[hChip][wChip].h = MapDataFile::kChipHeight;						// マップチップのサイズH
				PrototypeChipData[hChip][wChip].pos.x = wChip * MapDataFile::kChipWidth;			// マップチップの位置X
				PrototypeChipData[hChip][wChip].pos.y = hChip * MapDataFile::kChipHeight;			// マップチップの位置Y
			}
		}
	}

}

void BaseEnemy::Update(int mapNumber, Player* player)
{

	// 入力状態を更新
	auto input = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	// 敵の移動処理
	dir = VGet(0, 0, 0);
	//if (player->GetPlayerPos().x < pos.x)
	//{
	//	dir = VAdd(dir, VGet(-1, 0, 0));
	//}

	//if (player->GetPlayerPos().x > pos.x)
	//{
	//	dir = VAdd(dir, VGet(1, 0, 0));
	//}
	dir = VAdd(dir, VGet(-1, 0, 0));
	// 正規化
	if (VSquareSize(dir) > 0)
	{
		dir = VNorm(dir);
	}


	if ((player->GetPlayerPos().x == pos.x)||(player->GetPlayerPos().y == pos.y))
	{
		HitEnemy = 1;
	}
	else
	{
		HitEnemy = 0;
	}

	// 移動量を出す
	velocity = VScale(dir, Speed);

	// 落下速度を更新
	fallSpeed += Gravity;

	// 左右移動
	leftSpeed -= Speed;
	rightSpeed += Speed;

	// HACK: 先に設定判定をすることでfallSpeed修正＋接地フラグ更新
	CheckIsGround(mapNumber);
	CheckIsTopHit(mapNumber);
	CheckIsLeft(mapNumber);
	CheckIsRight(mapNumber);
	/*
	// 地に足が着いている場合のみジャンプボタン(ボタン１ or Ｚキー)を見る
	if (isGround && !isHitTop && input & PAD_INPUT_B)
	{
		fallSpeed = -JumpPower;	// ジャンプボタンを押したら即座に上方向の力に代わる
		isGround = false;
	}
	*/

	// 左に当たったら
	if (isLeft)
	{
		rightSpeed = +EnemySpeed;
		isRight = false;
	}

	// 右に当たったら
	if (isRight)
	{
		rightSpeed = -EnemySpeed;
		isLeft = false;
	}

	// 落下速度を移動量に加える
	auto fallVelocity = VGet(0, fallSpeed, 0);	// 落下をベクトルに。y座標しか変化しないので最後にベクトルにする
	velocity = VAdd(velocity, fallVelocity);

	// 当たり判定をして、壁にめり込まないようにvelocityを操作する
	velocity = CheckBaseEnemyHitWithMap(mapNumber);

	// 移動
	pos = VAdd(pos, velocity);
}

VECTOR BaseEnemy::CheckBaseEnemyHitWithMap(int mapNumber)
{
	// 速度が最初から0なら動かさず早期return
	if (VSize(velocity) == 0)
	{
		return velocity;
	}

	VECTOR ret = velocity;

	// 当たらなくなるまで繰り返す
	bool loop = true;
	bool isFirstHit = true;	// 初回で当たったか


	switch (mapNumber)
	{
	case 0:
		mapChip = 0;
		break;
	case 1:
		mapChip = 1;
		break;
	case 2:
		mapChip = 2;
		break;
	}

	if (mapChip == 0)
	{
		while (loop)
		{
			loop = false;

			// 未来の敵のポジションをまず出す
			VECTOR futurePos = VAdd(pos, ret);


			//全マップチップ分繰り返す
			for (int hChip = 0; hChip < m_kChipNumY; hChip++)
			{
				bool isHit = false;
				for (int wChip = 0; wChip < m_kChipNumX; wChip++)
				{
					bool isHit = IsHitBaseEnemyWithMapChip(mapNumber, futurePos, hChip, wChip);

					// 初回に当たったとき
					if (isHit && isFirstHit)
					{
						// 今後当たり判定でポジションやvelocityの補正をするとき、小数点以下の誤差が産まれる
						// 雑に1ドットずつ減らす、数学計算をしないマッシブ当たり判定には邪魔なので初回に丸めてしまい、
						// 以降改めて当たり判定
						// posもVelocityも丸める
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
		return ret;
	}

	if (mapChip == 1)
	{
		while (loop)
		{
			loop = false;

			// 未来の敵のポジションをまず出す
			VECTOR futurePos = VAdd(pos, ret);


			//全マップチップ分繰り返す
			for (int hChip = 0; hChip < m_k1ChipNumY; hChip++)
			{
				bool isHit = false;
				for (int wChip = 0; wChip < m_k1ChipNumX; wChip++)
				{
					bool isHit = IsHitBaseEnemyWithMapChip(mapNumber, futurePos, hChip, wChip);

					// 初回に当たったとき
					if (isHit && isFirstHit)
					{
						// 今後当たり判定でポジションやvelocityの補正をするとき、小数点以下の誤差が産まれる
						// 雑に1ドットずつ減らす、数学計算をしないマッシブ当たり判定には邪魔なので初回に丸めてしまい、
						// 以降改めて当たり判定
						// posもVelocityも丸める
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
		return ret;
	}
}

bool BaseEnemy::IsHitBaseEnemyWithMapChip(int mapNumber, const VECTOR& checkPos, int hChip, int wChip)
{
	int mapChip = 0;
	switch (mapNumber)
	{
	case 0:
		mapChip = 1;
		break;
	case 1:
		mapChip = 2;
		break;
	}
	if (mapChip == 1)
	{
		// ↓デバック用
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
	else if (mapChip == 2)
	{
		// ↓デバック用
		const auto& chip = PrototypeChipData1[hChip][wChip];
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
}

void BaseEnemy::CheckIsTopHit(int mapNumber)
{
	// 1ドット上にずらして当たれば頭上がぶつかっている （小数点無視）
	VECTOR checkPos = VGet(pos.x, floorf(pos.y) - 1.0f, pos.z);
	// 全マップチップ分繰り返す
	bool isHit = false;
	switch (mapNumber)
	{
	case 0:
		for (int hChip = 0; hChip < m_kChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < m_kChipNumX; wChip++)
			{
				isHit = IsHitBaseEnemyWithMapChip(mapNumber, checkPos, hChip, wChip);
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
		break;
	case 1:
		for (int hChip = 0; hChip < m_k1ChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < m_k1ChipNumX; wChip++)
			{
				isHit = IsHitBaseEnemyWithMapChip(mapNumber, checkPos, hChip, wChip);
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
		break;
	}
}

void BaseEnemy::CheckIsGround(int mapNumber)
{
	// 1ドット下にずらして当たれば地面に足がぶつかっている （小数点無視）
	VECTOR checkPos = VGet(pos.x, floorf(pos.y) + 1.0f, pos.z);
	// 全マップチップ分繰り返す
	bool isHit = false;
	switch (mapNumber)
	{
	case 0:
		for (int hChip = 0; hChip < m_kChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < m_kChipNumX; wChip++)
			{
				isHit = IsHitBaseEnemyWithMapChip(mapNumber, checkPos, hChip, wChip);
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
		break;
	case 1:
		for (int hChip = 0; hChip < m_k1ChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < m_k1ChipNumX; wChip++)
			{
				isHit = IsHitBaseEnemyWithMapChip(mapNumber, checkPos, hChip, wChip);
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
		break;
	}
}

void BaseEnemy::CheckIsLeft(int mapNumber)
{
	// 左に動いて当たれば壁に体がぶつかっている
	VECTOR checkPos = VGet(pos.x, floorf(pos.y) + 1.0f, pos.z);
	// 全マップチップ分繰り返す
	bool isHit = false;
	switch (mapNumber)
	{
	case 0:
		for (int hChip = 0; hChip < m_kChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < m_kChipNumX; wChip++)
			{
				isHit = IsHitBaseEnemyWithMapChip(mapNumber, checkPos, hChip, wChip);
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
			isLeft = true;
			// leftSpeedをゼロにし、急激な落下を防ぐ
			leftSpeed = 0.0f;

			// 後々の雑計算に響くので、y座標の小数点を消し飛ばす
			pos.x = floorf(pos.x);	// ちょうど地面に付く位置に
		}
		else
		{
			isLeft = false;
		}
		break;
	case 1:
		for (int hChip = 0; hChip < m_k1ChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < m_k1ChipNumX; wChip++)
			{
				isHit = IsHitBaseEnemyWithMapChip(mapNumber, checkPos, hChip, wChip);
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
			isLeft = true;
			// leftSpeedをゼロにし、急激な落下を防ぐ
			leftSpeed = 0.0f;

			// 後々の雑計算に響くので、y座標の小数点を消し飛ばす
			pos.x = floorf(pos.x);	// ちょうど地面に付く位置に
		}
		else
		{
			isLeft = false;
		}
		break;
	}
}

void BaseEnemy::CheckIsRight(int mapNumber)
{

}

void BaseEnemy::Draw(Camera* camera)
{
	// 敵の描画
	auto leftTop = static_cast<int>(pos.x - w * 0.5f);
	auto leftBottom = static_cast<int>(pos.y - h * 0.5f);
	auto rightTop = static_cast<int>(pos.x + w * 0.5f);
	auto rightBottom = static_cast<int>(pos.y + h * 0.5f);
	DrawBox(
		leftTop + static_cast<int>(camera->GetCameraDrawOffset().x),
		leftBottom + static_cast<int>(camera->GetCameraDrawOffset().y),
		rightTop + static_cast<int>(camera->GetCameraDrawOffset().x),
		rightBottom + static_cast<int>(camera->GetCameraDrawOffset().y),
		0x4b0082, TRUE);

#ifdef _DEBUG
	DrawFormatString(0, 600, 0xffffff, " PlayerIsHit : %d", HitEnemy, true);
#endif // _DEBUG
}
