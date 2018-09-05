#pragma once
#include "Scene.h"
#include "Vector2D.h"
#include <memory>

enum class PlayerState
{
	box,
	triangle,
};

class BackGround;
class GameScene : public Scene
{
private:
	int triboximg;//ÉvÉåÉCÉÑÅ[

	int changeframe;
	int normalframe;
	int imgcnt;

	float playerSpeed;

	bool onceExcute;
	bool changeflg;

	PlayerState pState;

	Vector2f imgpos;
	Vector2f imgcpos;
	Vector2f triboxpos;

	std::shared_ptr<BackGround> bg;

public:
	GameScene();
	~GameScene();

	void Update();
};

