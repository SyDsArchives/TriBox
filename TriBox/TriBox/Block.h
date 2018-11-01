#pragma once
#include "Vector2D.h"

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

	void Draw();
public:
	Block(Position2f _pos);
	~Block();

	void Update();

	HitObjectData HitCheck(Position2f pos);
};

