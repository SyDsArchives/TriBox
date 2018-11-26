#include "Player.h"
#include "Peripheral.h"
#include "DxLib.h"
#include <Windows.h>
#include <mmsystem.h>
#include "Geometry.h"

#pragma comment(lib,"winmm.lib")

Player::Player(Vector2f _pos) :
playerSpeed(3.f), jumpInertia(0.f), gravity(10.f), jumpPower(25.f),lastTime(0),
pos(_pos), vel(0,0),
onGround(false), isDead(false),
direction(PlayerDirection::none)
{
	playerImg = DxLib::LoadGraph("Resource/img/Circle.png");
	updateFunc = &Player::NeutralUpdate;
}

Player::~Player()
{
}

Vector2f Player::GetVector()
{
	return vel;
}


///////////////////////////////////////////
//��ԑJ�ڌn�֐�
///////////////////////////////////////////

//���̏�Ԃł��Ȃ��ꍇ
void Player::NeutralUpdate(const Peripheral& _p)
{
	//DrawFormatString(0, 0, GetColor(255, 255, 255), "�j���[�g����");

	//�ړ�
	if (_p.IsPressing(PAD_INPUT_LEFT) || _p.IsPressing(PAD_INPUT_RIGHT))
	{
		updateFunc = &Player::MoveUpdate;
	}

	//�W�����v
	if (_p.IsPressing(PAD_INPUT_UP))
	{
		onGround = false;
		vel.y = jumpPower;
		lastTime = timeGetTime();
		direction = PlayerDirection::none;
		updateFunc = &Player::AerialUpdate;
	}
}

//�ړ����̏ꍇ
void Player::MoveUpdate(const Peripheral& _p)
{
	//DrawFormatString(0, 0, GetColor(255, 255, 255), "���[��");


	//�������Ă��Ȃ�������NeutralUpdate�ɖ߂�
	if (!(_p.IsPressing(PAD_INPUT_LEFT) || _p.IsPressing(PAD_INPUT_RIGHT)))
	{
		direction = PlayerDirection::none;
		updateFunc = &Player::NeutralUpdate;
	}

	//���ړ�
	if (_p.IsPressing(PAD_INPUT_LEFT))
	{
		direction = PlayerDirection::left;
		pos.x -= playerSpeed;
	}
	//�E�ړ�
	if (_p.IsPressing(PAD_INPUT_RIGHT))
	{
		direction = PlayerDirection::right;
		pos.x += playerSpeed;
	}

	//�W�����v
	if (_p.IsPressing(PAD_INPUT_UP))
	{
		onGround = false;
		vel.y = jumpPower;
		lastTime = timeGetTime();
		updateFunc = &Player::AerialUpdate;
	}
}

//�󒆂̏ꍇ
void Player::AerialUpdate(const Peripheral & _p)
{
	//DrawFormatString(0, 0, GetColor(255, 255, 255), "�G���A��");

	float secondsLimit = 100.f;
	float addJumpPower = 2.f;
	bool aerialTime = (timeGetTime() - lastTime) <= secondsLimit;
	playerSpeed = 8.f;

	pos.y -= vel.y;
	vel.y -= 5.f;
	pos.x += jumpInertia;

	//��L�[�������Ă���Ԃ��A�����Ă��鎞�Ԃ�0.1�b�𒴂���܂ł̊�
	if (_p.IsPressing(PAD_INPUT_UP) && aerialTime)
	{
		vel.y += addJumpPower;
	}

	//���ړ�
	if (_p.IsPressing(PAD_INPUT_LEFT))
	{
		direction = PlayerDirection::left;
	}
	//�E�ړ�
	if (_p.IsPressing(PAD_INPUT_RIGHT))
	{
		direction = PlayerDirection::right;
	}

	if (direction == PlayerDirection::left)
	{
		jumpInertia = -playerSpeed;
	}
	else if (direction == PlayerDirection::right)
	{
		jumpInertia = playerSpeed;
	}

	//�n�ʂƓ������W�ɂ�����NeutralUpdate�ɖ߂�
	if (onGround)
	{
		jumpInertia = 0;
		playerSpeed = 3.f;
		direction = PlayerDirection::none;
		updateFunc = &Player::NeutralUpdate;
	}
}

void Player::PlayerDead(const Peripheral & _p)
{
	//���S���̃G�t�F�N�g�Ȃ�
}

///////////////////////////////////////////
//���t���[���X�V�p�֐�
///////////////////////////////////////////
void Player::Update(Peripheral& _p)
{
	(this->*updateFunc)(_p);
	

	if (isDead)
	{
		updateFunc = &Player::PlayerDead;
	}

	if (updateFunc != &Player::AerialUpdate && !onGround)
	{
		pos.y += gravity;
	}

	onGround = false;

	DxLib::DrawRectRotaGraph2(pos.x, pos.y, 0, 0, 100, 100, 50, 50, 0.5, 0, playerImg, true, false, false);//�v���C���[
}

Rect & Player::GetRect()
{
	Rect ret;
	ret.SetCenter(pos.x, pos.y, 50, 50);
	return ret;
}

///////////////////////////////////////////
//�ړ�����֐�
///////////////////////////////////////////
void Player::PlayerMoveLimit(bool excuteFlag)
{
	if (excuteFlag)
	{
		if (pos.x >= WindowSizeX / 2)
		{
			pos.x = WindowSizeX / 2;
		}
		if (pos.x <= 25)
		{
			pos.x = 25;
		}
	}
}

///////////////////////////////////////////
//�Z�b�g�n�֐�
///////////////////////////////////////////
void Player::SetPosition(Vector2f _pos, bool xEmpty, bool yEmpty)
{
	if (xEmpty)
	{
		pos.y = _pos.y;
	}
	else if (yEmpty)
	{
		pos.x = _pos.x;
	}
	else
	{
		pos = _pos;
	}
}

void Player::SetOnGround(bool _onGround)
{
	onGround = _onGround;
}

void Player::SetVector(Vector2f _vec)
{
	vel = _vec;
}

bool Player::IsDead(float _underLine)
{
	//isDead = _underLine < pos.y ? true : false;
	return isDead;
}

///////////////////////////////////////////
//�ۗ�
///////////////////////////////////////////
void Player::PlayerMouseMove()
{
	auto hwnd = DxLib::GetMainWindowHandle();
	POINT mouse;

	//�X�N���[�����W��̃}�E�X�J�[�\���ʒu���擾
	GetCursorPos(&mouse);

	//�J�[�\���ʒu���X�N���[�����W���N���C�A���g���W�֕ϊ�����
	//�擾�ɐ����� �utrue�v�A���s����� �ufalse�v ���o�͂����
	bool result = ScreenToClient(hwnd, &mouse);

	//Vector2�ϐ��ɑ���A�ۑ�
	Vector2f mousePos;
	mousePos.x = mouse.x;
	mousePos.y = mouse.y;

	//�J�[�\�����WX,Y�̃N���C�A���g�O�̍��W���̕␳
	if (mousePos.x < 0)
	{
		mousePos.x = 0;
	}
	else if (mousePos.x > WindowSizeX)
	{
		mousePos.x = WindowSizeX;
	}

	if (mousePos.y < 0)
	{
		mousePos.y = 0;
	}
	else if (mousePos.y > WindowSizeY)
	{
		mousePos.y = WindowSizeY;
	}

	//�L�������W�֑��
	pos.x = mousePos.x;
	pos.y = mousePos.y;


	DrawFormatString(0, 0, GetColor(255, 255, 255), "%.1f", mousePos.x);
	DrawFormatString(70, 0, GetColor(255, 255, 255), "%.1f", mousePos.y);
}