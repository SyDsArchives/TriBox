#include "Goal.h"
#include "ObjectParent.h"
#include "DxLib.h"
#include "Geometry.h"


Goal::Goal(Position2f _pos):pos(_pos)
{
	goalimg = DxLib::LoadGraph("Resource/img/Goal.png");
}

Goal::~Goal()
{
}

void Goal::MoveBlock(float _speed)
{
	pos.y -= _speed;
}

void Goal::Draw()
{
	DxLib::DrawRectRotaGraph2(pos.x, pos.y, 0, 0, blocksize, blocksize, blocksize / 2, blocksize / 2, 1.f, 0.f, goalimg, true, false, false);
}


Rect& Goal::GetRect()
{
	Rect blockRect;
	blockRect.SetCenter(pos.x, pos.y, blocksize, blocksize);
	return blockRect;
}

void Goal::Update(float _speed)
{
	MoveBlock(_speed);
	Draw();
}
