#include <iostream>
#include <glad/glad.h>
#include <SDL2/SDL.h>
#include "shader/shader.hpp"
#include "render/render.hpp"

int main(int argv, char **args)
{

	Render render;
	render.RenderInit();
	render.RenderInitTriangles();

	SDL_Event event;
	bool quit = false;

	while (!quit)
	{
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT)
		{
			quit = true;
		}

		render.RenderUpdate();
	}

	render.DestroyRender();

	return 0;
}