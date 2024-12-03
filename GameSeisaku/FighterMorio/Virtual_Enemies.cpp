#include "Virtual_Enemies.h"
#include <cmath>
#include "DxLib.h"
#include "Map.h"
#include "Camera.h"

namespace
{
	const float Gravity = 0.3f;		// 敵に掛かる重力加速度
	const float JumpPower = 5.0f;	// 敵のジャンプ力
	const float Speed = 3.0f;		// 敵の移動スピード
}
Virtual_Enemies::Virtual_Enemies() :
	m_camera(),
	m_map(),
	w(30),
	h(30),
	fallSpeed(0.0f),
	pos(VGet(32.0f + h * 0.5f, 1000, 0)),
	dir(VGet(0, 0, 0)),
	velocity(VGet(0, 0, 0)),
	isGround(false),
	isHitTop(false),
	mapChipY(),
	mapChipX()
{
}

Virtual_Enemies::~Virtual_Enemies()
{
}

void Virtual_Enemies::Init(int mapNumber)
{
}

void Virtual_Enemies::Update(int mapNumber)
{
}

VECTOR Virtual_Enemies::CheckVirtual_EnemiesHitWithMap(int mapNumber)
{
	return VECTOR();
}

bool Virtual_Enemies::IsHitVirtual_EnemiesWithMapChip(int mapNumber, const VECTOR& checkPos, int hChip, int wChip)
{
	return false;
}

void Virtual_Enemies::CheckIsTopHit(int mapNumber)
{
}

void Virtual_Enemies::CheckIsGround(int mapNumber)
{
}

void Virtual_Enemies::Draw(Camera* camera)
{
}
