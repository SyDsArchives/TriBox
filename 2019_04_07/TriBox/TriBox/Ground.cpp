#include "Ground.h"



Ground::Ground():groundLine(10000)
{
}


Ground::~Ground()
{
}

const void Ground::SetGroundLine(float _groundLine)
{
	groundLine = _groundLine;
}

const float Ground::GetGroundLine()
{
	return groundLine;
}
