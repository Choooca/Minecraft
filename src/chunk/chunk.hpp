#pragma once
#include "../perlin/perlin.hpp"
#include "../render/render.hpp"
#include "../MeshGenerator/MeshGenerator.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <array>
#include <cstdlib>

class Chunk
{
public:
	Chunk();
	Chunk(int x_chunk, int y_chunk);
	void Draw(Shader *shader);

	int map[256 * 16 * 16] = {0};
	int max_height = -1;

	RenderData mesh_data;

private:
	void GenerateMap();

	int x_chunk, z_chunk;
};