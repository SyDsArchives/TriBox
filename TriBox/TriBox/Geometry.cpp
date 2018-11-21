#include "Geometry.h"

template<typename T>
void Rect<T>::SetCenter(T _x, T _y)
{
	centerX += _x;
	centerY += _y;
}

template<typename T>
void Rect<T>::SetLeftTopWidhtHeight(T _top, T _left, T _width, T _height)
{
	top = _top;
	left = _left;
	width = _width;
	height = _height;

	centerX = left + width / 2;
	centerY = top + height / 2;
}