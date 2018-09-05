#include "DxLib.h"
#include "GameScene.h"

const int WindowSizeX = 1280;
const int WindowSizeY = 720;

GameScene::GameScene() : onceExcute(false), imgcnt(0)
{
	triboximg = DxLib::LoadGraph("Resource/img/tribox.png");
	backimg = DxLib::LoadGraph("Resource/img/block�w�i.png");
	backframeimg = DxLib::LoadGraph("Resource/img/�g.png");
	changeframe = 0;
	normalframe = 0;

	changeflg = false;
	pState = PlayerState::box;
	playerSpeed = 6.f;

	bgMoveSpeed = 0.f;
	bgMoveMaxSpeed = 5.f;

	triboxpos = Vector2f(WindowSizeX / 2, WindowSizeY / 2);
	backimgpos = Vector2f(0, 0);
	backframeimgpos = Vector2f(0, 0);

	imgpos = Vector2f(25, 25);
	imgcpos = Vector2f(75, 75);//125����
}


GameScene::~GameScene()
{
}

void GameScene::Update()
{
	DxLib::DrawFormatString(0, 0, GetColor(255, 255, 255), "GameScene");
	DxLib::DrawFormatString(0, 25, GetColor(255, 255, 255), "%d", pState);

	//�v���C���[�̈ړ�
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

#pragma region --------------------�v���C���[�A�j���[�V����(��)--------------------
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
				if (imgcnt == 0)//�v���C���[�C���[�W1�i��
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

				if (imgcnt == 1)//�v���C���[�C���[�W2�i��
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
				if (imgcnt == 0)//�v���C���[�C���[�W1�i��
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

				if (imgcnt == 1)//�v���C���[�C���[�W2�i��
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

	//�w�i�̈ʒu������
	if (backimgpos.x <= -WindowSizeX)
	{
		backimgpos.x = 0;
	}
	if (backframeimgpos.x <= -WindowSizeX)
	{
		backframeimgpos.x = 0;
	}

	//�w�i�̈ړ����x
	if (normalframe == 59)
	{
		if (bgMoveSpeed <= bgMoveMaxSpeed)//5�܂�
		{
			bgMoveSpeed += 0.5;
		}
	}

	//�w�i�̈ړ�
	backimgpos.x -= bgMoveSpeed;
	backframeimgpos.x -= (bgMoveSpeed / 2);

	//�摜
	DxLib::DrawExtendGraph(backimgpos.x, backimgpos.y, backimgpos.x + WindowSizeX, backimgpos.y + WindowSizeY, backimg, true);//�w�i
	DxLib::DrawExtendGraph(backimgpos.x + WindowSizeX, backimgpos.y, backimgpos.x + WindowSizeX * 2, backimgpos.y + WindowSizeY, backimg, true);//�w�i
	DxLib::DrawExtendGraph(backframeimgpos.x, backframeimgpos.y, backframeimgpos.x + WindowSizeX, backframeimgpos.y + WindowSizeY, backframeimg, true);//�g
	DxLib::DrawExtendGraph(backframeimgpos.x + WindowSizeX, backframeimgpos.y, backframeimgpos.x + WindowSizeX * 2, backframeimgpos.y + WindowSizeY, backframeimg, true);//�g


	//DxLib::DrawRectRotaGraph2(triboxpos.x, triboxpos.y, imgpos.x, imgpos.y, 100, 100, imgcpos.x, imgcpos.y, 1, 0, triboximg, true, false, false);//��,�v���C���[
	DxLib::DrawRectRotaGraph2(triboxpos.x, triboxpos.y, imgpos.x, imgpos.y, 100, 100, imgcpos.x, imgcpos.y, 0.5, 0, triboximg, true, false);//�w�Z,�v���C���[


	if (++normalframe % 60 == 0)//60f����f�̏��������s��
	{
		normalframe = 0;
	}
}
