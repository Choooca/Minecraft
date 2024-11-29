#pragma once

#include <SDL2/SDL.h>
#include <glad/glad.h>
#include "../shader/shader.hpp"

class Render
{
public:
	typedef struct
	{
		GLuint VAO;
		GLuint VBO;
		GLuint EBO;
	} RenderData;

	Render();

	void RenderInit();
	void RenderUpdate();
	Shader *GetShader();
	SDL_Window *GetWindow();

	~Render();

	RenderData *cubeRenderData = new RenderData;
	RenderData *triangleRenderData = new RenderData;

private:
	Shader *shader;
	SDL_Window *window;
	SDL_GLContext context;

	void RenderInitTriangles();
	void RenderInitCube();
};
