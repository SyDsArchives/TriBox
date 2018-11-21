#include "Camera.h"
#include "Stage.h"
#include "Vector2D.h"
#include "Geometry.h"
#include "Player.h"
#include "GameSystem.h"

#include <assert.h>

#include"DxLib.h"

Camera::Camera(Stage& _stage):stage(_stage)
{

}

Camera::~Camera()
{
}

void Camera::SetFocus(std::shared_ptr<Player> c)
{
	focus = c;
}

const Position2f & Camera::GetPosition() const
{
	return Position2f(0,0);
}

const Rect_f& Camera::GetViewport() const
{
	auto& size = GameSystem::GameInstance().GetWindowSize();
	return Rect_f(pos->y - size.top / 2, 0, 0, 0);
}

void Camera::Update()
{
	assert(!focus.expired());
	const Rect_f& range = stage.GetStageSize();
	const Rect_f& size = GameSystem::GameInstance().GetWindowSize();

	pos = &focus.lock()->GetPosition();

	Rect_f rect = size;
	Rect_f rect2 = range;

	//ƒJƒƒ‰ˆÊ’u‚Ì•â³
	if (rect.Right() > rect2.Right())
	{
		focus.lock()->PlayerMoveLimit(false);
		stage.SetStageSpeed(0.f);
		DrawFormatString(0, 150, GetColor(255, 255, 255), "‰E‚Í‚¶");
	}
	else
	{
		focus.lock()->PlayerMoveLimit(true);
		if (pos->x >= WindowSizeX / 2 && focus.lock()->GetPlayerDirection() == PlayerDirection::right)
		{
			stage.SetStageSpeed(focus.lock()->GetSpeed());
		}
		else
		{
			stage.SetStageSpeed(0.f);
		}
	}
}
