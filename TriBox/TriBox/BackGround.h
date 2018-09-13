#pragma once
#include "Vector2D.h"
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

public:
	BackGround();
	~BackGround();
	void Update();
};

