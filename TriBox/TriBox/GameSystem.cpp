#include "GameSystem.h"
#include "DxLib.h"
#include "Scene.h"
#include "GameScene.h"
#include "Geometry.h"

#include "TitleScene.h"



GameSystem::GameSystem()
{
}


GameSystem::~GameSystem()
{
}

const Rect GameSystem::GetWindowSize()
{
	Rect ret(0, WindowSizeX, 0, WindowSizeY);
	return ret;
}

void GameSystem::ChangeScene(Scene* _scene)
{
	scene.reset(_scene);
}

void GameSystem::Run()
{
	DxLib::ChangeWindowMode(true);
	DxLib::SetGraphMode(WindowSizeX, WindowSizeY, 32);

	if (DxLib::DxLib_Init() == -1)
	{
		return;
	}
	SetWindowText(_T("TriBox"));
	SetDrawScreen(DX_SCREEN_BACK);

	ChangeScene(new GameScene());

	while (DxLib::ProcessMessage() == 0)
	{
		ClearDrawScreen();
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		scene->Update();
		DxLib::ScreenFlip();
	}
	
}

void GameSystem::End() {
	DxLib::DxLib_End();
}