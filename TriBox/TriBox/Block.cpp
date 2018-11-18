#include "Block.h"
#include "DxLib.h"
#include "Ground.h"
#include <iostream>
#include "ObjectParent.h"
#include "Ground.h"
#include "Player.h"

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

	if (HitCheck(player.GetPosition()).isHit_All)
	{
		player.SetOnGround(true);
		float setPosY = pos.y - blocksize;
		player.SetPosition(Vector2f(player.GetPosition().x, setPosY));
	}
}

Position2f Block::GetBlockPos()
{
	return pos;
}

ObjectHitType Block::HitCheck(Position2f _pos)
{
	ObjectHitType ret = {};

	//ÉuÉçÉbÉNÇ…ìñÇΩÇ¡ÇƒÇ¢ÇÈÇ©
	ret.isHit_Top = pos.y - blocksize < _pos.y;
	ret.isHit_Left = pos.x - blocksize < _pos.x;
	ret.isHit_Right = pos.x + blocksize > _pos.x;
	ret.isHit_Bottom = pos.y + blocksize > _pos.y;

	ret.isHit_All = ret.isHit_Top && ret.isHit_Left && ret.isHit_Right && ret.isHit_Bottom;

	return ret;
}

