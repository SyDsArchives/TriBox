#include "Block.h"
#include "DxLib.h"



Block::Block()
{
	blockimg = DxLib::LoadGraph("Resource/img/block.png");
}


Block::~Block()
{
}

void Block::Draw()
{
	DxLib::DrawGraph(100, 100, blockimg, true);
}
