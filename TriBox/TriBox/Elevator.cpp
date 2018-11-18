#include "Elevator.h"
#include "DxLib.h"
#include "ElevatorRail.h"
#include "Player.h"



Elevator::Elevator(Player& _player,Position2f _pos) : player(_player),pos(_pos), vel(0.f), playerHit(false)
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

	if (HitCheck(player.GetPosition()))
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

bool Elevator::HitCheck(Position2f _pos)
{
	//ÉuÉçÉbÉNÇ…ìñÇΩÇ¡ÇƒÇ¢ÇÈÇ©
	bool isHitTop = pos.y - blocksize < _pos.y;
	bool isHitLeft = pos.x - blocksize < _pos.x;
	bool isHitRight = pos.x + blocksize > _pos.x;
	bool isHitBottom = pos.y + blocksize > _pos.y;

	playerHit = isHitTop && isHitLeft && isHitRight && isHitBottom;

	return playerHit;
}
