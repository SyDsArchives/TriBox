#include "BackGround.h"
#include "DxLib.h"
#include "Stage.h"
#include "Geometry.h"

BackGround::BackGround(Stage& _stage):backimgpos(Vector2f(0, 0)), backframeimgpos(Vector2f(0, 0)),stage(_stage)
{
	backimg = DxLib::LoadGraph("Resource/img/block”wŒiƒuƒ‰ƒEƒ“.png");
	back2img = DxLib::LoadGraph("Resource/img/block”wŒi‚Û‚í‚Û‚í.png");
}


BackGround::~BackGround()
{
}

void BackGround::Update(Position2f _playerPos)
{
	Position2f ppos = _playerPos;
	int x = _playerPos.x;
	
	//‰æ‘œ
	DxLib::DrawExtendGraph(0,0, WindowSizeX, WindowSizeY, backimg, true);//”wŒi

	DxLib::DrawExtendGraph(backimgpos.x, backimgpos.y, backimgpos.x + WindowSizeX, backimgpos.y + WindowSizeY, back2img, true);//”wŒi
}
