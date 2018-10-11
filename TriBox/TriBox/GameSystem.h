#pragma once
#include <memory>
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


	int GetWindowSize(char num);
	void ChangeScene(Scene* _scene);

	void Run();
	void End();
};

