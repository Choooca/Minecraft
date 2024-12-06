#include <iostream>
#include "render/render.hpp"
#include "input/input.hpp"

int main(int argv, char **args)
{
	Render render;
	render.RenderInit();

	while (!Input::GetInstance()->ShouldQuit())
	{
		Input::GetInstance()->InputLoop();
		render.RenderUpdate();
	}

	return 0;
}