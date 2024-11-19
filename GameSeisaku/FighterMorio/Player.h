/*
#pragma once
#include <memory>
#include "Rect.h"

//-----------------------------------------------------------------------------
// 2024 Takeru Yui All Rights Reserved.
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------//
// �萔
//-----------------------------------------//
const float Gravity = 0.3f;                         // �L�����Ɋ|����d�͉����x
const float JumpPower = 9.0f;                         // �L�����̃W�����v��
const float Speed = 5.0f;                         // �L�����̈ړ��X�s�[�h

/// <summary>
/// �v���C���[�\����
/// </summary>
struct Player
{
	VECTOR	pos;		// ���W HACK: �v���C���[�̍��W�̒��S�́A���F���S�@�c�F���S�B�`���v�Z��ς�����S���ς��̂Œ���
	VECTOR	dir;		// ���W
	float	w, h;		// ���A����
	float	fallSpeed;	// �v���C���[�̗������x�B�W�����v���͔��]����
	bool	isGround;	// �v���C���[���ڒn����
	bool	isHitTop;	// �v���C���[�̓����V��ɓ������Ă��邩
};

//-----------------------------------------//
// �v���g�^�C�v�錾
//-----------------------------------------//
struct Map;
struct MapChip;
struct Camera;
void InitPlayer(Player& player);
void UpdatePlayer(Player& player, const Map& map);
VECTOR CheckPlayerHitWithMap(Player& player, const Map& map, const VECTOR& velocity);
bool IsHitPlayerWithMapChip(const Player& player, const VECTOR& futurePos, const MapChip& mapChip);
void CheckIsTopHit(Player& player, const Map& map);
void CheckIsGround(Player& player, const Map& map);
void DrawPlayer(const Player& player, const Camera& camera);
*/
