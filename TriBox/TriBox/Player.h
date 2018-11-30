#pragma once
#include "Vector2D.h"//�ʒu���i�[�p
#include <vector>

//�v���C���[�̈ړ�����������
enum class PlayerDirection
{
	none,//�����ĂȂ�
	left,//���ړ�
	right,//�E�ړ�
};

//�v���C���[�̃A�j���[�V�����p
struct PlayerAnimationState 
{
	Position2 imgPos;//�摜���̍��W
	Position2 imgCenter;//�摜�̒��S���W
};

struct Rect;
class Peripheral;
class Player
{
private:
	int playerImg;//�v���C���[�摜
	int animNum;//�v���C���[�A�j���[�V������
	int frame;//�t���[�������p�ϐ�

	float playerSpeed;//�ړ����x
	float initialSpeed;//�ʏ푬�x(�������x)
	float jumpInertia;//�W�����v���̊���
	float gravity;//�d��
	float jumpPower;//�W�����v��
	float lastTime;//�W�����v�����u�Ԃ̎���
	
	bool aerialFlag;//�󒆂ɂ��邩(true:�󒆏㏸���,false:�󒆉��~��)
	bool onGround;//�n�ʂɓ������Ă��邩(true:�������Ă���,false:�������Ă��Ȃ�)
	bool isDead;//���S����(true:����,false:�܂�����łȂ�)
	bool reverse;//�v���C���[�̉摜���]����(true:��,false:�E)

	Vector2f pos;//�ʒu���
	Vector2f vel;//�ړ��x�N�g��

	Position2 imgPos = {};//�v���C���[�摜���W
	Position2 imgCenter = {};//�v���C���[�������W
	Position2 imgSize;//�v���C���[�̑傫��

	PlayerDirection direction;//�ړ����̌���

	std::vector<PlayerAnimationState> playerMoveAnimation;//�ړ��A�j���[�V����
	Position2 playerJumpPos;//�W�����v�A�j���[�V����

	//�v���C���[��ԑJ��
	void (Player::*updateFunc)(const Peripheral&);

	//�������͂������Ă��Ȃ����
	//@param (const Pheripheral& p) �L�[�{�[�h�̓��͂��o�͂���
	void NeutralUpdate(const Peripheral& _p);

	//�ړ����
	//@param (const Pheripheral& p) �L�[�{�[�h�̓��͂��o�͂���
	void MoveUpdate(const Peripheral& _p);

	//�W�����v(��)���
	//@param (const Pheripheral& p) �L�[�{�[�h�̓��͂��o�͂���
	void AerialUpdate(const Peripheral& _p);

	//���n���
	//@param (const Pheripheral& p) �L�[�{�[�h�̓��͂��o�͂���
	void OnLandUpdate(const Peripheral& _p);

	//���S���
	//@param (const Pheripheral& p) �L�[�{�[�h�̓��͂��o�͂���
	void PlayerDead(const Peripheral& _p);

	//�v���C���[�̃A�j���[�V�����𐶐�����
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
	//�v���C���[�̑傫���̎擾
	Position2 GetPlayerSize() { return imgSize; };
	//�v���C���[�̋�`���̎擾
	Rect& GetRect();


	//�ʒu�̐ݒ�
	//@param  (Vector2f _pos) �v���C���[�̈ʒu���W
	//@param  (bool xEmpty) �v���C���[��X���W���̗͂L�� (true:X�̑�������Ȃ�,false:X�̑��������)
	//@param  (bool yEmpty) �v���C���[��Y���W����̗L�� (true:Y�̑�������Ȃ�,false:Y�̑��������)
	void SetPosition(Vector2f _pos, bool xEmpty = false, bool yEmpty = false);
	
	//���n����̐ݒ�
	//@param (bool _onGround) �ϐ�onGround���Q��
	void SetOnGround(bool _onGround);

	//�v���C���[�̎��S����
	//@param (float _underLine) ��ԒႢ�X�e�[�W�I�u�W�F�N�g�̈ʒu
	bool IsDead(float _underLine);
	
	//�ړ�����
	//@param (bool excuteFlag) (true:���͈͈ȏ�i�߂Ȃ�,false:��ʓ��Ȃ�ǂ��ł�������)
	void PlayerMoveLimit(bool excuteFlag);

	//���t���[���X�V�p�֐�
	void Update(Peripheral& p);
};

