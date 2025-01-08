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

			for (size_t y = 0; y < val; y++)
			{
				map[x + z * 16 + y * 16 * 16] = 1;
			}
		}
	}

	max_height = current_max_height;
}
