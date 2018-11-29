#include "BackGround.h"
#include "DxLib.h"
#include "Stage.h"
#include "Geometry.h"

BackGround::BackGround(Stage& _stage):normalframe(0),bgMoveSpeed(0.f), bgMoveMaxSpeed(5.f), backimgpos(Vector2f(0, 0)), backframeimgpos(Vector2f(0, 0)),stage(_stage)
{
	backimg = DxLib::LoadGraph("Resource/img/block”wŒiƒuƒ‰ƒEƒ“.png");
	back2img = DxLib::LoadGraph("Resource/img/block”wŒi‚Û‚í‚Û‚í.png");
	backframeimg = DxLib::LoadGraph("Resource/img/˜g.png");
}


BackGround::~BackGround()
{
}

void BackGround::Update(Position2f _playerPos)
{
	Position2f ppos = _playerPos;
	int x = _playerPos.x;
	
	//if (x % WindowSizeX >= WindowSizeX / 2)
	//{
	//	stage.SetStageSpeed(5.f);
	//}
	//else
	//{
	//	stage.SetStageSpeed(0.f);
	//}
	//‰æ‘œ
	DxLib::DrawExtendGraph(0,0, WindowSizeX, WindowSizeY, backimg, true);//”wŒi

	DxLib::DrawExtendGraph(backimgpos.x, backimgpos.y, backimgpos.x + WindowSizeX, backimgpos.y + WindowSizeY, back2img, true);//”wŒi
	//DxLib::DrawExtendGraph(backimgpos.x + WindowSizeX, backimgpos.y, backimgpos.x + WindowSizeX * 2, backimgpos.y + WindowSizeY, back2img, true);//”wŒi

	//DrawFormatString(0, 200, GetColor(255, 0, 0), "%d", x % WindowSizeX);
}
