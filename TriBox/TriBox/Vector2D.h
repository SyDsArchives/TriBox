#pragma once
#include <cmath>

template<typename T>
struct Vector2D {
	Vector2D() : x(0), y(0){}
	Vector2D(T inx, T iny) : x(inx), y(iny){}
	T x;
	T y;
	void operator+=(const Vector2D<T>& in) {
		x += in.x;
		y += in.y;
	}
	void operator*=(float scale) {
		x *= scale;
		y *= scale;
	}
	void operator-=(const Vector2D<T>& in) {
		x -= in.x;
		y -= in.y;
	}
};

//Vector2D<T>�̂��߂�+�I�y���[�^�I�[�o�[���[�h
template<typename T>
Vector2D<T> operator+(const Vector2D<T>& lv, const Vector2D<T>& rv) {
	return Vector2D<T>(lv.x + rv.x, lv.y + rv.y);
}
//Vector2D<T>�̂��߂�-�I�y���[�^�I�[�o�[���[�h
template<typename T>
Vector2D<T> operator-(const Vector2D<T>& lv, const Vector2D<T>& rv) {
	return Vector2D<T>(lv.x - rv.x, lv.y - rv.y);
}
//Vector2D<T>�̂��߂�*�I�y���[�^�I�[�o�[���[�h
template<typename T>
Vector2D<T> operator*(const Vector2D<T>& lv, const float scale) {
	return Vector2D<T>(lv.x*scale, lv.y*scale);
}

//�����^�x�N�g��
typedef Vector2D<int> Vector2;
typedef Vector2 Position2;

//�����x�N�g��
typedef Vector2D<float> Vector2f;
typedef Vector2f Position2f;

//�x�N�g���v�Z�n
float FDot(Vector2f a, Vector2f b);
float FCross(Vector2f a, Vector2f b);
Vector2f Normalization(Vector2f vec);

