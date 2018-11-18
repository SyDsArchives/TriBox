#include "ElevatorRail.h"
#include "Vector2D.h"
#include "DxLib.h"


ElevatorRail::ElevatorRail(Position2f _pos, RailType _railType) :pos(_pos), railType(_railType)
{
	if (_railType == RailType::normalRail)
	{
		imgPath = LoadGraph("Resource/img/Rail.png");
	}
	else  if (_railType == RailType::topRail)
	{
		imgPath = LoadGraph("Resource/img/TopRail.png");
	}
	else if (_railType == RailType::bottomRail)
	{
		imgPath = LoadGraph("Resource/img/BottomRail.png");
	}
}

ElevatorRail::~ElevatorRail()
{
}

void ElevatorRail::MoveElevatorRail(float _speed)
{
	pos.x -= _speed;
}

void ElevatorRail::Draw()
{
	DrawRotaGraph(pos.x, pos.y, 1.f, 0.f, imgPath, true);
}

void ElevatorRail::Update(float _speed)
{
	MoveElevatorRail(_speed);
	Draw();
}

HitType ElevatorRail::HitCheck(Position2f _pos)
{
	HitType ret;

	//ÉuÉçÉbÉNÇ…ìñÇΩÇ¡ÇƒÇ¢ÇÈÇ©
	bool isHitTop = pos.y - blocksize < _pos.y;
	bool isHitLeft = pos.x - blocksize < _pos.x;
	bool isHitRight = pos.x + blocksize > _pos.x;
	bool isHitBottom = pos.y + blocksize > _pos.y;


	ret.isHit = isHitTop && isHitLeft && isHitRight && isHitBottom;
	ret.railType = railType;

	return ret;
}
