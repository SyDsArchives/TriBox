#pragma once
#include "Vector2D.h"

//プレイヤーの移動中向き情報列挙
enum class PlayerDirection
{
	none,//動いてない
	left,//左移動
	right,//右移動
};

class Peripheral;
class Player
{
private:
	int playerImg;//プレイヤー画像

	float playerSpeed;//移動速度
	float jumpInertia;//ジャンプ中の慣性
	float gravity;//重力
	float jumpPower;//ジャンプ力
	float lastTime;//ジャンプした瞬間の時間
	
	bool aerialFlag;//true:空中上昇状態 false:空中下降状態
	bool onGround;//地面にいるかどうか

	Vector2f pos;//位置情報
	Vector2f vel;//ジャンプベクトル

	PlayerDirection direction;//移動中の向き

	//プレイヤー状態遷移
	void (Player::*updateFunc)(const Peripheral&);
	//何も入力が入っていない状態
	void NeutralUpdate(const Peripheral& _p);
	//移動状態
	void MoveUpdate(const Peripheral& _p);
	//ジャンプ状態
	void AerialUpdate(const Peripheral& _p);

	//マウス(保留)
	void PlayerMouseMove();
public:
	Player(Vector2f _pos);
	~Player();

	//プレヤーの進んでいる方向取得
	PlayerDirection GetPlayerDirection() { return direction; };
	//移動速度の取得
	float GetSpeed() { return playerSpeed; };
	//重力の取得
	float GetGravity() { return gravity; };
	//位置の取得
	Vector2f GetPosition() { return Vector2f(pos.x, pos.y + 25); };


	//位置の設定
	void SetPosition(Vector2f _pos);
	//着地判定の設定
	void SetOnGround(bool _onGround);

	
	//移動制限
	//@param bool |true:一定範囲以上進めない|false:画面内ならどこでも動ける|
	void PlayerMoveLimit(bool excuteFlag);

	//毎フレーム更新用関数
	void Update(Peripheral& p);
};

