#include "Player.h"
#include "Peripheral.h"
#include "DxLib.h"
#include "Geometry.h"
#include <Windows.h>


Player::Player(Vector2f _pos):playerSpeed(6.f)
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
	DrawFormatString(0, 0, GetColor(255, 255, 255), "ニュートラル");

	if (_p.IsPressing(PAD_INPUT_UP) || _p.IsPressing(PAD_INPUT_DOWN) || _p.IsPressing(PAD_INPUT_LEFT) || _p.IsPressing(PAD_INPUT_RIGHT))
	{
		updateFunc = &Player::MoveUpdate;
	}
	
}

void Player::MoveUpdate(const Peripheral& _p)
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "ムーヴ");

	if (!(_p.IsPressing(PAD_INPUT_UP) || _p.IsPressing(PAD_INPUT_DOWN) || _p.IsPressing(PAD_INPUT_LEFT) || _p.IsPressing(PAD_INPUT_RIGHT)))
	{
		updateFunc = &Player::NeutralUpdate;
	}

	if (_p.IsPressing(PAD_INPUT_UP))//上
	{
		pos.y -= playerSpeed;
	}
	if (_p.IsPressing(PAD_INPUT_DOWN))//下
	{
		pos.y += playerSpeed;
	}
	if (_p.IsPressing(PAD_INPUT_LEFT))//左
	{
		pos.x -= playerSpeed;
	}
	if (_p.IsPressing(PAD_INPUT_RIGHT))//右
	{
		pos.x += playerSpeed;
	}
}


void Player::PlayerMouseMove()
{
	auto hwnd = DxLib::GetMainWindowHandle();
	POINT mouse;

	//スクリーン座標上のマウスカーソル位置を取得
	GetCursorPos(&mouse);
	
	//カーソル位置をスクリーン座標→クライアント座標へ変換する
	//取得に成功で 「true」、失敗すると 「false」 が出力される
	bool result = ScreenToClient(hwnd, &mouse);

	//Vector2変数に代入、保存
	Vector2f mousePos;
	mousePos.x = mouse.x;
	mousePos.y = mouse.y;

	//カーソル座標X,Yのクライアント外の座標時の補正
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

	//キャラ座標へ代入
	pos.x = mousePos.x;
	pos.y = mousePos.y;


	DrawFormatString(0, 0, GetColor(255, 255, 255), "%.1f", mousePos.x);
	DrawFormatString(70, 0, GetColor(255, 255, 255), "%.1f", mousePos.y);
}


void Player::Update(Peripheral& _p)
{
	(this->*updateFunc)(_p);
	//プレイヤー移動
	//PlayerMouseMove();

	if (pos.y < WindowSizeY - 100)
	{
		pos.y += 10.f;
	}

	DxLib::DrawRectRotaGraph2(pos.x, pos.y, imgpos.x, imgpos.y, 100, 100, imgcpos.x, imgcpos.y, 0.5, 0, triboximg, true, false, false);//プレイヤー

}
