#pragma once

#include <SDL2/SDL.h>
#include <glad/glad.h>
#include "../shader/shader.hpp"

class Render
{
public:
	typedef struct
	{
		unsigned int VAO;
		unsigned int VBO;
		unsigned int EBO;
	} RenderData;

	Render();

	void RenderInit();
	void RenderInitTriangles();
	void RenderUpdate();
	Shader *GetShader();
	void DestroyRender();

	RenderData *triangleRenderData;

private:
	Shader *shader;
	SDL_Window *window;
	SDL_GLContext context;
};
