#include "input.hpp"

Input *Input::instance = nullptr;

Input *Input::GetInstance()
{
	if (Input::instance == nullptr)
		Input::instance = new Input;
	return Input::instance;
}

Input::Input()
{
	current_time = SDL_GetTicks();
	last_time = 0.0f;
	delta_time = 0.0f;
	quit = false;
	Init();
}

void Input::Init()
{
	SDL_SetRelativeMouseMode(SDL_TRUE);
}

float Input::GetDeltaTime()
{
	return delta_time;
}

void Input::InputLoop()
{
	CalculateDeltaTime();

	Camera *cam = Camera::current_cam;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_KEYDOWN:
			keys[event.key.keysym.sym] = true;
			break;
		case SDL_KEYUP:
			keys[event.key.keysym.sym] = false;
			break;
		case SDL_MOUSEMOTION:

			cam->yaw += event.motion.xrel * 10.0f * delta_time;
			cam->pitch -= event.motion.yrel * 10.0f * delta_time;

			if (cam->pitch > 89.0f)
				cam->pitch = 89.0f;
			if (cam->pitch < -89.0f)
				cam->pitch = -89.0f;

			glm::vec3 direction;
			direction.x = cos(glm::radians(cam->yaw)) * cos(glm::radians(cam->pitch));
			direction.y = sin(glm::radians(cam->pitch));
			direction.z = sin(glm::radians(cam->yaw)) * cos(glm::radians(cam->pitch));
			Camera::current_cam->cam_fwd = glm::normalize(direction);
			break;
		default:
			break;
		}
	};

	if (keys[SDLK_z])
		cam->cam_pos += Camera::current_cam->cam_fwd * 5.0f * delta_time;
	if (keys[SDLK_s])
		cam->cam_pos -= Camera::current_cam->cam_fwd * 5.0f * delta_time;
	if (keys[SDLK_q])
		cam->cam_pos -= glm::cross(Camera::current_cam->cam_fwd, Camera::current_cam->cam_up) * 5.0f * delta_time;
	if (keys[SDLK_d])
		cam->cam_pos += glm::cross(Camera::current_cam->cam_fwd, Camera::current_cam->cam_up) * 5.0f * delta_time;

	if (event.type == SDL_QUIT)
		quit = true;
}

void Input::Test()
{
	std::cout << "ca glisse" << std::endl;
}

bool Input::ShouldQuit()
{
	return quit;
}

void Input::CalculateDeltaTime()
{
	current_time = SDL_GetTicks();
	delta_time = (current_time - last_time) / 1000.0f;
	last_time = current_time;
}