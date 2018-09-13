#include "BackGround.h"
#include "DxLib.h"
#include "Geometry.h"


BackGround::BackGround():normalframe(0),bgMoveSpeed(0.f), bgMoveMaxSpeed(5.f), backimgpos(Vector2f(0, 0)), backframeimgpos(Vector2f(0, 0))
{
	backimg = DxLib::LoadGraph("Resource/img/block”wŒiƒuƒ‰ƒEƒ“.png");
	back2img = DxLib::LoadGraph("Resource/img/block”wŒi‚Û‚í‚Û‚í.png");
	backframeimg = DxLib::LoadGraph("Resource/img/˜g.png");
}


BackGround::~BackGround()
{
}

void BackGround::Update()
{
	//”wŒi‚ÌˆÊ’u‰Šú‰»
	if (backimgpos.x <= -WindowSizeX)
	{
		backimgpos.x = 0;
	}
	if (backframeimgpos.x <= -WindowSizeX)
	{
		backframeimgpos.x = 0;
	}

	//”wŒi‚ÌˆÚ“®‘¬“x
	if (normalframe == 59)
	{
		if (bgMoveSpeed <= bgMoveMaxSpeed)//5‚Ü‚Å
		{
			bgMoveSpeed += 0.2;
		}
	}

	//”wŒi‚ÌˆÚ“®
	backimgpos.x -= bgMoveSpeed;
	backframeimgpos.x -= (bgMoveSpeed / 2);

	//‰æ‘œ
	DxLib::DrawExtendGraph(0,0, WindowSizeX, WindowSizeY, backimg, true);//”wŒi

	DxLib::DrawExtendGraph(backimgpos.x, backimgpos.y, backimgpos.x + WindowSizeX, backimgpos.y + WindowSizeY, back2img, true);//”wŒi
	DxLib::DrawExtendGraph(backimgpos.x + WindowSizeX, backimgpos.y, backimgpos.x + WindowSizeX * 2, backimgpos.y + WindowSizeY, back2img, true);//”wŒi

	DxLib::DrawExtendGraph(backframeimgpos.x, backframeimgpos.y, backframeimgpos.x + WindowSizeX, backframeimgpos.y + WindowSizeY, backframeimg, true);//˜g
	DxLib::DrawExtendGraph(backframeimgpos.x + WindowSizeX, backframeimgpos.y, backframeimgpos.x + WindowSizeX * 2, backframeimgpos.y + WindowSizeY, backframeimg, true);//˜g

	if (++normalframe % 60 == 0)//60f–ˆ‚Éf‚Ì‰Šú‰»‚ğs‚¤
	{
		normalframe = 0;
	}
}
