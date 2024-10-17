#include <iostream>
#include <glad/glad.h>
#include <SDL2/SDL.h>
#include "shader/shader.hpp"

int main(int argv, char **args)
{
	float vertices[] = {
		0.0f, .5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f};

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_Window *window = SDL_CreateWindow("Minecraft", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	if (!window)
	{
		std::cout << "Failed To Create Window : " << SDL_GetError() << std::endl;
		exit(-1);
	}

	SDL_GLContext context = SDL_GL_CreateContext(window);
	if (!context)
	{
		std::cout << "Failed to create Context : " << SDL_GetError() << std::endl;
		exit(-1);
	}

	SDL_GL_MakeCurrent(window, context);

	if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
	{
		std::cout << "Failed to initialized glad : " << glGetError() << std::endl;
		exit(-1);
	}

	glViewport(0, 0, 800, 600);

	Shader shader("C:/LearnCpp/Minecraft/shader/default.vert", "C:/LearnCpp/Minecraft/shader/default.frag");

	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	SDL_Event event;
	bool quit = false;

	while (!quit)
	{
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT)
		{
			quit = true;
		}

		glClearColor(.1f, .1f, .1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAO);

		shader.use();
		glDrawArrays(GL_TRIANGLES, 0, 3);

		SDL_GL_SwapWindow(window);
	}

	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}