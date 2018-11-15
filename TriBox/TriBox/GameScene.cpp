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
#include "Camera.h"
#include "Ground.h"

GameScene::GameScene():onceExcute(false)
{
	ground = std::make_shared<Ground>();
	player = std::make_shared<Player>(*ground,Vector2f(300, WindowSizeY - 110));
	stage = std::make_shared<Stage>(*player, *ground);
	bg = std::make_shared<BackGround>(*stage);
	camera = std::make_shared<Camera>(*stage);
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

	camera->SetFocus(player);
	camera->Update();

	DxLib::DrawFormatString(0, 120, GetColor(255, 255, 255), "%d", ground->GetGroundLine());

	if (stage->GoalCheck())
	{
		//GameSystem::GameInstance().ChangeScene(new ResultScene());
	}
}
