#include "ResultScene.h"
#include "GameSystem.h"
#include "TitleScene.h"
#include "DxLib.h"
#include "FPS.h"



ResultScene::ResultScene()
{
}


ResultScene::~ResultScene()
{
}

void ResultScene::Update(FPS& _fps)
{
	DxLib::DrawFormatString(0, 0, GetColor(255, 255, 255), "ResultScene");
	if (CheckHitKey(KEY_INPUT_SPACE)) 
	{
		GameSystem::GameInstance().ChangeScene(new TitleScene());
	}
}
