#include "Block.h"
#include "DxLib.h"
#include <iostream>


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
}

void Block::Update()
{
	if (CheckHitKey(KEY_INPUT_A))
	{
		pos.x = pos.x - 220;
	}
	Draw();
}
