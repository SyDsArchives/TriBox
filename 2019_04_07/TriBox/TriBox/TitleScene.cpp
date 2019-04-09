#include "TitleScene.h"
#include "DxLib.h"
#include "GameSystem.h"
#include "GameScene.h"
#include "FPS.h"


TitleScene::TitleScene()
{
}


TitleScene::~TitleScene()
{
}

void TitleScene::Update(FPS& _fps)
{
	DxLib::DrawFormatString(0, 0, GetColor(255, 255, 255), "TitleScene");
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		GameSystem::GameInstance().ChangeScene(new GameScene());
	}
}
