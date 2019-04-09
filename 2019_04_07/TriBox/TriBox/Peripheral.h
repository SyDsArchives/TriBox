#pragma once
///周辺機器(キーボード、パッド)の制御をするクラス
class Peripheral
{
private:
	int padState;
	int lastPadState;

public:
	Peripheral();
	~Peripheral();

	///現在の押下状態の検出
	///@param keyid 調べたいキー番号
	///@retval true 押してる
	///@retval false 押してない
	const bool IsPressing(int _keyid)const;

	///特定のキーのトリガーの検出
	///@param keyid 調べたいキーの番号
	///@retval true 押してる
	///@retval false 押してない
	const bool IsTrigger(int _keyid)const;

	///入力状態を更新する
	///@attention 毎フレーム実行してください
	void Update();
};

