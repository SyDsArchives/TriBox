#pragma once
#include "Scene.h"
#include "Vector2D.h"
#include <memory>

class Player;
class BackGround;
class GameScene : public Scene
{
private:
	
	int normalframe;

	std::shared_ptr<BackGround> bg;
	std::shared_ptr<Player> player;

public:
	GameScene();
	~GameScene();

	void Update();
};

