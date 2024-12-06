#include "render.hpp"
#include <string>
#include "../block/block.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

Render::Render() {};

void Render::RenderInit()
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	std::string title = "Minecraft";

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	if (!window)
	{
		std::cout << "Failed To Create Window : " << SDL_GetError() << std::endl;
		exit(-1);
	}

	context = SDL_GL_CreateContext(window);
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

	shader = new Shader("C:/LearnCpp/Minecraft/shader/default.vert", "C:/LearnCpp/Minecraft/shader/default.frag");

	glEnable(GL_DEPTH_TEST);

	myCam = new Camera;

	InitTexture("C://LearnCpp//Minecraft//textures//dirt.jpg", &dirt_texture);
	InitMatrix();
	RenderInitCube();
	RenderInitTriangles();
}

void Render::InitTexture(std::string path, unsigned int *texture)
{
	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, *texture);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int height, width;
	unsigned char *data = stbi_load(path.c_str(), &width, &height, 0, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);
}

void Render::InitMatrix()
{
	projLoc = glGetUniformLocation(shader->ID, "projection");
	modelLoc = glGetUniformLocation(shader->ID, "model");
	viewLoc = glGetUniformLocation(shader->ID, "view");

	projMat = glm::mat4(1.0f);
	projMat = glm::perspective(glm::radians(60.0f), 800.f / 600.f, .1f, 100.f);

	viewMat = glm::mat4(1.0f);
	viewMat = glm::lookAt(Camera::current_cam->cam_pos, Camera::current_cam->cam_pos + Camera::current_cam->cam_fwd, Camera::current_cam->cam_up);

	modelMat = glm::mat4(1.0f);
}

void Render::RenderInitTriangles()
{
	float vertices[] = {
		0.0f, .5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f};

	glGenVertexArrays(1, &triangleRenderData->VAO);
	glGenBuffers(1, &triangleRenderData->VBO);

	glBindVertexArray(triangleRenderData->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, triangleRenderData->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Render::RenderInitCube()
{
	float vertices[] = {
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

		-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f};

	glGenVertexArrays(1, &cubeRenderData->VAO);
	glGenBuffers(1, &cubeRenderData->VBO);

	glBindVertexArray(cubeRenderData->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, cubeRenderData->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void *)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Render::RenderUpdate()
{
	viewMat = glm::mat4(1.0f);
	viewMat = glm::lookAt(Camera::current_cam->cam_pos, Camera::current_cam->cam_pos + Camera::current_cam->cam_fwd, Camera::current_cam->cam_up);

	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projMat));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMat));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, dirt_texture);

	glClearColor(.1f, .1f, .1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Block::CreateBlock(glm::vec3(0, 0, 0));
	Block::CreateBlock(glm::vec3(0, 1, 0));
	Block::CreateBlock(glm::vec3(2, 1, 0));

	for (Block *block : Block::list)
	{
		glBindVertexArray(cubeRenderData->VAO);
		modelMat = glm::translate(glm::mat4(1.0f), block->position);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
		shader->use();
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	SDL_GL_SwapWindow(window);
}

Shader *Render::GetShader()
{
	return shader;
}

SDL_Window *Render::GetWindow()
{
	return window;
}

Render::~Render()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
}