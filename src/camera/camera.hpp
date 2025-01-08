#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Direction
{
	Up,
	Down,
	Left,
	Right
};

class Camera
{
public:
	Camera();

	glm::vec3 pos;
	glm::vec3 up;
	glm::vec3 fwd;

	glm::vec3 last_pos;

	float pitch, yaw = 270;

	void InitCam();

	void MoveCam(Direction dir);
};