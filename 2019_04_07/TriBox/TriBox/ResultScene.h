#pragma once
#include "Scene.h"
class FPS;
class ResultScene :
	public Scene
{
public:
	ResultScene();
	~ResultScene();

	void Update(FPS& fps);
};

