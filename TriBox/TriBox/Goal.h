#pragma once
#include "Vector2D.h"

struct HitObjectData;
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

	bool HitCheck(Position2f _pos);
	void Update(float _speed);
};

