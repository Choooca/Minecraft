#pragma once

#include <SDL2/SDL.h>
#include <glad/glad.h>
#include "../shader/shader.hpp"
#include "../camera/camera.hpp"
#include <string>

typedef struct
{
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	int n_vertices;
} RenderData;

void RenderInitCube(RenderData *render_data);
void RenderInitTriangles(RenderData *render_data);
void InitTexture(std::string path, unsigned int *texture);

class Render
{
public:
	Render();

	void RenderInit();
	SDL_Window *GetWindow();

	void BeginRender();
	void EndRender();

	~Render();

private:
	SDL_Window *window;
	SDL_GLContext context;
};
