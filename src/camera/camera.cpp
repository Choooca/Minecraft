#include "camera.hpp"

Camera *Camera::current_cam = nullptr;

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
}

Camera::~Camera()
{
	if (current_cam = this)
		current_cam = NULL;
}