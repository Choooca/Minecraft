#pragma once

#include <SDL2/SDL.h>
#include <glad/glad.h>
#include "../shader/shader.hpp"
#include "../camera/camera.hpp"
#include <string>

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

	unsigned int dirt_texture;

	RenderData *cubeRenderData = new RenderData;
	RenderData *triangleRenderData = new RenderData;

	Camera *myCam;

private:
	unsigned int projLoc;
	unsigned int modelLoc;
	unsigned int viewLoc;

	glm::mat4 projMat;
	glm::mat4 viewMat;
	glm::mat4 modelMat;

	Shader *shader;
	SDL_Window *window;
	SDL_GLContext context;

	void RenderInitTriangles();
	void RenderInitCube();
	void InitTexture(std::string path, unsigned int *texture);
	void InitMatrix();
};
