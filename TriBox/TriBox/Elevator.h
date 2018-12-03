#pragma once
#include "ObjectParent.h"
#include "Vector2D.h"

//struct ObjectHitType;
struct Rect;
enum class RailType;
class Player;
class Elevator : public ObjectParent
{
private:
	Position2f pos;
	
	Player& player;

	int imgPath;
	int imgPath_Light;

	float vel;

	bool hitPlayer;

	//ƒvƒŒƒCƒ„[‚É‡‚í‚¹‚½ˆÚ“®
	void MoveElevator(float _speed);
public:
	Elevator(Player & _player, Position2f _pos);
	~Elevator();

	void Active(RailType* _railType);
	void Draw();
	void Update(float _speed);

	void onPlayer(bool _hit);

	Position2f GetPosition() { return pos; };

	Rect& GetRect();
};

