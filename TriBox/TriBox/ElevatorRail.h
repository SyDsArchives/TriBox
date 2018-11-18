#pragma once
#include "ObjectParent.h"
#include "Vector2D.h"

enum class RailType {
	normalRail,//type = 3
	bottomRail,//type = 4
	topRail,//type = 5
};

struct HitType {
	bool isHit;
	RailType railType;
};

class ElevatorRail :
	public ObjectParent
{
private:
	Position2f pos;
	RailType railType;

	int imgPath;

	//プレイヤーに合わせた移動
	void MoveElevatorRail(float _speed);
public:
	ElevatorRail(Position2f _pos, RailType _railType);
	~ElevatorRail();

	//描画関数
	void Draw();
	
	//毎フレーム動作関数
	void Update(float _speed);

	RailType GetRailType() { return railType; };

	HitType HitCheck(Position2f _pos);
};

