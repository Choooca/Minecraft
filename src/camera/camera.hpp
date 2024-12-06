#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera();

	glm::vec3 cam_pos;
	glm::vec3 cam_up;
	glm::vec3 cam_fwd;

	float pitch, yaw = 270;

	static Camera *current_cam;
	void InitCam();

private:
	~Camera();
};