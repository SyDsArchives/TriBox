#pragma once
#include "ObjectParent.h"
#include "Vector2D.h"

enum class RailType {
	normalRail,//type = 3
	bottomRail,//type = 4
	topRail,//type = 5
};

class ElevatorRail :
	public ObjectParent
{
private:
	Position2f pos;

	int imgPath;

	//プレイヤーに合わせた移動
	void MoveBlock(float _speed);
public:
	ElevatorRail(Position2f _pos, RailType _railType);
	~ElevatorRail();

	//描画関数
	void Draw();
	
	//毎フレーム動作関数
	void Update(float _speed);
};

