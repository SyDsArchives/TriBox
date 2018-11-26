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

ObjectHitType Block::HitCheck(Position2f _pos)
{
	ObjectHitType ret = {};

	//ブロックに当たっているか
	ret.isHit_Top = pos.y - blocksize < _pos.y;
	ret.isHit_Left = pos.x - blocksize < _pos.x;
	ret.isHit_Right = pos.x + blocksize > _pos.x;
	ret.isHit_Bottom = pos.y + blocksize > _pos.y;

	ret.isHit_All = ret.isHit_Top && ret.isHit_Left && ret.isHit_Right && ret.isHit_Bottom;

	return ret;
}

ObjectRectHitType Block::HitRect(Position2f _pos)
{
	ObjectRectHitType ret = {};

	Rect blockRect;
	blockRect.SetCenter(pos.x, pos.y, blocksize, blocksize);

	//矩形当たり判定
	auto top = blockRect.Top();
	auto left = blockRect.Left();
	auto right = blockRect.Right();
	auto bottom = blockRect.Bottom();

	ret.isHit_Top = blockRect.Top() < _pos.y;
	ret.isHit_Left = blockRect.Left() < _pos.x;
	ret.isHit_Right = blockRect.Right() > _pos.x;
	ret.isHit_Bottom = blockRect.Bottom() > _pos.y;

	//ret.isHit_All = ret.isHit_Top && ret.isHit_Left && ret.isHit_Right && ret.isHit_Bottom;

	return ret;
}

