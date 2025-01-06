#include <iostream>
#include <SDL2/SDL.h>
#include "render/render.hpp"
#include "input/input.hpp"
#include "perlin/perlin.hpp"
#include "block/block.hpp"
#include "chunk/chunk.hpp"
#include "camera/camera.hpp"

int main(int argv, char **args)
{
	Render render;
	render.RenderInit();

	new Camera();

	ChunkManager chunk_manager;

	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			chunk_manager.GenerateChunk(i, j);
		}
	}

	while (!Input::GetInstance()->ShouldQuit())
	{
		render.BeginRender();

		Input::GetInstance()->InputLoop();
		chunk_manager.Update();

		render.EndRender();
	}
	return 0;
}
