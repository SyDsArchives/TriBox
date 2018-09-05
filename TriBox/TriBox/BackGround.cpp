#include "BackGround.h"
#include "DxLib.h"
#include "Geometry.h"


BackGround::BackGround():normalframe(0),bgMoveSpeed(0.f), bgMoveMaxSpeed(5.f), backimgpos(Vector2f(0, 0)), backframeimgpos(Vector2f(0, 0))
{
	backimg = DxLib::LoadGraph("Resource/img/blockîwåi.png");
	backframeimg = DxLib::LoadGraph("Resource/img/òg.png");
}


BackGround::~BackGround()
{
}

void BackGround::Update()
{
	//îwåiÇÃà íuèâä˙âª
	if (backimgpos.x <= -WindowSizeX)
	{
		backimgpos.x = 0;
	}
	if (backframeimgpos.x <= -WindowSizeX)
	{
		backframeimgpos.x = 0;
	}

	//îwåiÇÃà⁄ìÆë¨ìx
	if (normalframe == 59)
	{
		if (bgMoveSpeed <= bgMoveMaxSpeed)//5Ç‹Ç≈
		{
			bgMoveSpeed += 0.2;
		}
	}

	//îwåiÇÃà⁄ìÆ
	backimgpos.x -= bgMoveSpeed;
	backframeimgpos.x -= (bgMoveSpeed / 2);

	//âÊëú
	DxLib::DrawExtendGraph(backimgpos.x, backimgpos.y, backimgpos.x + WindowSizeX, backimgpos.y + WindowSizeY, backimg, true);//îwåi
	DxLib::DrawExtendGraph(backimgpos.x + WindowSizeX, backimgpos.y, backimgpos.x + WindowSizeX * 2, backimgpos.y + WindowSizeY, backimg, true);//îwåi

	DxLib::DrawExtendGraph(backframeimgpos.x, backframeimgpos.y, backframeimgpos.x + WindowSizeX, backframeimgpos.y + WindowSizeY, backframeimg, true);//òg
	DxLib::DrawExtendGraph(backframeimgpos.x + WindowSizeX, backframeimgpos.y, backframeimgpos.x + WindowSizeX * 2, backframeimgpos.y + WindowSizeY, backframeimg, true);//òg

	if (++normalframe % 60 == 0)//60fñàÇ…fÇÃèâä˙âªÇçsÇ§
	{
		normalframe = 0;
	}
}
