#pragma once
#include "Vector2D.h"
class BackGround
{
private:
	int normalframe;
	int backimg;//�w�i
	int back2img;
	int backframeimg;//�g

	float bgMoveSpeed;
	float bgMoveMaxSpeed;

	Vector2f backimgpos;
	Vector2f backframeimgpos;

public:
	BackGround();
	~BackGround();
	void Update();
};

