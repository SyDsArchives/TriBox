#pragma once
#include <string>

enum class HitDirection {
	none,
	top,
	left,
	right,
	bottom,
};

struct ObjectRectHitType {
	bool isHit_Top;
	bool isHit_Right;
	bool isHit_Left;
	bool isHit_Bottom;
	bool isHit_All;
};

struct Rect;
struct ObjectHitType;
class Player;
class Block
{
private:

	Position2f pos;
	Player& player;

	int blockimg;

	void MoveBlock(float _speed);
public:
	Block(Player& _player, Position2f _pos);
	~Block();

	void Draw();

	void Update(float _speed);

	Position2f GetBlockPos();
	Rect& GetRect();
};

