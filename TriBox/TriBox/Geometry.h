#pragma once
//プロジェクト全体で必要な機能のみ

const int WindowSizeX = 978;
const int WindowSizeY = 50 * 11;

struct Rect {
	Rect() {};
	Rect(float _top, float _bottom, float _left, float _right)
		:top(_top), bottom(_bottom), right(_right), left(_left) {};

	float top;
	float bottom;
	float right;
	float left;
};

