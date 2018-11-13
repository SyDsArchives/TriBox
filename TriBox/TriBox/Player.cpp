#include "Player.h"
#include "Peripheral.h"
#include "DxLib.h"
#include "Geometry.h"
#include <Windows.h>
#include <mmsystem.h>

#pragma comment(lib,"winmm.lib")

const float initJumpHeight = 12.f;

Player::Player(Vector2f _pos):playerSpeed(6.f),lastTime(0.f), jumpInertia(0.f),
aerialFlag(false),
direction(PlayerDirection::none)
{
	updateFunc = &Player::NeutralUpdate;
	triboximg = DxLib::LoadGraph("Resource/img/tribox.png");
	pos = Vector2f(_pos.x,_pos.y);

	imgpos = Vector2f(25, 25);
	imgcpos = Vector2f(75, 75);
}


Player::~Player()
{
}

void Player::SetPosition(Vector2f _pos)
{
	pos = _pos;
}

Vector2f Player::GetPosition()
{
	return pos;
}

void Player::NeutralUpdate(const Peripheral& _p)
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "�j���[�g����");

	//�ړ�
	if (_p.IsPressing(PAD_INPUT_LEFT) || _p.IsPressing(PAD_INPUT_RIGHT))
	{
		updateFunc = &Player::MoveUpdate;
	}

	//�W�����v
	if (_p.IsPressing(PAD_INPUT_UP))
	{
		aerialFlag = true;
		pos.y -= 50.f;
		lastTime = timeGetTime();
		direction = PlayerDirection::none;
		updateFunc = &Player::AerialUpdate;
	}
}

void Player::MoveUpdate(const Peripheral& _p)
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "���[��");

	//�������Ă��Ȃ�������NeutralUpdate�ɖ߂�
	if (!(_p.IsPressing(PAD_INPUT_LEFT) || _p.IsPressing(PAD_INPUT_RIGHT)))
	{
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
		aerialFlag = true;
		pos.y -= 50.f;
		lastTime = timeGetTime();
		updateFunc = &Player::AerialUpdate;
	}
}

void Player::AerialUpdate(const Peripheral & _p)
{
	float secondsLimit = 100.f;
	bool aerialTime = (timeGetTime() - lastTime) <= secondsLimit;

	//��L�[�������Ă���Ԃ��A�����Ă��鎞�Ԃ�0.1�b�𒴂���܂ł̊�
	if (_p.IsPressing(PAD_INPUT_UP) && aerialTime)
	{
		pos.y -= initJumpHeight;
	}
	else
	{
		aerialFlag = false;
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

	pos.x += jumpInertia;

	//�n�ʂƓ������W�ɂ�����NeutralUpdate�ɖ߂�
	if (pos.y >= WindowSizeY - 100)
	{
		jumpInertia = 0;
		updateFunc = &Player::NeutralUpdate;
	}
}


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


void Player::Update(Peripheral& _p)
{
	(this->*updateFunc)(_p);
	//�v���C���[�ړ�
	//PlayerMouseMove();

	if (pos.y < WindowSizeY - 100 && !aerialFlag)
	{
		pos.y += 8.f;
	}

	DxLib::DrawRectRotaGraph2(pos.x, pos.y, imgpos.x, imgpos.y, 100, 100, imgcpos.x, imgcpos.y, 0.5, 0, triboximg, true, false, false);//�v���C���[

}
