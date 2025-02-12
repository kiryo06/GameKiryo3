#pragma once
#include "../Geometry.h"

class GameScene;
class Collision;
class Input;

// �Q�[���I�u�W�F�N�g
class Actor
{
protected:
	GameScene& gameScene_;
	Position2 pos_; // ���S�ʒu

public:
	Actor(GameScene& gameScene);
	virtual ~Actor() {}

	void SetPosition(const Position2& pos);

	virtual void Update(Input& input) = 0;
	virtual void Draw() const = 0;

	// ���������Ƃ��ɗ����֐�
	virtual void OnHit(Collision& collision) = 0;
};

