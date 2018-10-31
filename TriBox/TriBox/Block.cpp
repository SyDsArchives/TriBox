#include "Block.h"
#include "DxLib.h"
#include <iostream>

const int blocksize = 50;

Block::Block(Position2f _pos):pos(_pos)
{
	blockimg = DxLib::LoadGraph("Resource/img/block.png");
}


Block::~Block()
{
}

void Block::Draw()
{
	DxLib::DrawGraph(pos.x, pos.y, blockimg, true);
	//DxLib::DrawRectRotaGraph2();
}

void Block::Update()
{
	if (CheckHitKey(KEY_INPUT_A))
	{
		pos.x = pos.x - 220;
	}
	Draw();
}

bool Block::HitCheck(Position2f _pos)
{
	bool testx = pos.x - blocksize/2 < _pos.x && pos.x + blocksize/2 > _pos.x;
	bool testy = pos.y - blocksize/2 < _pos.y && pos.y + blocksize/2 > _pos.y;
	if (testx || testy)
	{
		int a = 0;
	}

	return false;
}
