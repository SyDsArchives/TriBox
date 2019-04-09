#include "Vector2D.h"
#include "Lava.h"
#include "ObjectParent.h"
#include "DxLib.h"
#include "Geometry.h"


Lava::Lava(Position2f _pos) :pos(_pos), riseSpeed(0.3f)
{
}

Lava::~Lava()
{
}

Rect & Lava::GetRect()
{
	Rect blockRect;
	blockRect.SetCenter(pos.x, pos.y, WindowSizeX, blocksize);
	return blockRect;
}

void Lava::Update(float _speed)
{
	Draw();
	MoveBlock(_speed);
	pos.y -= riseSpeed;
}

void Lava::MoveBlock(float _speed)
{
	pos.y -= _speed;
}

void Lava::Draw()
{
	DrawBox(0, pos.y, WindowSizeX, WindowSizeY, 0xff0000, true);
}
