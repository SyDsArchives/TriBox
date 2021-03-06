#include "Player.h"
#include "Peripheral.h"
#include "DxLib.h"
#include <Windows.h>
#include <mmsystem.h>
#include "Geometry.h"
#include "FPS.h"

#pragma comment(lib,"winmm.lib")

Player::Player(Vector2f _pos) :
initialSpeed(3.f), playerSpeed(3.f), jumpInertia(0.f), gravity(6.f), jumpPower(18.f),
lastTime(0),animNum(0),
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

	//移動アニメーション
	for (int num = 0; num < 5; ++num)
	{
		state = { Position2(num * 50,40),Position2(25,20) };
		playerMoveAnimation.emplace_back(state);
	}

	//ジャンプイメージ座標
	playerJumpPos = {0, 80};
}

///////////////////////////////////////////
//状態遷移系関数
///////////////////////////////////////////

//何の状態でもない場合
void Player::NeutralUpdate(const Peripheral& _p)
{
	imgPos = { 0,0 };
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
	//何もしていなかったらNeutralUpdateに戻る
	if (!(_p.IsPressing(PAD_INPUT_LEFT) || _p.IsPressing(PAD_INPUT_RIGHT)))
	{
		frame = 0;
		direction = PlayerDirection::none;
		updateFunc = &Player::NeutralUpdate;
	}

	//左移動
	if (_p.IsPressing(PAD_INPUT_LEFT))
	{
		direction = PlayerDirection::left;
		pos.x -= playerSpeed;
		reverse = true;
	}
	//右移動
	if (_p.IsPressing(PAD_INPUT_RIGHT))
	{
		direction = PlayerDirection::right;
		pos.x += playerSpeed;
		reverse = false;
	}

	//ジャンプ
	if (_p.IsPressing(PAD_INPUT_UP))
	{
		onGround = false;
		vel.y = jumpPower;
		lastTime = timeGetTime();
		updateFunc = &Player::AerialUpdate;
	}


	if (++frame % 5 == 0)
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

//空中の場合
void Player::AerialUpdate(const Peripheral & _p)
{
	imgPos = playerJumpPos;
	float playerSpeed_aerial = 5.f;//空中時の横移動速度
	float secondsLimit = 120.f;//追加ジャンプ時間
	float addJumpPower = 2.f;//追加ジャンプ力
	bool aerialTime = (timeGetTime() - lastTime) <= secondsLimit;//追加ジャンプ判定
	playerSpeed = playerSpeed_aerial;

	pos.x += jumpInertia;

	////上キーを押している間かつ、押している時間が0.1秒を超えるまでの間
	//if (_p.IsPressing(PAD_INPUT_UP) && aerialTime)
	//{
	//	vel.y += addJumpPower;
	//}

	//左移動
	if (_p.IsPressing(PAD_INPUT_LEFT) && direction == PlayerDirection::none)
	{
		direction = PlayerDirection::left;
	}
	//右移動
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

	//地面と同じ座標についたらNeutralUpdateに戻る
	if (onGround)
	{
		playerSpeed = initialSpeed;
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
		frame = 0;
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
void Player::Update(Peripheral& _p,FPS& _fps)
{
	if (_fps.Wait())
	{
		Sleep(_fps.WaitTime());
		//DrawFormatString(0, 300, GetColor(255, 0, 0), "%d", _fps.WaitTime());
	}

	auto a = _fps.WaitTime();
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
	
	
	//描画
	DxLib::DrawRectRotaGraph2(pos.x, pos.y, imgPos.x, imgPos.y, imgSize.x, imgSize.y, imgCenter.x, imgCenter.y, 1.f, 0, playerImg, true, reverse, false);//プレイヤー
}


///////////////////////////////////////////
//移動制御関数
///////////////////////////////////////////
void Player::PlayerMoveLimit(bool _excuteFlag)
{
	if (_excuteFlag)
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

bool Player::IsDead(float _underLine)
{
	isDead = _underLine < pos.y ? true : false;
	return isDead;
}

///////////////////////////////////////////
//出力
///////////////////////////////////////////
Rect & Player::GetRect()
{
	Rect ret;
	float playerWidth = 25;
	float playerHeight = 50;
	ret.SetCenter(pos.x, pos.y, playerWidth, playerHeight);
	return ret;
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


	/*DrawFormatString(0, 0, GetColor(255, 255, 255), "%.1f", mousePos.x);
	DrawFormatString(70, 0, GetColor(255, 255, 255), "%.1f", mousePos.y);*/
}
