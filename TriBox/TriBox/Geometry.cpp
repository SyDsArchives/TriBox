#include "Geometry.h"
#include <cmath>

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

HitRectDirection Rect::HitRect(Rect a, Rect b)
{
	HitRectDirection ret = {};

	ret.isHit_Top = a.Top() < b.Bottom();
	ret.isHit_Bottom = a.Bottom() > b.Top();
	ret.isHit_Right = a.Right() > b.Left();
	ret.isHit_Left = a.Left() < b.Right();

	ret.isHit_All = a.Right() > b.Left() 
					&& a.Top() < b.Bottom() 
					&& a.Left() < b.Right() 
					&& a.Bottom() > b.Top();

	return ret;
}

bool Rect::IsCollision(Rect a, Rect b)
{
	return std::abs(a.centerX - b.centerX) < (a.width + b.width) / 2 && abs(a.centerY - b.centerY) <
		(a.height + b.height) / 2;
}
