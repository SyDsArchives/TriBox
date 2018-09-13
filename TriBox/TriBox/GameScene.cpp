#include "DxLib.h"
#include "Geometry.h"
#include "GameScene.h"
#include "BackGround.h"
#include "Player.h"
#include "Peripheral.h"

GameScene::GameScene():onceExcute(false)
{
	bg = std::make_shared<BackGround>();
	player = std::make_shared<Player>(Vector2f(WindowSizeX / 2, WindowSizeY / 2));

	normalframe = 0;
}


GameScene::~GameScene()
{
}

void GameScene::Update()
{
	if (!onceExcute)
	{
		for (int i = 0; i < 3; ++i)
		{
			playerLife.push_back(Player(Vector2f(WindowSizeX / 2, WindowSizeY / 2)));
		}
		onceExcute = true;
	}

	Peripheral p;
	DxLib::DrawFormatString(0, 0, GetColor(255, 255, 255), "GameScene");

	bg->Update();//�w�i�֌W
	int plcnt = 0;
	bool frontorback = false;//true�Ofalse���
	Vector2f backrowPos = playerLife.at(0).GetPosition();
	//for (auto& pl : playerLife)
	//{
	//	//�擪
	//	if (plcnt == 0)
	//	{
	//		pl.Update(p);//�v���C���[
	//	}
	//	else//����ȊO
	//	{
	//		if (normalframe % 10 == 0)
	//		{
	//			backrowPos = Vector2f(playerLife.at(plcnt - 1).GetPosition().x, playerLife.at(plcnt - 1).GetPosition().y);
	//			pl.SetPosition(backrowPos);
	//			pl.Update(p);//�v���C���[
	//		}
	//		
	//	}
	//	pl.Update(p);//�v���C���[
	//	++plcnt;
	//}
	
	player->Update(p);

	if (++normalframe % 60 == 0)//60f����f�̏��������s��
	{
		normalframe = 0;
	}
}
