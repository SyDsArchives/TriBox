#pragma once


struct Rect;
class Lava
{

private:
	Position2f pos;
	int lavaimg;

	float riseSpeed;

	void MoveBlock(float _speed);
	void Draw();

public:
	Lava(Position2f _pos);
	~Lava();

	Position2f GetPosition() { return pos; };
	Rect& GetRect();

	void Update(float _speed);

};

