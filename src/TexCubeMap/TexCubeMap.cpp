#include "TexCubeMap.hpp"

TexCubeMap::TexCubeMap(const char *texPath)
{
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
}