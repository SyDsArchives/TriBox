#pragma once
#include "Scene.h"
#include "Vector2D.h"

enum class PlayerState
{
	box,
	triangle,
};

class GameScene :
	public Scene
{
private:
	int triboximg;
	int changeframe;
	int imgcnt;

	bool onceExcute;
	bool changeflg;

	PlayerState pState;

	Vector2f imgpos;
	Vector2f imgcpos;
	Vector2f triboxpos;
public:
	GameScene();
	~GameScene();

	void Update();
};

