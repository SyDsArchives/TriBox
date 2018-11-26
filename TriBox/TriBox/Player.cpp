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
//状態遷移系関数
///////////////////////////////////////////

//何の状態でもない場合
void Player::NeutralUpdate(const Peripheral& _p)
{
	//DrawFormatString(0, 0, GetColor(255, 255, 255), "ニュートラル");

	//移動
	if (_p.IsPressing(PAD_INPUT_LEFT) || _p.IsPressing(PAD_INPUT_RIGHT))
	{
		updateFunc = &Player::MoveUpdate;
	}

	//ジャンプ
	if (_p.IsPressing(PAD_INPUT_UP))
	{
		onGround = false;
		vel.y = jumpPower;
		lastTime = timeGetTime();
		direction = PlayerDirection::none;
		updateFunc = &Player::AerialUpdate;
	}
}

//移動中の場合
void Player::MoveUpdate(const Peripheral& _p)
{
	//DrawFormatString(0, 0, GetColor(255, 255, 255), "ムーヴ");


	//何もしていなかったらNeutralUpdateに戻る
	if (!(_p.IsPressing(PAD_INPUT_LEFT) || _p.IsPressing(PAD_INPUT_RIGHT)))
	{
		direction = PlayerDirection::none;
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
		onGround = false;
		vel.y = jumpPower;
		lastTime = timeGetTime();
		updateFunc = &Player::AerialUpdate;
	}
}

//空中の場合
void Player::AerialUpdate(const Peripheral & _p)
{
	//DrawFormatString(0, 0, GetColor(255, 255, 255), "エリアル");

	float secondsLimit = 100.f;
	float addJumpPower = 2.f;
	bool aerialTime = (timeGetTime() - lastTime) <= secondsLimit;
	playerSpeed = 8.f;

	pos.y -= vel.y;
	vel.y -= 5.f;
	pos.x += jumpInertia;

	//上キーを押している間かつ、押している時間が0.1秒を超えるまでの間
	if (_p.IsPressing(PAD_INPUT_UP) && aerialTime)
	{
		vel.y += addJumpPower;
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

	//地面と同じ座標についたらNeutralUpdateに戻る
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
	//死亡時のエフェクトなど
}

///////////////////////////////////////////
//毎フレーム更新用関数
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

	DxLib::DrawRectRotaGraph2(pos.x, pos.y, 0, 0, 100, 100, 50, 50, 0.5, 0, playerImg, true, false, false);//プレイヤー
}

Rect & Player::GetRect()
{
	Rect ret;
	ret.SetCenter(pos.x, pos.y, 50, 50);
	return ret;
}

///////////////////////////////////////////
//移動制御関数
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
//セット系関数
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
//保留
///////////////////////////////////////////
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