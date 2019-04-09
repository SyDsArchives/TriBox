#pragma once
#include "Scene.h"

class FPS;
class TitleScene :
	public Scene
{
public:
	TitleScene();
	~TitleScene();

	void Update(FPS& _fps);
};

