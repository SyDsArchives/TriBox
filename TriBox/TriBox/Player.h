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
	int triboximg;//�v���C���[�摜

	float lastTime;
	float playerSpeed;
	float jumpInertia;//�W�����v���̊���
	
	bool aerialFlag;//true:�󒆏㏸��� false:�󒆉��~���

	Vector2f imgpos;
	Vector2f imgcpos;
	Vector2f pos;

	PlayerDirection direction;

	//�v���C���[��ԑJ��
	void (Player::*updateFunc)(const Peripheral&);
	//�������͂������Ă��Ȃ����
	void NeutralUpdate(const Peripheral& _p);
	//�ړ����
	void MoveUpdate(const Peripheral& _p);
	//�W�����v���
	void AerialUpdate(const Peripheral& _p);

	void PlayerMoveLimit();


	//�}�E�X
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

