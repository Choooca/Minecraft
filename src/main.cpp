#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include "render/render.hpp"
#include "input/input.hpp"
#include "perlin/perlin.hpp"
#include "block/block.hpp"
#include "chunkmanager/chunkmanager.hpp"
#include "camera/camera.hpp"

RenderData test;
MVPMat my_mat;
MVPLoc my_loc;
Shader *shader;

int main(int argv, char **args)
{
	Render render;
	render.RenderInit();

	Camera cam;

	ChunkManager chunk_manager;

	for (size_t x = 0; x < 10; x++)
	{
		for (size_t z = 0; z < 10; z++)
		{
			chunk_manager.GenerateChunk(x, z);
		}
	}

	while (!Input::GetInstance()->ShouldQuit())
	{
		render.BeginRender();

		Input::GetInstance()->InputLoop(cam);
		chunk_manager.Update(cam);

		render.EndRender();
	}

	return 0;
}
