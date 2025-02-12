#pragma once
#include "Actor.h"

class UnbreakableBlock : public Actor
{
private:
	int handle_;
public:
	UnbreakableBlock(GameScene& gameScene);

	void Update(Input&) override;
	void Draw() const override;

	void OnHit(Collision& collision) override;
};

