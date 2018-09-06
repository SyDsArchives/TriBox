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

	bg->Update();//�w�i�֌W
	player->Update(p);//�v���C���[

	if (++normalframe % 60 == 0)//60f����f�̏��������s��
	{
		normalframe = 0;
	}
}
