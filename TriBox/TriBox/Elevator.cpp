#include "Elevator.h"
#include "DxLib.h"
#include "ElevatorRail.h"
#include "Player.h"



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

	Position2f objPos(player.GetPosition().x, player.GetPosition().y + 25);

	if (HitCheck(objPos).isHit_All)
	{
		player.SetOnGround(true);
		float setPosY = pos.y - blocksize - 5;
		player.SetPosition(Vector2f(player.GetPosition().x, setPosY));
	}
}

void Elevator::MoveElevator(float _speed)
{
	pos.x -= _speed;
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

ObjectHitType Elevator::HitCheck(Position2f _pos)
{
	ObjectHitType ret = {};

	//ÉuÉçÉbÉNÇ…ìñÇΩÇ¡ÇƒÇ¢ÇÈÇ©
	ret.isHit_Top = pos.y - blocksize < _pos.y;
	ret.isHit_Left = pos.x - blocksize < _pos.x;
	ret.isHit_Right = pos.x + blocksize > _pos.x;
	ret.isHit_Bottom = pos.y + blocksize > _pos.y;

	ret.isHit_All = ret.isHit_Top && ret.isHit_Left && ret.isHit_Right && ret.isHit_Bottom;

	return ret;
}
