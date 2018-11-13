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
	DrawFormatString(0, 0, GetColor(255, 255, 255), "ニュートラル");

	//移動
	if (_p.IsPressing(PAD_INPUT_LEFT) || _p.IsPressing(PAD_INPUT_RIGHT))
	{
		updateFunc = &Player::MoveUpdate;
	}

	//ジャンプ
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
	DrawFormatString(0, 0, GetColor(255, 255, 255), "ムーヴ");

	//何もしていなかったらNeutralUpdateに戻る
	if (!(_p.IsPressing(PAD_INPUT_LEFT) || _p.IsPressing(PAD_INPUT_RIGHT)))
	{
		updateFunc = &Player::NeutralUpdate;
	}

	//左移動
	if (_p.IsPressing(PAD_INPUT_LEFT))
	{
		direction = PlayerDirection::left;
		pos.x -= playerSpeed;
	}
	//右移動
	if (_p.IsPressing(PAD_INPUT_RIGHT))
	{
		direction = PlayerDirection::right;
		pos.x += playerSpeed;
	}

	//ジャンプ
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

	//上キーを押している間かつ、押している時間が0.1秒を超えるまでの間
	if (_p.IsPressing(PAD_INPUT_UP) && aerialTime)
	{
		pos.y -= initJumpHeight;
	}
	else
	{
		aerialFlag = false;
	}

	//左移動
	if (_p.IsPressing(PAD_INPUT_LEFT))
	{
		direction = PlayerDirection::left;
	}
	//右移動
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

	//地面と同じ座標についたらNeutralUpdateに戻る
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

	if (pos.y < WindowSizeY - 100 && !aerialFlag)
	{
		pos.y += 8.f;
	}

	DxLib::DrawRectRotaGraph2(pos.x, pos.y, imgpos.x, imgpos.y, 100, 100, imgcpos.x, imgcpos.y, 0.5, 0, triboximg, true, false, false);//プレイヤー

}
