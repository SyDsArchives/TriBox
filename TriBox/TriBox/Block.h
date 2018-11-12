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
	int blockimg;
	Position2f pos;

	void MoveBlock(float _speed);

public:
	Block(Position2f _pos);
	~Block();

	void Draw();

	void Update(float _speed);

	Position2f GetBlockPos();

	bool HitCheck(Position2f pos);
};

