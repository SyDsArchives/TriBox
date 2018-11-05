#include "Player.h"
#include "Peripheral.h"
#include "DxLib.h"
#include "Geometry.h"
#include <Windows.h>


Player::Player(Vector2f _pos): imgcnt(0),changeframe(0),playerSpeed(6.f),changeflg(false),onceExcute(false)
{
	triboximg = DxLib::LoadGraph("Resource/img/tribox.png");
	pState = PlayerState::box;
	triboxpos = Vector2f(_pos.x,_pos.y);

	imgpos = Vector2f(25, 25);
	imgcpos = Vector2f(75, 75);//125����
}


Player::~Player()
{
}

void Player::SetPosition(Vector2f _pos)
{
	triboxpos = _pos;
}

Vector2f Player::GetPosition()
{
	return triboxpos;
}

void Player::SetSpeed(float _speed)
{
	playerSpeed = _speed;
}

float Player::GetSpeed()
{
	return playerSpeed;
}

void Player::PlayerMove(Peripheral& _p)
{
	//�v���C���[�̈ړ�(������)
	if (_p.IsPressing(PAD_INPUT_UP))//��
	{
		triboxpos.y -= playerSpeed;
	}
	if (_p.IsPressing(PAD_INPUT_DOWN))//��
	{
		triboxpos.y += playerSpeed;
	}
	if (_p.IsPressing(PAD_INPUT_LEFT))//��
	{
		triboxpos.x -= playerSpeed;
	}
	if (_p.IsPressing(PAD_INPUT_RIGHT))//�E
	{
		triboxpos.x += playerSpeed;
	}

	//�v���C���[�̃A�j���[�V�����Đ��J�n
	if (_p.IsPressing(PAD_INPUT_A))
	{
		if (!changeflg)
		{
			changeflg = true;
			changeframe = 0;
		}
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
	triboxpos = mousePos;


	DrawFormatString(0, 0, GetColor(255, 255, 255), "%.1f", mousePos.x);
	DrawFormatString(70, 0, GetColor(255, 255, 255), "%.1f", mousePos.y);
}

void Player::PlayerAnimation()
{
	//if (changeflg)
	//{
	//	if (imgcnt == 2)
	//	{
	//		changeflg = false;
	//		onceExcute = false;
	//		imgcnt = 0;
	//	}

	//	changeframe += 1;
	//	if (changeframe % 3 == 0)
	//	{
	//		if (pState == PlayerState::box)
	//		{
	//			if (imgcnt == 0)//�v���C���[�C���[�W1�i��
	//			{
	//				if (!onceExcute)
	//				{
	//					imgpos.x = 25;
	//					imgpos.y = 25;
	//					onceExcute = true;
	//				}
	//				if (imgpos.x < 400)
	//				{
	//					imgpos.x = imgpos.x + 125;
	//				}
	//				else
	//				{
	//					imgcnt = 1;
	//					onceExcute = false;
	//				}
	//			}

	//			if (imgcnt == 1)//�v���C���[�C���[�W2�i��
	//			{
	//				if (!onceExcute)
	//				{
	//					imgpos.x = 25;
	//					imgpos.y = 150;
	//					onceExcute = true;
	//				}
	//				if (imgpos.x < 400)
	//				{
	//					imgpos.x = imgpos.x + 125;
	//				}
	//				else
	//				{
	//					imgcnt = 2;
	//					pState = PlayerState::triangle;
	//				}
	//			}
	//		}
	//		else if (pState == PlayerState::triangle)
	//		{
	//			if (imgcnt == 0)//�v���C���[�C���[�W1�i��
	//			{
	//				if (!onceExcute)
	//				{
	//					imgpos.x = 400;
	//					imgpos.y = 150;
	//					onceExcute = true;
	//				}
	//				if (imgpos.x > 25)
	//				{
	//					imgpos.x = imgpos.x - 125;
	//				}
	//				else
	//				{
	//					imgcnt = 1;
	//					onceExcute = false;
	//				}
	//			}

	//			if (imgcnt == 1)//�v���C���[�C���[�W2�i��
	//			{
	//				if (!onceExcute)
	//				{
	//					imgpos.x = 400;
	//					imgpos.y = 25;
	//					onceExcute = true;
	//				}
	//				if (imgpos.x > 25)
	//				{
	//					imgpos.x = imgpos.x - 125;
	//				}
	//				else
	//				{
	//					imgcnt = 2;
	//					pState = PlayerState::box;
	//				}
	//			}
	//		}
	//	}
	//}
}

void Player::Update(Peripheral& _p)
{
	
	//�v���C���[�ړ�
	PlayerMouseMove();

	//PlayerAnimation();//�v���C���[�̃A�j���[�V�����Đ�

	DxLib::DrawRectRotaGraph2(triboxpos.x, triboxpos.y, imgpos.x, imgpos.y, 100, 100, imgcpos.x, imgcpos.y, 0.5, 0, triboximg, true, false, false);//�v���C���[

}
