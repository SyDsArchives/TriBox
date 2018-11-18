#pragma once

struct ObjectHitType {
	bool isHit_Top;
	bool isHit_Right;
	bool isHit_Left;
	bool isHit_Bottom;
	bool isHit_All;
};

const int blocksize = 50;

class ObjectParent
{
private:

public:
	ObjectParent();
	~ObjectParent();
};

