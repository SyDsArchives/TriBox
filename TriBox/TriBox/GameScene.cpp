#include "DxLib.h"
#include "Geometry.h"
#include "GameScene.h"
#include "BackGround.h"
#include "Player.h"
#include "Peripheral.h"
#include "GameSystem.h"
#include "ResultScene.h"

#include "Block.h"
#include "Stage.h"
#include "Goal.h"

GameScene::GameScene():onceExcute(false)
{
	bg = std::make_shared<BackGround>();
	player = std::make_shared<Player>(Vector2f(300, WindowSizeY - 110));
	stage = std::make_shared<Stage>(*player);
	
}


GameScene::~GameScene()
{
}

void GameScene::Update()
{


	Peripheral p;
	DxLib::DrawFormatString(0, 0, GetColor(255, 255, 255), "GameScene");

	bg->Update();//�w�i�֌W
	
	stage->Draw();
	
	player->Update(p);

	if (stage->GoalCheck())
	{
		GameSystem::GameInstance().ChangeScene(new ResultScene());
	}
}
