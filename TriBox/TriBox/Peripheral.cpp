#include "Peripheral.h"
#include "DxLib.h"
#include <iostream>


Peripheral::Peripheral():padState(0),lastPadState(0)
{
	padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
}


Peripheral::~Peripheral()
{
}

const bool Peripheral::IsPressing(int _keyid)const
{
	return _keyid & padState ? true : false;
}

const bool Peripheral::IsTrigger(int _keyid)const
{

	return ((padState & _keyid) & (lastPadState & _keyid)) ^ (padState & _keyid);
}

void Peripheral::Update()
{
	lastPadState = padState;
	padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
}
