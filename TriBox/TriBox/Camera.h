#pragma once
#include <memory>

struct Rect;
template<typename T> 
struct Vector2D;
typedef Vector2D<float> Vector2f;
typedef Vector2f Position2f;
class Player;
class Stage;
class Camera
{
private:
	std::weak_ptr<Player> focus;
	Position2f* pos;
	Stage& stage;
public:
	Camera(Stage& _stage);
	~Camera();

	void SetFocus(std::shared_ptr<Player> c);

	const Position2f& GetPosition()const;
	
	const Rect& GetViewport() const;

	void Update();
};

