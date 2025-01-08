#include "chunk.hpp"

Chunk::Chunk() : Chunk(0, 0) {};

Chunk::Chunk(int x_chunk, int y_chunk) : x_chunk(x_chunk), z_chunk(y_chunk)
{
	GenerateMap();
	create_mesh(&mesh_data, map, 16 * 16 * max_height, 16, max_height, 16);
}

void Chunk::Draw(Shader *shader)
{
	glBindVertexArray(mesh_data.VAO);
	glDrawArrays(GL_TRIANGLES, 0, mesh_data.n_vertices);
}

void Chunk::GenerateMap()
{
	int current_max_height = -1;
	for (int x = 0; x < 16; x++)
	{
		for (int z = 0; z < 16; z++)
		{
			float val = 0;

			float freq = 1;
			float amp = 10;

			for (int i = 0; i < 5; i++)
			{
				val += perlin((x + x_chunk * 16) * freq / 16, (z + z_chunk * 16) * freq / 16) * amp;

				freq *= 2;
				amp /= 2;
			}

			if (val > current_max_height)
				current_max_height = val;

			for (size_t y = 0; y < val - 1; y++)
			{
				map[x + z * 16 + y * 16 * 16] = 1;
			}
			map[x + z * 16 + ((int)val - 1) * 16 * 16] = 2;
		}
	}

	int x_tree_pos = (std::rand() % 14) + 1;
	int y_tree_pos = 0;
	int z_tree_pos = (std::rand() % 14) + 1;

	while (map[x_tree_pos + z_tree_pos * 16 + (y_tree_pos + 1) * 256] != 0)
	{
		y_tree_pos++;
	}

	if (y_tree_pos + 5 > current_max_height)
		current_max_height = y_tree_pos + 5;

	for (size_t i = y_tree_pos; i < y_tree_pos + 4; i++)
		map[x_tree_pos + z_tree_pos * 16 + i * 256] = 3;

	for (size_t x = x_tree_pos - 1; x <= x_tree_pos + 1; x++)
	{
		for (size_t z = z_tree_pos - 1; z <= z_tree_pos + 1; z++)
		{
			for (size_t y = y_tree_pos + 3; y <= y_tree_pos + 5; y++)
			{
				map[x + z * 16 + y * 256] = 4;
			}
		}
	}

	max_height = current_max_height;
}
