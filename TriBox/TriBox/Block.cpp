#include "Block.h"
#include "DxLib.h"



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
