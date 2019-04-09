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

	Rect cameraRect = size;
	
	//カメラ位置の補正
	if (cameraRect.Top() < range.endY - WindowSizeY / 2)
	{
		//focus.lock()->PlayerMoveLimit(false);
		stage.SetStageSpeed(0.f);
	}
	else
	{
		//focus.lock()->PlayerMoveLimit(true);
		if (pos->y >= WindowSizeY - 50 /*&& focus.lock()->GetPlayerDirection() == PlayerDirection::right*/)//マジックナンバー
		{
			//stage.SetStageSpeed(focus.lock()->GetSpeed());
			stage.SetStageSpeed(-focus.lock()->GetVelocity().y);
		}
		else if (pos->y <= WindowSizeY / 2 + 10 /*&& focus.lock()->GetPlayerDirection() == PlayerDirection::right*/)//マジックナンバー
		{
			stage.SetStageSpeed(-focus.lock()->GetSpeed());
		}
		else
		{
			stage.SetStageSpeed(0.f);
		}
	}
}
