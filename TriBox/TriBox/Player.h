#pragma once
#include "Vector2D.h"

enum class PlayerDirection
{
	none,
	left,
	right,
};


class Peripheral;
class Player
{
private:
	int triboximg;//プレイヤー画像

	float lastTime;
	float playerSpeed;
	float jumpInertia;//ジャンプ中の慣性
	
	bool aerialFlag;//true:空中上昇状態 false:空中下降状態

	Vector2f imgpos;
	Vector2f imgcpos;
	Vector2f pos;

	PlayerDirection direction;

	//プレイヤー状態遷移
	void (Player::*updateFunc)(const Peripheral&);
	//何も入力が入っていない状態
	void NeutralUpdate(const Peripheral& _p);
	//移動状態
	void MoveUpdate(const Peripheral& _p);
	//ジャンプ状態
	void AerialUpdate(const Peripheral& _p);

	void PlayerMoveLimit();


	//マウス
	void PlayerMouseMove();
public:
	Player(Vector2f _pos);
	~Player();

	void SetPosition(Vector2f _pos);
	Vector2f GetPosition();
	float GetSpeed() { return playerSpeed; };
	PlayerDirection GetPlayerDirection() { return direction; };

	void Update(Peripheral& p);
};

