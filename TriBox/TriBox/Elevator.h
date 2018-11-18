#pragma once
#include "ObjectParent.h"
#include "Vector2D.h"

enum class RailType;
class Player;
class Elevator : public ObjectParent
{
private:
	Position2f pos;
	
	Player& player;

	int imgPath;

	float vel;

	bool playerHit;

	//ƒvƒŒƒCƒ„[‚É‡‚í‚¹‚½ˆÚ“®
	void MoveElevator(float _speed);

	bool HitCheck(Position2f _pos);
public:
	Elevator(Player & _player, Position2f _pos);
	~Elevator();

	void Active(RailType* _railType);
	void Draw();
	void Update(float _speed);

	Position2f GetPosition() { return pos; };
};

