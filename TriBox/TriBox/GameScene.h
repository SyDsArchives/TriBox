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
	int triboximg;//ÉvÉåÉCÉÑÅ[
	int backimg;//îwåi
	int backframeimg;//òg

	int changeframe;
	int normalframe;
	int imgcnt;

	float playerSpeed;
	float bgMoveSpeed;
	float bgMoveMaxSpeed;

	bool onceExcute;
	bool changeflg;

	PlayerState pState;

	Vector2f imgpos;
	Vector2f imgcpos;
	Vector2f triboxpos;
	Vector2f backimgpos;
	Vector2f backframeimgpos;


public:
	GameScene();
	~GameScene();

	void Update();
};

