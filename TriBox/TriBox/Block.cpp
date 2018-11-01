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
	//DxLib::DrawGraph(pos.x, pos.y, blockimg, true);
	DxLib::DrawRectRotaGraph2(pos.x, pos.y, 0, 0, blocksize, blocksize, blocksize / 2, blocksize / 2, 1.f, 0.f, blockimg, true, false, false);
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
	bool checkX = pos.x - blocksize/2 < _pos.x && pos.x + blocksize/2 > _pos.x;
	bool checkY = pos.y - blocksize/2 < _pos.y && pos.y + blocksize/2 > _pos.y;

	return checkX && checkY;
}
