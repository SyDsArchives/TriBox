#include "TitleScene.h"
#include "DxLib.h"
#include "GameSystem.h"
#include "GameScene.h"



TitleScene::TitleScene()
{
}


TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	DxLib::DrawFormatString(0, 0, GetColor(255, 255, 255), "TitleScene");
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		GameSystem::GameInstance().ChangeScene(new GameScene());
	}
}
