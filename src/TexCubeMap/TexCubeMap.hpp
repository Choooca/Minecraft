#pragma once
#include <glad/glad.h>

class TexCubeMap
{
public:
	unsigned int textureID;

	TexCubeMap(const char *texPath);
};