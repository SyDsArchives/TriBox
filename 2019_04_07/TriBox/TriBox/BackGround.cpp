#include "BackGround.h"
#include "DxLib.h"
#include "Stage.h"
#include "Geometry.h"

BackGround::BackGround(Stage& _stage):backimgpos(Vector2f(0, 0)), backframeimgpos(Vector2f(0, 0)),stage(_stage)
{
	backimg = DxLib::LoadGraph("Resource/img/block�w�i�u���E��.png");
	back2img = DxLib::LoadGraph("Resource/img/block�w�i�ۂ�ۂ�.png");
}


BackGround::~BackGround()
{
}

void BackGround::Update(Position2f _playerPos)
{
	Position2f ppos = _playerPos;
	int x = _playerPos.x;
	
	//�摜
	DxLib::DrawExtendGraph(0,0, WindowSizeX, WindowSizeY, backimg, true);//�w�i

	DxLib::DrawExtendGraph(backimgpos.x, backimgpos.y, backimgpos.x + WindowSizeX, backimgpos.y + WindowSizeY, back2img, true);//�w�i
}
