#include "Player.h"
#include "Peripheral.h"
#include "DxLib.h"
#include <Windows.h>
#include <mmsystem.h>
#include "Geometry.h"

#pragma comment(lib,"winmm.lib")

Player::Player(Vector2f _pos) :
playerSpeed(3.f), jumpInertia(0.f), gravity(10.f), jumpPower(10.f),lastTime(0), imgframe(0),animNum(0),
pos(_pos), vel(0,0),imgCenter(25,20),imgSize(50,40),
onGround(false), isDead(false),reverse(false),
direction(PlayerDirection::none)
{
	playerImg = DxLib::LoadGraph("Resource/img/player.png");
	CreatePlayerAnimation();
	updateFunc = &Player::NeutralUpdate;
}

Player::~Player()
{
}

void Player::CreatePlayerAnimation()
{
	PlayerAnimationState state = {};

	//�ړ��A�j���[�V����
	for (int num = 0; num < 5; ++num)
	{
		state = { Position2(num * 50,40),Position2(25,20) };
		playerMoveAnimation.emplace_back(state);
	}

	//�W�����v�C���[�W���W
	playerJumpPos = {0, 80};
}

///////////////////////////////////////////
//��ԑJ�ڌn�֐�
///////////////////////////////////////////

//���̏�Ԃł��Ȃ��ꍇ
void Player::NeutralUpdate(const Peripheral& _p)
{
	imgPos = { 0,0 };
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
		reverse = true;
	}
	//�E�ړ�
	if (_p.IsPressing(PAD_INPUT_RIGHT))
	{
		direction = PlayerDirection::right;
		pos.x += playerSpeed;
		reverse = false;
	}

	//�W�����v
	if (_p.IsPressing(PAD_INPUT_UP))
	{
		onGround = false;
		vel.y = jumpPower;
		lastTime = timeGetTime();
		updateFunc = &Player::AerialUpdate;
	}


	if (++imgframe % 5 == 0)
	{
		imgPos = playerMoveAnimation[animNum].imgPos;
		imgCenter = playerMoveAnimation[animNum].imgCenter;
		++animNum;
		if (animNum == playerMoveAnimation.size() - 1)
		{
			animNum = 0;
		}
	}
}

//�󒆂̏ꍇ
void Player::AerialUpdate(const Peripheral & _p)
{
	imgPos = playerJumpPos;
	float secondsLimit = 100.f;
	float addJumpPower = 2.f;
	bool aerialTime = (timeGetTime() - lastTime) <= secondsLimit;
	playerSpeed = 5.f;

	pos.x += jumpInertia;

	//��L�[�������Ă���Ԃ��A�����Ă��鎞�Ԃ�0.1�b�𒴂���܂ł̊�
	if (_p.IsPressing(PAD_INPUT_UP) && aerialTime)
	{
		vel.y += addJumpPower;
	}

	//���ړ�
	if (_p.IsPressing(PAD_INPUT_LEFT) && direction == PlayerDirection::none)
	{
		direction = PlayerDirection::left;
	}
	//�E�ړ�
	if (_p.IsPressing(PAD_INPUT_RIGHT) && direction == PlayerDirection::none)
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
		playerSpeed = 3.f;
		direction = PlayerDirection::none;
		jumpInertia = 0;
		updateFunc = &Player::OnLandUpdate;
	}
}

void Player::OnLandUpdate(const Peripheral & _p)
{
	imgPos = { 0,0 };
	if (++frame % 5 == 0)
	{
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

	pos.y -= vel.y;
	if (vel.y >= -8.f)
	{
		vel.y -= 2.f;
	}
	else
	{
		vel.y = -9.f;
	}

	DxLib::DrawRectRotaGraph2(pos.x, pos.y, imgPos.x, imgPos.y, imgSize.x, imgSize.y, imgCenter.x, imgCenter.y, 1.f, 0, playerImg, true, reverse, false);//�v���C���[
}

Position2 Player::GetPlayerSize()
{
	return imgSize;
}

Rect & Player::GetRect()
{
	Rect ret;
	ret.SetCenter(pos.x, pos.y, 25, 50);
	//ret.SetCenter(pos.x, pos.y, imgSize.x, imgSize.y);
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
	isDead = _underLine < pos.y ? true : false;
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