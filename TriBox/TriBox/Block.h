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

struct HitObjectData {
	bool isHit;
	std::string objectName;
};

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

	HitObjectData HitCheck(Position2f pos);
};

