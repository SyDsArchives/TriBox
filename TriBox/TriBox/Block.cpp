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

HitObjectData Block::HitCheck(Position2f _pos)
{
	//返り値用変数
	HitObjectData ret;
	ret.objectName = "block";

	//ブロックに当たっているか
	bool isHitTop = pos.y - blocksize / 2 < _pos.y;
	bool isHitLeft = pos.x - blocksize / 2 < _pos.x;
	bool isHitRight = pos.x + blocksize / 2 > _pos.x;
	bool isHitBottom = pos.y + blocksize / 2 > _pos.y;

	bool checkX = isHitLeft && isHitRight;
	bool checkY = isHitTop && isHitBottom;

	ret.isHit = isHitTop && isHitLeft && isHitRight && isHitBottom;
		
	return ret;
}

