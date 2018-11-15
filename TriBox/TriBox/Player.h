#pragma once
#include "Vector2D.h"

//�v���C���[�̈ړ�����������
enum class PlayerDirection
{
	none,//�����ĂȂ�
	left,//���ړ�
	right,//�E�ړ�
};

class Peripheral;
class Player
{
private:
	int playerImg;//�v���C���[�摜

	float playerSpeed;//�ړ����x
	float jumpInertia;//�W�����v���̊���
	float gravity;//�d��
	float jumpPower;//�W�����v��
	float lastTime;//�W�����v�����u�Ԃ̎���
	
	bool aerialFlag;//true:�󒆏㏸��� false:�󒆉��~���
	bool onGround;//�n�ʂɂ��邩�ǂ���

	Vector2f pos;//�ʒu���
	Vector2f vel;//�W�����v�x�N�g��

	PlayerDirection direction;//�ړ����̌���

	//�v���C���[��ԑJ��
	void (Player::*updateFunc)(const Peripheral&);
	//�������͂������Ă��Ȃ����
	void NeutralUpdate(const Peripheral& _p);
	//�ړ����
	void MoveUpdate(const Peripheral& _p);
	//�W�����v���
	void AerialUpdate(const Peripheral& _p);

	//�}�E�X(�ۗ�)
	void PlayerMouseMove();
public:
	Player(Vector2f _pos);
	~Player();

	//�v�����[�̐i��ł�������擾
	PlayerDirection GetPlayerDirection() { return direction; };
	//�ړ����x�̎擾
	float GetSpeed() { return playerSpeed; };
	//�d�͂̎擾
	float GetGravity() { return gravity; };
	//�ʒu�̎擾
	Vector2f GetPosition() { return Vector2f(pos.x, pos.y + 25); };


	//�ʒu�̐ݒ�
	void SetPosition(Vector2f _pos);
	//���n����̐ݒ�
	void SetOnGround(bool _onGround);

	
	//�ړ�����
	//@param bool |true:���͈͈ȏ�i�߂Ȃ�|false:��ʓ��Ȃ�ǂ��ł�������|
	void PlayerMoveLimit(bool excuteFlag);

	//���t���[���X�V�p�֐�
	void Update(Peripheral& p);
};

