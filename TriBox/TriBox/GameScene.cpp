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
#include "FPS.h"

GameScene::GameScene():onceExcute(false)
{
	ground = std::make_shared<Ground>();
	player = std::make_shared<Player>(Vector2f(300, WindowSizeY - 150));
	stage = std::make_shared<Stage>(*player);
	bg = std::make_shared<BackGround>(*stage);
	camera = std::make_shared<Camera>(*stage);
}


GameScene::~GameScene()
{
}

void GameScene::Update(FPS& _fps)
{
	Peripheral p;
	//DxLib::DrawFormatString(0, 0, GetColor(255, 255, 255), "GameScene");

	//背景関係
	bg->Update(player->GetPosition());
	
	//ステージオブジェクト管理
	stage->Update();

	//プレイヤー
	player->Update(p, _fps);

	//カメラ関係
	camera->SetFocus(player);
	camera->Update();

	//画面遷移
	if (stage->GoalCheck() || player->IsDead(stage->GetStageUnderLine()))
	{
		GameSystem::GameInstance().ChangeScene(new ResultScene());
	}
}
