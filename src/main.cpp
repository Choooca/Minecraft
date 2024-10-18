#include <iostream>
#include <SDL2/SDL.h>
#include "render/render.hpp"

int main(int argv, char **args)
{

	Render render;
	render.RenderInit();

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