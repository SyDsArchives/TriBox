#include "GameSystem.h"
#include "DxLib.h"
#include "Scene.h"
#include "GameScene.h"
#include "Geometry.h"


GameSystem::GameSystem()
{
}


GameSystem::~GameSystem()
{
}

int GameSystem::GetWindowSize(char num)
{
	if (num == 'x')
	{
		return WindowSizeX;
	}
	else if (num == 'y')
	{
		return WindowSizeY;
	}
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
