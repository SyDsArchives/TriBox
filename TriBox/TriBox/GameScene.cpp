#include "DxLib.h"
#include "GameScene.h"

const int WindowSizeX = 1280;
const int WindowSizeY = 720;

GameScene::GameScene()
{
	triboximg = DxLib::LoadGraph("Resource/img/tribox.png");
	changeframe = 0;

	changeflg = false;
	boxorTriangle = true;

	triboxpos = Vector2f(WindowSizeX / 2, WindowSizeY / 2);
	imgpos = Vector2f(25, 25);
	imgcpos = Vector2f(75, 75);//125‚¸‚Â
}


GameScene::~GameScene()
{
}

void GameScene::Update()
{
	if (CheckHitKey(KEY_INPUT_W))
	{
		triboxpos.y -= 4;
	}
	else if (CheckHitKey(KEY_INPUT_S))
	{
		triboxpos.y += 4;
	}
	else if (CheckHitKey(KEY_INPUT_A))
	{
		triboxpos.x -= 4;
	}
	else if (CheckHitKey(KEY_INPUT_D))
	{
		triboxpos.x += 4;
	}


	if (CheckHitKey(KEY_INPUT_R))
	{
		if (!changeflg)
		{
			changeflg = true;
			changeframe = 0;
		}
	}
	if (changeflg)
	{
		changeframe += 1;
		if (changeframe % 20 == 0)
		{
			if (imgpos.x < 400)
			{
				imgpos.x = imgpos.x + 125;
			}
			else
			{
				changeflg = false;
			}
		}
	}


	DxLib::DrawFormatString(0, 0, GetColor(255, 255, 255), "GameScene");
	//DxLib::DrawRectRotaGraph2(triboxpos.x, triboxpos.y, imgpos.x, imgpos.y, 100, 100, imgcpos.x, imgcpos.y, 1, 0, triboximg, true, false, false);//‰Æ
	DxLib::DrawRectRotaGraph2(triboxpos.x, triboxpos.y, imgpos.x, imgpos.y, 100, 100, imgcpos.x, imgcpos.y, 1, 0, triboximg, true, false);//ŠwZ
}
