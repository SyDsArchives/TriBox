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
	player = std::make_shared<Player>(Vector2f(300, WindowSizeY - 110));
	stage = std::make_shared<Stage>(*player);
	bg = std::make_shared<BackGround>(*stage);
	
}


GameScene::~GameScene()
{
}

void GameScene::Update()
{


	Peripheral p;
	DxLib::DrawFormatString(0, 0, GetColor(255, 255, 255), "GameScene");

	bg->Update(player->GetPosition());//”wŒiŠÖŒW
	
	stage->Draw();
	
	player->Update(p);

	if (stage->GoalCheck())
	{
		GameSystem::GameInstance().ChangeScene(new ResultScene());
	}
}
