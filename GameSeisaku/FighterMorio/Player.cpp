#include "Player.h"
#include <cmath>
#include "DxLib.h"
#include "Map.h"
#include "Camera.h"
#include "Kuribou.h"
#include "SystemEngineer.h"
#include "Pad.h"

namespace
{
	const float Gravity = 0.5f;		// キャラに掛かる重力加速度
	const float JumpPower = 11.75f;	// キャラのジャンプ力
	const float Speed = 4.5f;		// キャラの移動スピード
	const float RunSpeed = 6.5f;		// キャラのダッシュ時移動スピード
	const int	Width = 32;
}

Player::Player() :
	m_pMap(),
	m_pCamera(),
	//m_pKuribou(new Kuribou),
	m_pSystemEngineer(new SystemEngineer),
	w(32),
	h(32),
	fallSpeed(0.0f),
	pos(VGet(40.0f + h * 0.5f, 992, 0)),
	dir(VGet(0, 0, 0)),
	velocity(VGet(0, 0, 0)),
	isGround(false),
	isHitTop(false),
	playerDeath(0),
	isDeath(false),
	isClear(false),
	mapChip(0),
	_isHit(0),
	m_PlayerGraph(0),
	m_kChipNumY(MapDataFile::kChipNumY),
	m_kChipNumX(MapDataFile::kChipNumX),
	m_k1ChipNumY(MapDataFile::k1ChipNumY),
	m_k1ChipNumX(MapDataFile::k1ChipNumX),
	m_k2ChipNumY(MapDataFile::k2ChipNumY),
	m_k2ChipNumX(MapDataFile::k2ChipNumX)
{
}

Player::~Player()
{
	DeleteGraph(m_PlayerGraph);
	delete m_pSystemManager;
}

void Player::Init(int mapNumber, SystemEngineer* pSE)
{
	m_PlayerGraph = LoadGraph("data/image/player(kari).png");
	mapChip = mapNumber;
	m_pSystemEngineer = pSE;
	if (mapChip == 0)
	{
		for (int hChip = 0; hChip < m_kChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < m_kChipNumX; wChip++)
			{
				PrototypeChipData[hChip][wChip].chipKind = MapDataFile::mapChipData[hChip][wChip];
				PrototypeChipData[hChip][wChip].w = MapDataFile::kChipWidth;
				PrototypeChipData[hChip][wChip].h = MapDataFile::kChipHeight;
				PrototypeChipData[hChip][wChip].pos.x = wChip * MapDataFile::kChipWidth;
				PrototypeChipData[hChip][wChip].pos.y = hChip * MapDataFile::kChipHeight;
			}
		}
	}

	if (mapChip == 1)
	{
		for (int hChip = 0; hChip < m_k1ChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < m_k1ChipNumX; wChip++)
			{
				PrototypeChipData1[hChip][wChip].chipKind = MapDataFile::mapChipData1[hChip][wChip];
				PrototypeChipData1[hChip][wChip].w = MapDataFile::kChipWidth;
				PrototypeChipData1[hChip][wChip].h = MapDataFile::kChipHeight;
				PrototypeChipData1[hChip][wChip].pos.x = wChip * MapDataFile::kChipWidth;
				PrototypeChipData1[hChip][wChip].pos.y = hChip * MapDataFile::kChipHeight;
			}
		}
	}

	if (mapChip == 2)
	{
		for (int hChip = 0; hChip < m_k2ChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < m_k2ChipNumX; wChip++)
			{
				PrototypeChipData2[hChip][wChip].chipKind = MapDataFile::mapChipData2[hChip][wChip];
				PrototypeChipData2[hChip][wChip].w = MapDataFile::kChipWidth;
				PrototypeChipData2[hChip][wChip].h = MapDataFile::kChipHeight;
				PrototypeChipData2[hChip][wChip].pos.x = wChip * MapDataFile::kChipWidth;
				PrototypeChipData2[hChip][wChip].pos.y = hChip * MapDataFile::kChipHeight;
			}
		}
	}
}

void Player::Update(Camera* camera, std::list<Kuribou*>& Kuribou, int mapNumber)
{
	if(isDeath)return;
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

	// 走っているかどうか
	if (input & PAD_INPUT_A)
	{
		// 走っている場合移動量を出す
		velocity = VScale(dir, RunSpeed);
	}
	else
	{
		// 通常時移動量を出す
		velocity = VScale(dir, Speed);
	}
#ifdef _DEBUG
	if (input & PAD_INPUT_C)
	{
		fallSpeed = -JumpPower + 4;
		isGround = false;
	}
#endif // _DEBUG

	// 落下速度を更新
	fallSpeed += Gravity;

	// 先に設定判定をする
	CheckIsGround(mapNumber);
	CheckIsTopHit(mapNumber);
	// 画面上にいる敵の数だけ繰り返して調べる
	for (auto& item : Kuribou)
	{
		if (!item->IsEnemyDeath())
		{
			if (CheckIsEnemyTopHit(item))
			{
				fallSpeed = -JumpPower + 4;	// ジャンプする
				item->SetEnemyDeath(true);
				m_pSystemEngineer->SetScore(true);
				break;
			}
			else
			{
				if ((ChickIsEnemyLeftHit(item)) || (ChickIsEnemyRightHit(item)))
				{
					playerDeath += 1;
					isDeath = true;
					break;
				}
			}
		}
	}
	// 地に足が着いている場合のみジャンプボタンを見る
	if (isGround && !isHitTop && Pad::IsTrigger(input & PAD_INPUT_B))
	{
		fallSpeed = -JumpPower;	// ジャンプボタンを押したら即座に上方向の力に代わる
		isGround = false;
	}
	// プレイヤーの死ぬ高さ
	if (pos.y > 1500)
	{
		isDeath = true;
		playerDeath += 1;
	}
	//976, 656
	if (pos.x >= 6320)
	{
		isClear = true;
	}

	// 落下速度を移動量に加える
	auto fallVelocity = VGet(0, fallSpeed, 0);	// 落下をベクトルに。y座標しか変化しないので最後にベクトルにする
	velocity = VAdd(velocity, fallVelocity);

	// 当たり判定をして、壁にめり込まないようにvelocityを操作する
	velocity = CheckPlayerHitWithMap(mapNumber);

	// 移動
	pos = VAdd(pos, velocity);
}


VECTOR Player::CheckPlayerHitWithMap(int mapNumber)
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


	if (mapChip == 0)
	{
		while (loop)
		{
			loop = false;

			// 未来のプレイヤーのポジションをまず出す
			VECTOR futurePos = VAdd(pos, ret);
			_isHit = 0;

			//全マップチップ分繰り返す
			for (int hChip = 0; hChip < m_kChipNumY; hChip++)
			{
				bool isHit = false;
				for (int wChip = 0; wChip < m_kChipNumX; wChip++)
				{
					bool isHit = IsHitPlayerWithMapChip(mapNumber, futurePos, hChip, wChip);

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
								_isHit = 3;
								ret.y = 0.0f;
							}
							loop = true;
						}
						// どちらも締め切ったときにloop解除
						if (ret.x == 0.0f && ret.y == 0.0f)
						{
							_isHit = 2;
							loop = false;
							break;
						}

						break;
					}
					if (isHit)
					{
						_isHit = 1;//Debug用
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

			// 未来のプレイヤーのポジションをまず出す
			VECTOR futurePos = VAdd(pos, ret);

			_isHit = 0;

			//全マップチップ分繰り返す
			for (int hChip = 0; hChip < m_k1ChipNumY; hChip++)
			{
				bool isHit = false;
				for (int wChip = 0; wChip < m_k1ChipNumX; wChip++)
				{
					bool isHit = IsHitPlayerWithMapChip(mapNumber, futurePos, hChip, wChip);

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
								_isHit = 3;
								ret.y = 0.0f;
							}
							loop = true;
						}
						// どちらも締め切ったときにloop解除
						if (ret.x == 0.0f && ret.y == 0.0f)
						{
							_isHit = 2;
							loop = false;
							break;
						}

						break;
					}
					if (isHit)
					{
						_isHit = 1;//Debug用
						break;
					}
				}
			}
		}
		return ret;
	}
	if (mapChip == 2)
	{
		while (loop)
		{
			loop = false;

			// 未来のプレイヤーのポジションをまず出す
			VECTOR futurePos = VAdd(pos, ret);

			_isHit = 0;

			//全マップチップ分繰り返す
			for (int hChip = 0; hChip < m_k2ChipNumY; hChip++)
			{
				bool isHit = false;
				for (int wChip = 0; wChip < m_k2ChipNumX; wChip++)
				{

					bool isHit = IsHitPlayerWithMapChip(mapNumber, futurePos, hChip, wChip);

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
								_isHit = 3;
								ret.y = 0.0f;
							}
							loop = true;
						}
						// どちらも締め切ったときにloop解除
						if (ret.x == 0.0f && ret.y == 0.0f)
						{
							_isHit = 2;
							loop = false;
							break;
						}

						break;
					}
					if (isHit)
					{
						_isHit = 1;//Debug用
						break;
					}
				}
			}
		}
		return ret;
	}
}

bool Player::IsHitPlayerWithMapChip(int mapNumber, const VECTOR& checkPos, int hChip, int wChip)
{
	// 当たっているかどうか調べる
	float futurePosLeft = checkPos.x - w * 0.5f;
	float futurePosRight = checkPos.x + w * 0.5f;
	float futurePosTop = checkPos.y - h * 0.5f;
	float futurePosBottom = checkPos.y + h * 0.5f;
	if (mapChip == 0)
	{
		// ↓デバック用
		const auto& chip = PrototypeChipData[hChip][wChip];
		// マップチップが当たらない種類なら早期return
		if ((chip.chipKind == 0) ||
			(chip.chipKind >= 9) &&
			(chip.chipKind <= 45))
		{
			return false;
		}
		// 当たっているかどうか調べる
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
	if (mapChip == 1)
	{
		// ↓デバック用
		const auto& chip = PrototypeChipData1[hChip][wChip];
		// マップチップが当たらない種類なら早期return
		if ((chip.chipKind == 0) ||
			(chip.chipKind >= 9) &&
			(chip.chipKind <= 45))
		{
			return false;
		}
		// 当たっているかどうか調べる
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
	if (mapChip == 2)
	{
		// ↓デバック用
		const auto& chip = PrototypeChipData2[hChip][wChip];
		// マップチップが当たらない種類なら早期return
		if ((chip.chipKind == 0) ||
			(chip.chipKind >= 9) &&
			(chip.chipKind <= 45))
		{
			return false;
		}
		// 当たっているかどうか調べる
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

bool Player::IsHitPlayerAndEnemy(Kuribou* Kuribou,const VECTOR& checkPos)
{

	// 当たっているかどうか調べる
	float PosLeft = checkPos.x - w * 0.5f;
	float PosRight = checkPos.x + w * 0.5f;
	float PosTop = checkPos.y - h * 0.5f;
	float PosBottom = checkPos.y + h * 0.5f;

	VECTOR Enemypos;
	int EnemyW;
	int EnemyH;
	Enemypos.x = static_cast<int>(Kuribou->GetKuribouPos().x);
	Enemypos.y = static_cast<int>(Kuribou->GetKuribouPos().y);
	EnemyW = static_cast<float>(Kuribou->GetW());
	EnemyH = static_cast<float>(Kuribou->GetH());
	float KuribouLeft = Enemypos.x - EnemyW * 0.5f;
	float KuribouRight = Enemypos.x + EnemyW * 0.5f;
	float KuribouTop = Enemypos.y - EnemyH * 0.5f;
	float KuribouBottom = Enemypos.y + EnemyH * 0.5f;

	if (((KuribouLeft <= PosLeft && PosLeft < KuribouRight) ||
		(KuribouLeft > PosLeft && KuribouLeft < PosRight)) &&
			(KuribouTop > PosTop && KuribouTop < PosBottom))
	{
		return true;
	}
	return false;
}

bool Player::IsHitPlayerAndEnemySide(Kuribou* Kuribou, const VECTOR& checkPos)
{
	// 当たっているかどうか調べる
	float PosLeft = checkPos.x - w * 0.5f;
	float PosRight = checkPos.x + w * 0.5f;
	float PosTop = checkPos.y - h * 0.5f;
	float PosBottom = checkPos.y + h * 0.5f;

	VECTOR Enemypos;
	int EnemyW;
	int EnemyH;
	Enemypos.x = static_cast<int>(Kuribou->GetKuribouPos().x);
	Enemypos.y = static_cast<int>(Kuribou->GetKuribouPos().y);
	EnemyW = static_cast<float>(Kuribou->GetW());
	EnemyH = static_cast<float>(Kuribou->GetH());
	float KuribouLeft = Enemypos.x - EnemyW * 0.5f;
	float KuribouRight = Enemypos.x + EnemyW * 0.5f;
	float KuribouTop = Enemypos.y - EnemyH * 0.5f;
	float KuribouBottom = Enemypos.y + EnemyH * 0.5f;

	if (((KuribouLeft > PosLeft && KuribouLeft < PosRight) ||
		(KuribouRight < PosRight && KuribouRight > PosLeft)) &&
		((KuribouTop <= PosTop && PosTop < KuribouBottom) ||
			(KuribouTop > PosTop && KuribouTop < PosBottom)))
	{
		return true;
	}

	return false;
}

void Player::CheckIsTopHit(int mapNumber)
{
	// 1ドット上にずらして当たれば頭上がぶつかっている （小数点無視）
	VECTOR checkPos = VGet(pos.x, floorf(pos.y) - 1.0f, pos.z);
	// 全マップチップ分繰り返す
	bool isHit = false;

	if (mapChip == 0)
	{
		for (int hChip = 0; hChip < m_kChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < m_kChipNumX; wChip++)
			{
				isHit = IsHitPlayerWithMapChip(mapNumber, checkPos, hChip, wChip);
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

	if (mapChip == 1)
	{
		for (int hChip = 0; hChip < m_k1ChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < m_k1ChipNumX; wChip++)
			{
				isHit = IsHitPlayerWithMapChip(mapNumber, checkPos, hChip, wChip);
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

	if (mapChip == 2)
	{
		for (int hChip = 0; hChip < m_k2ChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < m_k2ChipNumX; wChip++)
			{
				isHit = IsHitPlayerWithMapChip(mapNumber, checkPos, hChip, wChip);
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

void Player::CheckIsGround(int mapNumber)
{
	// 1ドット下にずらして当たれば地面に足がぶつかっている （小数点無視）
	VECTOR checkPos = VGet(pos.x, floorf(pos.y) + 1.0f, pos.z);
	// 全マップチップ分繰り返す
	bool isHit = false;

	if (mapChip == 0)
	{
		for (int hChip = 0; hChip < m_kChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < m_kChipNumX; wChip++)
			{
				isHit = IsHitPlayerWithMapChip(mapNumber, checkPos, hChip, wChip);
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

	if (mapChip == 1)
	{
		for (int hChip = 0; hChip < m_k1ChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < m_k1ChipNumX; wChip++)
			{
				isHit = IsHitPlayerWithMapChip(mapNumber, checkPos, hChip, wChip);
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

	if (mapChip == 2)
	{
		for (int hChip = 0; hChip < m_k2ChipNumY; hChip++)
		{
			for (int wChip = 0; wChip < m_k2ChipNumX; wChip++)
			{
				isHit = IsHitPlayerWithMapChip(mapNumber, checkPos, hChip, wChip);
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
}

bool Player::CheckIsEnemyTopHit(Kuribou* Kuribou)
{
	// 1ドット下にずらして当たれば敵に足がぶつかっている （小数点無視）
	VECTOR checkPos = VGet(pos.x, floorf(pos.y) + 1.0f, pos.z);
	// 全マップチップ分繰り返す
	bool isHit = false;

	
	isHit = IsHitPlayerAndEnemy(Kuribou, checkPos);
	if (isHit)
	{
		// fallSpeedをゼロにし、急激な落下を防ぐ
		fallSpeed = 0.0f;

		// 後々の雑計算に響くので、y座標の小数点を消し飛ばす
		pos.y = floorf(pos.y);	// ちょうど地面に付く位置に
		return true;
	}
	else
	{
		return false;
	}
}

bool Player::ChickIsEnemyLeftHit(Kuribou* Kuribou)
{
	// 1ドット右にずらして当たれば敵にぶつかっている
	VECTOR checkPos = VGet(floorf(pos.x) + 1.0f, pos.y, pos.z);
	// 全マップチップ分繰り返す
	bool isHit = false;
	isHit = IsHitPlayerAndEnemySide(Kuribou, checkPos);
	if (isHit)
	{
		// 後々の雑計算に響くので、y座標の小数点を消し飛ばす
		pos.x = floorf(pos.x);	// ちょうど地面に付く位置に
		return true;
	}
	else
	{
		return false;
	}
}

bool Player::ChickIsEnemyRightHit(Kuribou* Kuribou)
{
	// 1ドット左にずらして当たれば敵にぶつかっている
	VECTOR checkPos = VGet(floorf(pos.x) - 1.0f, pos.y, pos.z);
	// 全マップチップ分繰り返す
	bool isHit = false;
	isHit = IsHitPlayerAndEnemySide(Kuribou, checkPos);
	if (isHit)
	{
		// 後々の雑計算に響くので、y座標の小数点を消し飛ばす
		pos.x = floorf(pos.x);	// ちょうど地面に付く位置に
		return true;
	}
	else
	{
		return false;
	}
}


void Player::Draw(int mapNumber,Camera* camera)
{
	// キャラクタの描画
	auto leftTop = static_cast<int>(pos.x - w * 0.5f);
	auto leftBottom = static_cast<int>(pos.y - h * 0.5f);
	auto rightTop = static_cast<int>(pos.x + w * 0.5f);
	auto rightBottom = static_cast<int>(pos.y + h * 0.5f);
	DrawRectExtendGraph(
		leftTop + static_cast<int>(camera->GetCameraDrawOffset().x),
		leftBottom + static_cast<int>(camera->GetCameraDrawOffset().y),
		rightTop + static_cast<int>(camera->GetCameraDrawOffset().x),
		rightBottom + static_cast<int>(camera->GetCameraDrawOffset().y),
		0, 0, 540, 641,
		m_PlayerGraph, TRUE);
	DrawLine(
		6336 + static_cast<int>(camera->GetCameraDrawOffset().x),
		976 + static_cast<int>(camera->GetCameraDrawOffset().y),
		6336 + static_cast<int>(camera->GetCameraDrawOffset().x),
		656 + static_cast<int>(camera->GetCameraDrawOffset().y), 0xff0000); // (50, 50) から (200, 200) まで赤い線を描画
#ifdef _DEBUG
	DrawBox(
		leftTop + static_cast<int>(camera->GetCameraDrawOffset().x),
		leftBottom + static_cast<int>(camera->GetCameraDrawOffset().y),
		rightTop + static_cast<int>(camera->GetCameraDrawOffset().x),
		rightBottom + static_cast<int>(camera->GetCameraDrawOffset().y),
		0xff0000, FALSE);
	DrawBox(
		static_cast<int>(pos.x) + static_cast<int>(camera->GetCameraDrawOffset().x),
		static_cast<int>(pos.y - h * 1) + static_cast<int>(camera->GetCameraDrawOffset().y),
		static_cast<int>(pos.x) + static_cast<int>(camera->GetCameraDrawOffset().x),
		rightBottom + static_cast<int>(camera->GetCameraDrawOffset().y),
		0xff0000, FALSE);
#endif // _DEBUG
}



//x = 6336
//y =976, 656