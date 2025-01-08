#include "MeshGenerator.hpp"

void create_mesh(RenderData *render_data, int map[], size_t array_size, int grid_x_size, int grid_y_size, int grid_z_size)
{
	std::vector<float> vertices;

	int face_size = sizeof(front_face) / sizeof(front_face[0]);

	int count = 0;

	for (size_t i = 0; i < array_size; i++)
	{
		if (map[i] == 0)
			continue;

		count++;

		int y = i / (grid_x_size * grid_z_size);
		int z = (i - y * (grid_x_size * grid_z_size)) / grid_x_size;
		int x = i - z * grid_x_size - y * (grid_x_size * grid_z_size);

		bool is_grass = false;

		if (y == grid_y_size - 1 || map[i + grid_x_size * grid_z_size] == 0)
		{
			add_face(vertices, top_face, face_size, glm::vec3(x, y, z), 1);
			is_grass = true;
		}

		if (y == 0 || map[i - grid_x_size * grid_z_size] == 0)
			add_face(vertices, bottom_face, face_size, glm::vec3(x, y, z), 0);

		if (x == 0 || map[i - 1] == 0)
			add_face(vertices, left_face, face_size, glm::vec3(x, y, z), is_grass ? 2 : 0);

		if (x == grid_x_size - 1 || map[i + 1] == 0)
			add_face(vertices, right_face, face_size, glm::vec3(x, y, z), is_grass ? 2 : 0);

		if (z == grid_z_size - 1 || map[i + grid_x_size] == 0)
			add_face(vertices, front_face, face_size, glm::vec3(x, y, z), is_grass ? 2 : 0);

		if (z == 0 || map[i - grid_x_size] == 0)
			add_face(vertices, back_face, face_size, glm::vec3(x, y, z), is_grass ? 2 : 0);
	}

	glGenVertexArrays(1, &render_data->VAO);
	glGenBuffers(1, &render_data->VBO);

	glBindVertexArray(render_data->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, render_data->VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void *)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void *)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	render_data->n_vertices = vertices.size() / 6;
}

void add_face(std::vector<float> &vertices, const float face[], size_t face_size, glm::vec3 face_pos, float tex_index)
{
	float *translated_face = translate_face(face, face_size, face_pos);

	for (size_t i = 5; i < face_size; i += 6)
		translated_face[i] = tex_index;

	vertices.insert(vertices.end(), translated_face, translated_face + face_size);
}

float *translate_face(const float face[], size_t size, glm::vec3 translate_vec)
{
	float *translated_face = new float[size];

	for (size_t i = 0; i < size; i += 6)
	{
		translated_face[i] = face[i] + translate_vec.x;
		translated_face[i + 1] = face[i + 1] + translate_vec.y;
		translated_face[i + 2] = face[i + 2] + translate_vec.z;
		translated_face[i + 3] = face[i + 3];
		translated_face[i + 4] = face[i + 4];
	}

	return translated_face;
}