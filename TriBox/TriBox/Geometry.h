#pragma once
//プロジェクト全体で必要な機能のみ

const int WindowSizeX = 978;
const int WindowSizeY = 50 * 11;

struct Rect {
	//中央座標系
	Rect() : top(0), left(0), width(0), height(0), centerX(0), centerY(0) {};
	//左上座標系
	Rect(float _top, float _left, float _width, float _height)
		:top(_top), left(_left), width(_width), height(_height)
	{
		centerX = left + width / 2;
		centerY = top + height / 2;
	};

	float top;
	float left;
	float width;
	float height;
	float centerX;
	float centerY;

	float Top() { return centerY - height / 2; };
	float Bottom() { return centerY + height / 2; };
	float Right() { return centerX + width / 2; };
	float Left() { return centerX - width / 2; };

	//中央座標系
	void SetCenter(float _x, float _y, float _width, float _height);
	//左上座標系
	void SetLeftTopWidhtHeight(float _top, float _left, float _width, float _height);
};