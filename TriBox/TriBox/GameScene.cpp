#include "DxLib.h"
#include "Geometry.h"
#include "GameScene.h"
#include "BackGround.h"

GameScene::GameScene() : onceExcute(false), imgcnt(0)
{
	bg = std::make_shared<BackGround>();

	triboximg = DxLib::LoadGraph("Resource/img/tribox.png");

	changeframe = 0;
	normalframe = 0;

	changeflg = false;
	pState = PlayerState::box;
	playerSpeed = 6.f;

	triboxpos = Vector2f(WindowSizeX / 2, WindowSizeY / 2);
	
	imgpos = Vector2f(25, 25);
	imgcpos = Vector2f(75, 75);//125ずつ

}


GameScene::~GameScene()
{
}

void GameScene::Update()
{
	DxLib::DrawFormatString(0, 0, GetColor(255, 255, 255), "GameScene");
	DxLib::DrawFormatString(0, 25, GetColor(255, 255, 255), "%d", pState);

	bg->Update();//背景関係

	//プレイヤーの移動
	if (CheckHitKey(KEY_INPUT_W))
	{
		triboxpos.y -= playerSpeed;
	}
	else if (CheckHitKey(KEY_INPUT_S))
	{
		triboxpos.y += playerSpeed;
	}
	else if (CheckHitKey(KEY_INPUT_A))
	{
		triboxpos.x -= playerSpeed;
	}
	else if (CheckHitKey(KEY_INPUT_D))
	{
		triboxpos.x += playerSpeed;
	}


	if (CheckHitKey(KEY_INPUT_R))
	{
		if (!changeflg)
		{
			changeflg = true;
			changeframe = 0;
		}
	}

#pragma region --------------------プレイヤーアニメーション(仮)--------------------
	if (changeflg)
	{
		if (imgcnt == 2)
		{
			changeflg = false;
			onceExcute = false;
			imgcnt = 0;
		}

		changeframe += 1;
		if (changeframe % 3 == 0)
		{
			if (pState == PlayerState::box)
			{
				if (imgcnt == 0)//プレイヤーイメージ1段目
				{
					if (!onceExcute)
					{
						imgpos.x = 25;
						imgpos.y = 25;
						onceExcute = true;
					}
					if (imgpos.x < 400)
					{
						imgpos.x = imgpos.x + 125;
					}
					else
					{
						imgcnt = 1;
						onceExcute = false;
					}
				}

				if (imgcnt == 1)//プレイヤーイメージ2段目
				{
					if (!onceExcute)
					{
						imgpos.x = 25;
						imgpos.y = 150;
						onceExcute = true;
					}
					if (imgpos.x < 400)
					{
						imgpos.x = imgpos.x + 125;
					}
					else
					{
						imgcnt = 2;
						pState = PlayerState::triangle;
					}
				}
			}
			else if (pState == PlayerState::triangle)
			{
				if (imgcnt == 0)//プレイヤーイメージ1段目
				{
					if (!onceExcute)
					{
						imgpos.x = 400;
						imgpos.y = 150;
						onceExcute = true;
					}
					if (imgpos.x > 25)
					{
						imgpos.x = imgpos.x - 125;
					}
					else
					{
						imgcnt = 1;
						onceExcute = false;
					}
				}

				if (imgcnt == 1)//プレイヤーイメージ2段目
				{
					if (!onceExcute)
					{
						imgpos.x = 400;
						imgpos.y = 25;
						onceExcute = true;
					}
					if (imgpos.x > 25)
					{
						imgpos.x = imgpos.x - 125;
					}
					else
					{
						imgcnt = 2;
						pState = PlayerState::box;
					}
				}
			}
		}
	}
#pragma endregion

	DxLib::DrawRectRotaGraph2(triboxpos.x, triboxpos.y, imgpos.x, imgpos.y, 100, 100, imgcpos.x, imgcpos.y, 0.5, 0, triboximg, true, false, false);//家,プレイヤー

	if (++normalframe % 60 == 0)//60f毎にfの初期化を行う
	{
		normalframe = 0;
	}
}
