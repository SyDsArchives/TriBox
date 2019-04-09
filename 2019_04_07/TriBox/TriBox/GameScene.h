#pragma once
#include "Scene.h"
#include <memory>
#include <vector>
#include "Vector2D.h"

class Ground;
class Camera;
class Player;
class BackGround;
class Block;
class Stage;
class FPS;
class GameScene : public Scene
{
private:
	
	int normalframe;

	bool onceExcute;

	std::shared_ptr<BackGround> bg;
	std::shared_ptr<Player> player;
	std::shared_ptr<Block> block;
	std::shared_ptr<Stage> stage;
	std::shared_ptr<Camera> camera;
	std::shared_ptr<Ground> ground;

	std::vector<Player> playerLife;

public:
	GameScene();
	~GameScene();

	void Update(FPS& _fps);
};

