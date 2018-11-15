#include "Block.h"
#include "DxLib.h"
#include "Ground.h"
#include <iostream>
#include "ObjectParent.h"
#include "Ground.h"
#include "Player.h"

Block::Block(Player& _player,Position2f _pos):player(_player), pos(_pos), playerHit(false)
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

	if (HitCheck(player.GetPosition()))
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

bool Block::HitCheck(Position2f _pos)
{
	//ret->objectName = "block";

	//ÉuÉçÉbÉNÇ…ìñÇΩÇ¡ÇƒÇ¢ÇÈÇ©
	bool isHitTop = pos.y - blocksize < _pos.y;
	bool isHitLeft = pos.x - blocksize < _pos.x;
	bool isHitRight = pos.x + blocksize > _pos.x;
	bool isHitBottom = pos.y + blocksize > _pos.y;

	/*bool checkX = isHitLeft && isHitRight;
	bool checkY = isHitTop && isHitBottom;*/

	playerHit = isHitTop && isHitLeft && isHitRight && isHitBottom;

	return playerHit;
}

