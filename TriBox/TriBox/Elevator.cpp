#include "Elevator.h"
#include "DxLib.h"
#include "ElevatorRail.h"
#include "Player.h"
#include "Geometry.h"


Elevator::Elevator(Player& _player,Position2f _pos) : player(_player),pos(_pos), vel(0.f)
{
	imgPath = LoadGraph("Resource/img/elevator.png");
}


Elevator::~Elevator()
{
}

void Elevator::Draw()
{
	DrawRotaGraph(pos.x, pos.y, 1.f, 0.f, imgPath, true);
}

void Elevator::Update(float _speed)
{
	MoveElevator(_speed);
}

Rect& Elevator::GetRect()
{
	Rect rect;
	rect.SetCenter(pos.x, pos.y, blocksize, blocksize);
	return rect;
}

void Elevator::MoveElevator(float _speed)
{
	pos.y -= _speed;
	pos.y += vel;
}

void Elevator::Active(RailType* _railType)
{
	float num = 0.8f;

	if (*_railType == RailType::topRail)
	{
		vel = num;
	}
	else if (*_railType == RailType::bottomRail)
	{
		vel = -num;
	}
}

