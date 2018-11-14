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

const Rect& Camera::GetViewport() const
{
	auto& size = GameSystem::GameInstance().GetWindowSize();
	return Rect(pos->y - size.top / 2, 0, 0, 0);
}

void Camera::Update()
{
	assert(!focus.expired());
	auto& range = stage.GetStageSize();
	auto& size = GameSystem::GameInstance().GetWindowSize();

	pos = &focus.lock()->GetPosition();

	//ƒJƒƒ‰ˆÊ’u‚Ì•â³
	if (pos->x - size.right / 2 < range.left)
	{
		pos->x = range.left + size.right / 2;
		DrawFormatString(0, 150, GetColor(255, 255, 255), "¶‚Í‚¶");
	}else if (pos->x + size.right / 2 > range.right)
	{
		pos->x = range.right - size.right / 2;
		DrawFormatString(0, 150, GetColor(255, 255, 255), "‰E‚Í‚¶");
	}
	else
	{
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
