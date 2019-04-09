#pragma once
#include <memory>
#include "Vector2D.h"

struct Rect;
class Scene;
class GameSystem
{
private:
	GameSystem();
	GameSystem(const GameSystem&);
	GameSystem& operator=(const GameSystem&)const;

	std::shared_ptr<Scene> scene;
	
public:
	static GameSystem& GameInstance()
	{
		static GameSystem instance;
		return instance;
	}
	~GameSystem();


	const Rect GetWindowSize();
	void ChangeScene(Scene* _scene);

	void Run();
	void End();
};

