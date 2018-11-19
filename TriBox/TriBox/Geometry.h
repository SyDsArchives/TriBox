#pragma once
//�v���W�F�N�g�S�̂ŕK�v�ȋ@�\�̂�

const int WindowSizeX = 978;
const int WindowSizeY = 50 * 11;

template<typename T>
struct Rect {
	Rect() {};
	Rect(T _top, T _bottom, T _left, T _right)
		:top(_top), bottom(_bottom), right(_right), left(_left) {};

	T top;
	T bottom;
	T right;
	T left;
};

