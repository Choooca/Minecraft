#include "camera.hpp"
#include "../input/input.hpp"
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

Camera::Camera()
{
	pos = glm::vec3(0, 0, 0.0f);
	fwd = glm::vec3(0, 0, -1);
	up = glm::vec3(0, 1, 0);

	Input::GetInstance()->RegisterCallback(SDLK_z, [&]()
										   { MoveCam(Up); });
	Input::GetInstance()->RegisterCallback(SDLK_s, [&]()
										   { MoveCam(Down); });
	Input::GetInstance()->RegisterCallback(SDLK_d, [&]()
										   { MoveCam(Right); });
	Input::GetInstance()->RegisterCallback(SDLK_q, [&]()
										   { MoveCam(Left); });
}

void Camera::MoveCam(Direction dir)
{

	switch (dir)
	{
	case Up:
		pos += fwd * 20.0f * Input::GetInstance()->GetDeltaTime();
		break;
	case Down:
		pos -= fwd * 20.0f * Input::GetInstance()->GetDeltaTime();
		break;
	case Right:
		pos += glm::cross(fwd, up) * 20.0f * Input::GetInstance()->GetDeltaTime();
		break;
	case Left:
		pos -= glm::cross(fwd, up) * 20.0f * Input::GetInstance()->GetDeltaTime();
		break;

	default:
		break;
	}
}