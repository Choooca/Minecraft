#include <iostream>
#include <SDL2/SDL.h>
#include "camera/camera.hpp"
#include "render/render.hpp"
#include <map>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main(int argv, char **args)
{

	Render render;
	render.RenderInit();

	SDL_Event event;
	bool quit = false;

	float pitch, yaw = 270;

	auto currentTime = SDL_GetTicks();
	float deltaTime = 0.0f, lastTime = 0.0f;

	std::map<int, bool> keys;

	Shader *shader = render.GetShader();

	SDL_SetRelativeMouseMode(SDL_TRUE);

	unsigned int texture;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int height, width;
	unsigned char *data = stbi_load("C://LearnCpp//Minecraft//textures//dirt.jpg", &width, &height, 0, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);

	bool firstMouse = true;

	while (!quit)
	{
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

				yaw += event.motion.xrel * 10.0f * deltaTime;
				pitch -= event.motion.yrel * 10.0f * deltaTime;

				if (pitch > 89.0f)
					pitch = 89.0f;
				if (pitch < -89.0f)
					pitch = -89.0f;

				glm::vec3 direction;
				direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
				direction.y = sin(glm::radians(pitch));
				direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
				Camera::current_cam->cam_fwd = glm::normalize(direction);
				break;
			default:
				break;
			}
		};

		currentTime = SDL_GetTicks();
		deltaTime = (currentTime - lastTime) / 1000.0f;
		lastTime = currentTime;

		if (keys[SDLK_z])
			Camera::current_cam->cam_pos += Camera::current_cam->cam_fwd * 5.0f * deltaTime;
		if (keys[SDLK_s])
			Camera::current_cam->cam_pos -= Camera::current_cam->cam_fwd * 5.0f * deltaTime;
		if (keys[SDLK_q])
			Camera::current_cam->cam_pos -= glm::cross(Camera::current_cam->cam_fwd, Camera::current_cam->cam_up) * 5.0f * deltaTime;
		if (keys[SDLK_d])
			Camera::current_cam->cam_pos += glm::cross(Camera::current_cam->cam_fwd, Camera::current_cam->cam_up) * 5.0f * deltaTime;

		if (event.type == SDL_QUIT)
		{
			quit = true;
		}

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		render.RenderUpdate();
	}

	return 0;
}