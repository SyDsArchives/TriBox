#pragma once
#include "Vector2D.h"

class Stage;
class BackGround
{
private:
	int normalframe;
	int backimg;//îwåi
	int back2img;
	int backframeimg;//òg

	float bgMoveSpeed;
	float bgMoveMaxSpeed;

	Vector2f backimgpos;
	Vector2f backframeimgpos;

	Stage& stage;

public:
	BackGround(Stage& _stage);
	~BackGround();
	void Update(Position2f _playerPos);
};

