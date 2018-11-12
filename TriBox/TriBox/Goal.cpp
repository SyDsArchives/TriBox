#include "Goal.h"
#include "ObjectParent.h"
#include "DxLib.h"


Goal::Goal(Position2f _pos):pos(_pos)
{
	goalimg = DxLib::LoadGraph("Resource/img/Goal.png");
}

Goal::~Goal()
{
}

void Goal::MoveBlock(float _speed)
{
	pos.x -= _speed;
}

bool Goal::HitCheck(Position2f _pos)
{
	//返り値用変数
	bool ret;

	//ブロックに当たっているか
	bool isHitTop = pos.y - blocksize / 2 < _pos.y;
	bool isHitLeft = pos.x - blocksize / 2 < _pos.x;
	bool isHitRight = pos.x + blocksize > _pos.x;
	bool isHitBottom = pos.y + blocksize > _pos.y;

	bool checkX = isHitLeft && isHitRight;
	bool checkY = isHitTop && isHitBottom;

	ret = isHitTop && isHitLeft && isHitRight && isHitBottom;

	return ret;
}

void Goal::Draw()
{
	DxLib::DrawRectRotaGraph2(pos.x, pos.y, 0, 0, blocksize, blocksize, blocksize / 2, blocksize / 2, 1.f, 0.f, goalimg, true, false, false);
}


void Goal::Update(float _speed)
{
	MoveBlock(_speed);
	Draw();
}
