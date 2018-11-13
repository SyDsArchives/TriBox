#pragma once
#include "Vector2D.h"

class Peripheral;
class Player
{
private:
	int triboximg;//プレイヤー画像

	float playerSpeed;

	Vector2f imgpos;
	Vector2f imgcpos;
	Vector2f pos;

	//プレイヤー状態遷移
	void (Player::*updateFunc)(const Peripheral&);
	//何も入力が入っていない状態
	void NeutralUpdate(const Peripheral& _p);
	//移動状態
	void MoveUpdate(const Peripheral& _p);


	//マウス
	void PlayerMouseMove();
public:
	Player(Vector2f _pos);
	~Player();

	void SetPosition(Vector2f _pos);
	Vector2f GetPosition();

	void Update(Peripheral& p);
};

