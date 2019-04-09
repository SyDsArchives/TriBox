#include "Vector2D.h"
#include "Block.h"
#include "DxLib.h"
#include "Ground.h"
#include <iostream>
#include "ObjectParent.h"
#include "Ground.h"
#include "Player.h"
#include "Geometry.h"

Block::Block(Player& _player,Position2f _pos):player(_player), pos(_pos)
{
	blockimg = DxLib::LoadGraph("Resource/img/block.png");	
}

Block::~Block()
{
}

void Block::Draw()
{
	DxLib::DrawRotaGraph(pos.x, pos.y, 1.f, 0.f, blockimg, true);
	DrawPixel(pos.x, pos.y, 0xff0000);
}

void Block::MoveBlock(float _speed)
{
	pos.x -= _speed;
}

void Block::Update(float _speed)
{
	MoveBlock(_speed);
}

Position2f Block::GetBlockPos()
{
	return pos;
}

Rect& Block::GetRect()
{
	Rect blockRect;
	blockRect.SetCenter(pos.x, pos.y, blocksize, blocksize);
	return blockRect;
}



