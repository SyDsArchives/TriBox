#include "Geometry.h"

void Rect::SetCenter(float _x, float _y, float _width, float _height)
{
	centerX = _x;
	centerY = _y;
	width = _width;
	height = _height;
}

void Rect::SetLeftTopWidhtHeight(float _top, float _left, float _width, float _height)
{
	top = _top;
	left = _left;
	width = _width;
	height = _height;

	centerX = left + width / 2;
	centerY = top + height / 2;
}