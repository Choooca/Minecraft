#include "camera.hpp"
#include "../input/input.hpp"
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

Camera *Camera::current_cam = nullptr;
bool Camera::already_init = false;

Camera::Camera()
{
	InitCam();
}

void Camera::InitCam()
{
	Camera::cam_pos = glm::vec3(0, 0, 3.0f);
	Camera::cam_fwd = glm::vec3(0, 0, -1);
	Camera::cam_up = glm::vec3(0, 1, 0);

	current_cam = this;

	if (!already_init)
	{
		Input::GetInstance()->RegisterCallback(SDLK_z, []()
											   { MoveCam(Up); });
		Input::GetInstance()->RegisterCallback(SDLK_s, []()
											   { MoveCam(Down); });
		Input::GetInstance()->RegisterCallback(SDLK_d, []()
											   { MoveCam(Right); });
		Input::GetInstance()->RegisterCallback(SDLK_q, []()
											   { MoveCam(Left); });
	}

	already_init = true;
}

void Camera::MoveCam(Direction dir)
{
	current_cam->last_pos = current_cam->cam_pos;

	switch (dir)
	{
	case Up:
		current_cam->cam_pos += Camera::current_cam->cam_fwd * 20.0f * Input::GetInstance()->GetDeltaTime();
		break;
	case Down:
		current_cam->cam_pos -= Camera::current_cam->cam_fwd * 20.0f * Input::GetInstance()->GetDeltaTime();
		break;
	case Right:
		current_cam->cam_pos += glm::cross(Camera::current_cam->cam_fwd, Camera::current_cam->cam_up) * 20.0f * Input::GetInstance()->GetDeltaTime();
		break;
	case Left:
		current_cam->cam_pos -= glm::cross(Camera::current_cam->cam_fwd, Camera::current_cam->cam_up) * 20.0f * Input::GetInstance()->GetDeltaTime();
		break;

	default:
		break;
	}
}

Camera::~Camera()
{
	if (current_cam = this)
		current_cam = NULL;
}