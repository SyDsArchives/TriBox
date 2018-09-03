#pragma once
#include "Scene.h"
#include "Vector2D.h"
class GameScene :
	public Scene
{
private:
	int triboximg;
	int changeframe;

	bool changeflg;
	bool boxorTriangle;

	Vector2f imgpos;
	Vector2f imgcpos;
	Vector2f triboxpos;
public:
	GameScene();
	~GameScene();

	void Update();
};

