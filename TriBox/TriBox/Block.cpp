#include "Block.h"
#include "DxLib.h"
#include "Ground.h"
#include <iostream>
#include "ObjectParent.h"
#include "Ground.h"

Block::Block(Ground& _ground,Position2f _pos):ground(_ground),pos(_pos)
{
	blockimg = DxLib::LoadGraph("Resource/img/block.png");	
}


Block::~Block()
{
}

void Block::Draw()
{
	DxLib::DrawRectRotaGraph2(pos.x, pos.y, 0, 0, blocksize, blocksize, blocksize / 2, blocksize / 2, 1.f, 0.f, blockimg, true, false, false);
}

void Block::MoveBlock(float _speed)
{
	pos.x -= _speed;
	DrawFormatString(0, 30, GetColor(255, 0, 0),"%d", pos.x);
}

void Block::Update(float _speed)
{
	MoveBlock(_speed);
}

Position2f Block::GetBlockPos()
{
	return pos;
}

bool Block::HitCheck(Position2f _pos)
{
	//返り値用変数
	bool ret;
	//ret->objectName = "block";

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

