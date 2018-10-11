#include "DxLib.h"
#include "Geometry.h"
#include "GameScene.h"
#include "BackGround.h"
#include "Player.h"
#include "Peripheral.h"

#include "Block.h"
#include "Stage.h"

GameScene::GameScene():onceExcute(false)
{
	bg = std::make_shared<BackGround>();
	player = std::make_shared<Player>(Vector2f(WindowSizeX / 2, WindowSizeY / 2));
	//block = std::make_shared<Block>(Position2f(100,100));
	stage = std::make_shared<Stage>();
}


GameScene::~GameScene()
{
}

void GameScene::Update()
{
	Peripheral p;
	DxLib::DrawFormatString(0, 0, GetColor(255, 255, 255), "GameScene");

	bg->Update();//”wŒiŠÖŒW
	
	stage->Draw();
	
	player->Update(p);
}
