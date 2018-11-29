#pragma once
#include "Vector2D.h"
#include <vector>

//�v���C���[�̈ړ�����������
enum class PlayerDirection
{
	none,//�����ĂȂ�
	left,//���ړ�
	right,//�E�ړ�
};

struct PlayerAnimationState 
{
	Position2 imgPos;
	Position2 imgCenter;
};

struct Rect;
class Peripheral;
class Player
{
private:
	int playerImg;//�v���C���[�摜
	int imgframe;
	int animNum;
	int frame;

	float playerSpeed;//�ړ����x
	float jumpInertia;//�W�����v���̊���
	float gravity;//�d��
	float jumpPower;//�W�����v��
	float lastTime;//�W�����v�����u�Ԃ̎���
	
	bool aerialFlag;//true:�󒆏㏸��� false:�󒆉��~���
	bool onGround;//�n�ʂɂ��邩�ǂ���
	bool isDead;
	bool reverse;

	Vector2f pos;//�ʒu���
	Vector2f vel;//�ړ��x�N�g��

	Position2 imgPos = {};
	Position2 imgCenter = {};
	Position2 imgSize;

	PlayerDirection direction;//�ړ����̌���

	std::vector<PlayerAnimationState> playerMoveAnimation;
	Position2 playerJumpPos;

	//�v���C���[��ԑJ��
	void (Player::*updateFunc)(const Peripheral&);
	//�������͂������Ă��Ȃ����
	void NeutralUpdate(const Peripheral& _p);
	//�ړ����
	void MoveUpdate(const Peripheral& _p);
	//�W�����v���
	void AerialUpdate(const Peripheral& _p);
	//���n���
	void OnLandUpdate(const Peripheral& _p);
	//���S����
	void PlayerDead(const Peripheral& _p);

	void CreatePlayerAnimation();

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
	Vector2f GetPosition() { return Vector2f(pos.x, pos.y); };


	//�ʒu�̐ݒ�
	void SetPosition(Vector2f _pos, bool xEmpty = false, bool yEmpty = false);
	//���n����̐ݒ�
	void SetOnGround(bool _onGround);
	//�ړ��x�N�g���̐ݒ�
	void SetVector(Vector2f _vec);

	//�v���C���[�̎��S����
	bool IsDead(float _underLine);
	
	//�ړ�����
	//@param bool |true:���͈͈ȏ�i�߂Ȃ�|false:��ʓ��Ȃ�ǂ��ł�������|
	void PlayerMoveLimit(bool excuteFlag);

	//���t���[���X�V�p�֐�
	void Update(Peripheral& p);

	Position2 GetPlayerSize();

	Rect& GetRect();
};

