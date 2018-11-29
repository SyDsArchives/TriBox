#pragma once
#include "Vector2D.h"
#include <vector>

//プレイヤーの移動中向き情報列挙
enum class PlayerDirection
{
	none,//動いてない
	left,//左移動
	right,//右移動
};

struct PlayerAnimationState 
{
	Position2 imgPos;
	Position2 imgCenter;
};

struct Rect;
class Peripheral;
class Player
{
private:
	int playerImg;//プレイヤー画像
	int imgframe;
	int animNum;
	int frame;

	float playerSpeed;//移動速度
	float jumpInertia;//ジャンプ中の慣性
	float gravity;//重力
	float jumpPower;//ジャンプ力
	float lastTime;//ジャンプした瞬間の時間
	
	bool aerialFlag;//true:空中上昇状態 false:空中下降状態
	bool onGround;//地面にいるかどうか
	bool isDead;
	bool reverse;

	Vector2f pos;//位置情報
	Vector2f vel;//移動ベクトル

	Position2 imgPos = {};
	Position2 imgCenter = {};
	Position2 imgSize;

	PlayerDirection direction;//移動中の向き

	std::vector<PlayerAnimationState> playerMoveAnimation;
	Position2 playerJumpPos;

	//プレイヤー状態遷移
	void (Player::*updateFunc)(const Peripheral&);
	//何も入力が入っていない状態
	void NeutralUpdate(const Peripheral& _p);
	//移動状態
	void MoveUpdate(const Peripheral& _p);
	//ジャンプ状態
	void AerialUpdate(const Peripheral& _p);
	//着地状態
	void OnLandUpdate(const Peripheral& _p);
	//死亡判定
	void PlayerDead(const Peripheral& _p);

	void CreatePlayerAnimation();

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
	Vector2f GetPosition() { return Vector2f(pos.x, pos.y); };


	//位置の設定
	void SetPosition(Vector2f _pos, bool xEmpty = false, bool yEmpty = false);
	//着地判定の設定
	void SetOnGround(bool _onGround);
	//移動ベクトルの設定
	void SetVector(Vector2f _vec);

	//プレイヤーの死亡判定
	bool IsDead(float _underLine);
	
	//移動制限
	//@param bool |true:一定範囲以上進めない|false:画面内ならどこでも動ける|
	void PlayerMoveLimit(bool excuteFlag);

	//毎フレーム更新用関数
	void Update(Peripheral& p);

	Position2 GetPlayerSize();

	Rect& GetRect();
};

