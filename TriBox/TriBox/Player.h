#pragma once
#include "Vector2D.h"

enum class PlayerDirection
{
	none,
	left,
	right,
};

class Ground;
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

	Ground& ground;

	//�v���C���[��ԑJ��
	void (Player::*updateFunc)(const Peripheral&);
	//�������͂������Ă��Ȃ����
	void NeutralUpdate(const Peripheral& _p);
	//�ړ����
	void MoveUpdate(const Peripheral& _p);
	//�W�����v���
	void AerialUpdate(const Peripheral& _p);

	//�}�E�X
	void PlayerMouseMove();
public:
	Player(Ground& _ground,Vector2f _pos);
	~Player();

	void SetPosition(Vector2f _pos);
	Vector2f GetPosition();
	float GetSpeed() { return playerSpeed; };
	PlayerDirection GetPlayerDirection() { return direction; };
	void PlayerMoveLimit(bool excuteFlag);

	void Update(Peripheral& p);
};

