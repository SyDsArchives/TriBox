#pragma once
class FPS;
class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void Update(FPS& _fps) = 0;
};

