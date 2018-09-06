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

public:
	Player();
	~Player();

	void Update(Peripheral& p);
};

