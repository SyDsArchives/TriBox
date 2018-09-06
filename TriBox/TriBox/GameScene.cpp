#include "DxLib.h"
#include "Geometry.h"
#include "GameScene.h"
#include "BackGround.h"
#include "Player.h"
#include "Peripheral.h"

GameScene::GameScene()
{
	bg = std::make_shared<BackGround>();
	player = std::make_shared<Player>();

	normalframe = 0;
}


GameScene::~GameScene()
{
}

void GameScene::Update()
{
	Peripheral p;
	DxLib::DrawFormatString(0, 0, GetColor(255, 255, 255), "GameScene");

	bg->Update();//”wŒiŠÖŒW
	player->Update(p);//ƒvƒŒƒCƒ„[

	if (++normalframe % 60 == 0)//60f–ˆ‚Éf‚Ì‰Šú‰»‚ğs‚¤
	{
		normalframe = 0;
	}
}
