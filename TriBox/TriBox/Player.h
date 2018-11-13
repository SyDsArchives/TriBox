#pragma once
#include "Vector2D.h"

class Peripheral;
class Player
{
private:
	int triboximg;//�v���C���[�摜

	float playerSpeed;

	Vector2f imgpos;
	Vector2f imgcpos;
	Vector2f pos;

	//�v���C���[��ԑJ��
	void (Player::*updateFunc)(const Peripheral&);
	//�������͂������Ă��Ȃ����
	void NeutralUpdate(const Peripheral& _p);
	//�ړ����
	void MoveUpdate(const Peripheral& _p);


	//�}�E�X
	void PlayerMouseMove();
public:
	Player(Vector2f _pos);
	~Player();

	void SetPosition(Vector2f _pos);
	Vector2f GetPosition();

	void Update(Peripheral& p);
};

