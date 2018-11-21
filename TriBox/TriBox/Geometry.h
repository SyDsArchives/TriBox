#pragma once
//プロジェクト全体で必要な機能のみ

const int WindowSizeX = 978;
const int WindowSizeY = 50 * 11;

template<typename T>
struct Rect {
	Rect() 
		:top(0), left(0), width(0), height(0), centerX(0), centerY(0){};
	Rect(T _top, T _left, T _width, T _height)
		:top(_top), left(_left), width(_width), height(_height)
	{
		centerX = left + width / 2;
		centerY = top + height / 2;
	};

	//bool Rect<T>::operator>(T num1, T num2) const
	//{
	//	return num1 > num2;
	//}

	T top;
	T left;
	T width;
	T height;
	T centerX;
	T centerY;

	T Top() { return centerY - height / 2; };
	T Bottom() { return centerY + height / 2; };
	T Right() { return centerX + width / 2; };
	T Left() { return centerX - width / 2; };

	void SetCenter(T _x, T _y);
	void SetLeftTopWidhtHeight(T _top, T _left, T _width, T _height);
};
