#include "DxLib.h"
#include "Geometry.h"
#include "GameScene.h"
#include "BackGround.h"
#include "Player.h"
#include "Peripheral.h"

#include "Block.h"

GameScene::GameScene():onceExcute(false)
{
	bg = std::make_shared<BackGround>();
	player = std::make_shared<Player>(Vector2f(WindowSizeX / 2, WindowSizeY / 2));
	block = std::make_shared<Block>();

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

	bg->Update();//背景関係
	int plcnt = 0;
	bool frontorback = false;//true前false後ろ
	Vector2f backrowPos = playerLife.at(0).GetPosition();
	
	block->Draw();
	
	player->Update(p);

	if (++normalframe % 60 == 0)//60f毎にfの初期化を行う
	{
		normalframe = 0;
	}
}
