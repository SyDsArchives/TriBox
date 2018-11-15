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

struct HitObjectData;
class Player;
class Block
{
private:

	Player& player;

	int blockimg;
	Position2f pos;
	bool playerHit;

	void MoveBlock(float _speed);


public:
	Block(Player& _player, Position2f _pos);
	~Block();

	void Draw();

	void Update(float _speed);

	Position2f GetBlockPos();

	bool HitCheck(Position2f pos);
};

