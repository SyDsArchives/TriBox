#pragma once
#include "ObjectParent.h"

enum class RailType {
	normalRail,
	topRail,
	bottomRail,
};

template<typename T>
struct Vector2D;
typedef Vector2D <float> Vector2f;
typedef Vector2f Position2f;
class ElevatorRail :
	public ObjectParent
{
private:
	int imgPath;

	Position2f* pos;
public:
	ElevatorRail(Position2f& _pos, RailType _railType);
	~ElevatorRail();

	//•`‰æŠÖ”
	void Draw();
	//–ˆƒtƒŒ[ƒ€“®ìŠÖ”
	void Update();
};

