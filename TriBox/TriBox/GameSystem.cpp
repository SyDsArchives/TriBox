#include "GameSystem.h"
#include "DxLib.h"
#include "Scene.h"
#include "GameScene.h"
#include "Geometry.h"

#include "TitleScene.h"

#include "FPS.h"



GameSystem::GameSystem()
{
}


GameSystem::~GameSystem()
{
}

const Rect GameSystem::GetWindowSize()
{
	Rect ret(0, WindowSizeY, 0, WindowSizeX);
	return ret;
}

void GameSystem::ChangeScene(Scene* _scene)
{
	scene.reset(_scene);
}

void GameSystem::Run()
{
	FPS fps;
	DxLib::ChangeWindowMode(true);
	DxLib::SetGraphMode(WindowSizeX, WindowSizeY, 32);
	
	DxLib::SetWindowPosition(0, 0);

	if (DxLib::DxLib_Init() == -1)
	{
		return;
	}
	//SetWindowText(_T("TriBox"));
	SetWindowText(_T("2DAC"));
	SetDrawScreen(DX_SCREEN_BACK);

	ChangeScene(new GameScene());

	while (DxLib::ProcessMessage() == 0)
	{
		ClearDrawScreen();
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		fps.Update();
		scene->Update(fps);

		DxLib::ScreenFlip();
	}
	
}

void GameSystem::End() {
	DxLib::DxLib_End();
}