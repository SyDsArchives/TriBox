#pragma once
#include "Vector2D.h"//位置情報格納用
#include <vector>

//プレイヤーの移動中向き情報列挙
enum class PlayerDirection
{
	none,//動いてない
	left,//左移動
	right,//右移動
};

//プレイヤーのアニメーション用
struct PlayerAnimationState 
{
	Position2 imgPos;//画像内の座標
	Position2 imgCenter;//画像の中心座標
};

struct Rect;
class Peripheral;
class Player
{
private:
	int playerImg;//プレイヤー画像
	int animNum;//プレイヤーアニメーション数
	int frame;//フレーム処理用変数

	float playerSpeed;//移動速度
	float initialSpeed;//通常速度(初期速度)
	float jumpInertia;//ジャンプ中の慣性
	float gravity;//重力
	float jumpPower;//ジャンプ力
	float lastTime;//ジャンプした瞬間の時間
	
	bool aerialFlag;//空中にいるか(true:空中上昇状態,false:空中下降状)
	bool onGround;//地面に当たっているか(true:当たっている,false:当たっていない)
	bool isDead;//死亡判定(true:死んだ,false:まだ死んでない)
	bool reverse;//プレイヤーの画像反転判定(true:左,false:右)

	Vector2f pos;//位置情報
	Vector2f vel;//移動ベクトル

	Position2 imgPos = {};//プレイヤー画像座標
	Position2 imgCenter = {};//プレイヤー中央座標
	Position2 imgSize;//プレイヤーの大きさ

	PlayerDirection direction;//移動中の向き

	std::vector<PlayerAnimationState> playerMoveAnimation;//移動アニメーション
	Position2 playerJumpPos;//ジャンプアニメーション

	//プレイヤー状態遷移
	void (Player::*updateFunc)(const Peripheral&);

	//何も入力が入っていない状態
	//@param (const Pheripheral& p) キーボードの入力を出力する
	void NeutralUpdate(const Peripheral& _p);

	//移動状態
	//@param (const Pheripheral& p) キーボードの入力を出力する
	void MoveUpdate(const Peripheral& _p);

	//ジャンプ(空中)状態
	//@param (const Pheripheral& p) キーボードの入力を出力する
	void AerialUpdate(const Peripheral& _p);

	//着地状態
	//@param (const Pheripheral& p) キーボードの入力を出力する
	void OnLandUpdate(const Peripheral& _p);

	//死亡状態
	//@param (const Pheripheral& p) キーボードの入力を出力する
	void PlayerDead(const Peripheral& _p);

	//プレイヤーのアニメーションを生成する
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
	//プレイヤーの大きさの取得
	Position2 GetPlayerSize() { return imgSize; };
	//プレイヤーの矩形情報の取得
	Rect& GetRect();


	//位置の設定
	//@param  (Vector2f _pos) プレイヤーの位置座標
	//@param  (bool xEmpty) プレイヤーのX座標入力の有無 (true:Xの代入をしない,false:Xの代入をする)
	//@param  (bool yEmpty) プレイヤーのY座標代入の有無 (true:Yの代入をしない,false:Yの代入をする)
	void SetPosition(Vector2f _pos, bool xEmpty = false, bool yEmpty = false);
	
	//着地判定の設定
	//@param (bool _onGround) 変数onGroundを参照
	void SetOnGround(bool _onGround);

	//プレイヤーの死亡判定
	//@param (float _underLine) 一番低いステージオブジェクトの位置
	bool IsDead(float _underLine);
	
	//移動制限
	//@param (bool excuteFlag) (true:一定範囲以上進めない,false:画面内ならどこでも動ける)
	void PlayerMoveLimit(bool excuteFlag);

	//毎フレーム更新用関数
	void Update(Peripheral& p);
};

