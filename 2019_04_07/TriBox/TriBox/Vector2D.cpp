#include "Vector2D.h"

float FDot(Vector2f a, Vector2f b)
{
	return a.x * b.x + a.y * b.y;
}

float FCross(Vector2f a, Vector2f b)
{
	return a.x * b.y - a.y * b.x;
}

Vector2f Normalization(Vector2f vec)
{
	float length = sqrt(vec.x * vec.x + vec.y * vec.y);
	return Vector2f(vec.x / length, vec.y / length);
}
