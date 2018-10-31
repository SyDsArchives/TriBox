#pragma once
#include "Vector2D.h"
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

	bool HitCheck(Position2f _pos);
};

