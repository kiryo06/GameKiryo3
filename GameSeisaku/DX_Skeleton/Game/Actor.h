#pragma once
#include "../Geometry.h"

class GameScene;
class Collision;
class Input;

// ゲームオブジェクト
class Actor
{
protected:
	GameScene& gameScene_;
	Position2 pos_; // 中心位置

public:
	Actor(GameScene& gameScene);
	virtual ~Actor() {}

	void SetPosition(const Position2& pos);

	virtual void Update(Input& input) = 0;
	virtual void Draw() const = 0;

	// 当たったときに流れる関数
	virtual void OnHit(Collision& collision) = 0;
};

