#pragma once
#include "Vector2D.h"


struct Rect;
class Goal
{
private:
	Position2f pos;
	int goalimg;

	void MoveBlock(float _speed);
	void Draw();

public:
	Goal(Position2f _pos);
	~Goal();

	Position2f GetPosition() { return pos; };
	Rect& GetRect();

	void Update(float _speed);
};

