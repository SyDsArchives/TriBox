#pragma once
#include "Scene.h"
#include "Vector2D.h"
#include <memory>
#include <vector>

class Player;
class BackGround;
class Block;
class Stage;
class GameScene : public Scene
{
private:
	
	int normalframe;

	bool onceExcute;

	std::shared_ptr<BackGround> bg;
	std::shared_ptr<Player> player;
	std::shared_ptr<Block> block;
	std::shared_ptr<Stage> stage;

	std::vector<Player> playerLife;

public:
	GameScene();
	~GameScene();

	void Update();
};

