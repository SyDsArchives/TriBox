#pragma once
#include "Vector2D.h"
#include <string>

enum class HitDirection {
	none,
	top,
	left,
	right,
	bottom,
};

struct ObjectHitType;
class Player;
class Block
{
private:

	Position2f pos;

	Player& player;

	int blockimg;

	void MoveBlock(float _speed);

	ObjectHitType HitCheck(Position2f pos);
public:
	Block(Player& _player, Position2f _pos);
	~Block();

	void Draw();

	void Update(float _speed);

	Position2f GetBlockPos();
};

