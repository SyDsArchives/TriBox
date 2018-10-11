#pragma once
#include "Vector2D.h"
class Block
{
private:
	int blockimg;
	Position2f pos;
public:
	Block(Position2f _pos);
	~Block();

	void Draw();

};

