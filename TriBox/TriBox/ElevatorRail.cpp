#include "ElevatorRail.h"
#include "Vector2D.h"
#include "DxLib.h"


ElevatorRail::ElevatorRail(Position2f _pos, RailType _railType) :pos(_pos)
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

void ElevatorRail::MoveBlock(float _speed)
{
	pos.x -= _speed;
}

void ElevatorRail::Draw()
{
	DrawRotaGraph(pos.x, pos.y, 1.f, 0.f, imgPath, true);
}

void ElevatorRail::Update(float _speed)
{
	MoveBlock(_speed);
	Draw();
}
