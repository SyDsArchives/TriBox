#pragma once
#include "Vector2D.h"
enum class PlayerState
{
	box,
	triangle,
};

class Peripheral;
class Player
{
private:
	int triboximg;//ÉvÉåÉCÉÑÅ[
	int imgcnt;
	int changeframe;

	float playerSpeed;

	bool onceExcute;
	bool changeflg;

	PlayerState pState;

	Vector2f imgpos;
	Vector2f imgcpos;
	Vector2f triboxpos;

	void PlayerMove(Peripheral& _p);
	void PlayerAnimation();

	void PlayerMouseMove();
public:
	Player(Vector2f _pos);
	~Player();

	void SetPosition(Vector2f _pos);
	Vector2f GetPosition();

	void SetSpeed(float _speed);
	float GetSpeed();

	void Update(Peripheral& p);
};

