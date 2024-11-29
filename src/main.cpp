#include <iostream>
#include <SDL2/SDL.h>
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

	glm::vec3 camPos = glm::vec3(0, 0, 3.0f);
	glm::vec3 camFront = glm::vec3(0, 0, -1);
	glm::vec3 camUp = glm::vec3(0, 1, 0);

	unsigned int projLoc = glGetUniformLocation(shader->ID, "projection");
	unsigned int modelLoc = glGetUniformLocation(shader->ID, "model");
	unsigned int viewLoc = glGetUniformLocation(shader->ID, "view");

	glm::mat4 projMat = glm::mat4(1.0f);
	projMat = glm::perspective(glm::radians(60.0f), 800.f / 600.f, .1f, 100.f);

	glm::mat4 viewMat = glm::mat4(1.0f);
	viewMat = glm::lookAt(camPos, camPos + camFront, camUp);

	glm::mat4 modelMat = glm::mat4(1.0f);

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
		int xMousePos, yMousePos;

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
				camFront = glm::normalize(direction);
				break;
			default:
				break;
			}
		};

		currentTime = SDL_GetTicks();
		deltaTime = (currentTime - lastTime) / 1000.0f;
		lastTime = currentTime;

		if (keys[SDLK_z])
			camPos += camFront * 5.0f * deltaTime;
		if (keys[SDLK_s])
			camPos -= camFront * 5.0f * deltaTime;
		if (keys[SDLK_q])
			camPos -= glm::cross(camFront, camUp) * 5.0f * deltaTime;
		if (keys[SDLK_d])
			camPos += glm::cross(camFront, camUp) * 5.0f * deltaTime;

		viewMat = glm::mat4(1.0f);
		viewMat = glm::lookAt(camPos, camPos + camFront, camUp);

		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projMat));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMat));

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