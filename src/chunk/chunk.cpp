#include "chunk.hpp"

ChunkManager::ChunkManager()
{
	RenderInit();
	InitTexture("C://LearnCpp//Minecraft//textures//dirt.jpg", &dirt_texture);
	RenderInitCube(&cube_render_data);
}

void ChunkManager::RenderInit()
{
	shader = new Shader("C:/LearnCpp/Minecraft/shader/default.vert", "C:/LearnCpp/Minecraft/shader/default.frag");

	shader_loc.projection = glGetUniformLocation(shader->ID, "projection");
	shader_loc.model = glGetUniformLocation(shader->ID, "model");
	shader_loc.view = glGetUniformLocation(shader->ID, "view");

	mvp_mat.projection = glm::mat4(1.0f);
	mvp_mat.projection = glm::perspective(glm::radians(60.0f), 800.f / 600.f, .1f, 100.f);
}

void ChunkManager::DestroyAroundPlayer()
{
	int current_x_player_chunk = (int)Camera::current_cam->cam_pos.x / 16;
	int current_y_player_chunk = (int)Camera::current_cam->cam_pos.z / 16;

	for (int x = -1 + current_x_player_chunk; x <= 1 + current_x_player_chunk; x++)
	{
		for (int y = -1 + current_y_player_chunk; y <= 1 + current_y_player_chunk; y++)
		{
			DeleteChunk(x, y);
		}
	}
}

void ChunkManager::CreateAroundPlayer()
{
	int current_x_player_chunk = (int)Camera::current_cam->cam_pos.x / 16;
	int current_y_player_chunk = (int)Camera::current_cam->cam_pos.z / 16;

	for (int x = -1 + current_x_player_chunk; x <= 1 + current_x_player_chunk; x++)
	{
		for (int y = -1 + current_y_player_chunk; y <= 1 + current_y_player_chunk; y++)
		{
			GenerateChunk(x, y);
		}
	}
}

void ChunkManager::Update()
{
	Render();
}

void ChunkManager::Render()
{
	mvp_mat.view = glm::mat4(1.0f);
	mvp_mat.view = glm::lookAt(Camera::current_cam->cam_pos, Camera::current_cam->cam_pos + Camera::current_cam->cam_fwd, Camera::current_cam->cam_up);

	glUniformMatrix4fv(shader_loc.projection, 1, GL_FALSE, glm::value_ptr(mvp_mat.projection));
	glUniformMatrix4fv(shader_loc.view, 1, GL_FALSE, glm::value_ptr(mvp_mat.view));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, dirt_texture);

	glBindVertexArray(cube_render_data.VAO);

	for (const auto &[key, chunk] : chunk_map)
	{

		for (size_t i = 0; i < 16 * 16 * chunk.max_height; i++)
		{
			glm::mat4 model_mat = glm::translate(glm::mat4(1.0f), chunk.map[i].position);
			glUniformMatrix4fv(shader_loc.model, 1, GL_FALSE, glm::value_ptr(model_mat));
			shader->use();
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}
}

void ChunkManager::UpdateChunk()
{
	int last_x_player_chunk, last_y_player_chunk;
	int current_x_player_chunk, current_y_player_chunk;

	last_x_player_chunk = (int)Camera::current_cam->last_pos.x / 16;
	last_y_player_chunk = (int)Camera::current_cam->last_pos.z / 16;

	current_x_player_chunk = (int)Camera::current_cam->cam_pos.x / 16;
	current_y_player_chunk = (int)Camera::current_cam->cam_pos.z / 16;

	if (last_x_player_chunk != current_x_player_chunk ||
		last_y_player_chunk != current_y_player_chunk)
	{
		for (int x = -1 + last_x_player_chunk; x <= 1 + last_x_player_chunk; x++)
		{
			for (int y = -1 + last_y_player_chunk; y <= 1 + last_y_player_chunk; y++)
			{
				DeleteChunk(x, y);
			}
		}

		for (int x = -1 + current_x_player_chunk; x <= 1 + current_x_player_chunk; x++)
		{
			for (int y = -1 + current_y_player_chunk; y <= 1 + current_y_player_chunk; y++)
			{
				GenerateChunk(x, y);
			}
		}
	}
}

void ChunkManager::GenerateChunk(int x_chunk, int y_chunk)
{

	if (ChunkManager::chunk_map.find(glm::vec2(x_chunk, y_chunk)) != ChunkManager::chunk_map.end())
		return;

	int current_max_height = -1;
	for (int x = 0; x < 16; x++)
	{
		for (int y = 0; y < 16; y++)
		{
			float val = 0;

			float freq = 1;
			float amp = 10;

			for (int i = 0; i < 5; i++)
			{
				val += perlin((x + x_chunk * 16) * freq / 16, (y + y_chunk * 16) * freq / 16) * amp;

				freq *= 2;
				amp /= 2;
			}

			if (val > current_max_height)
				current_max_height = val;

			for (size_t i = 0; i < val; i++)
			{
				if (x % 16 + i * 256 + y % 16 * 16 > 256 * 16 * 16)
					std::cout << "oui" << std::endl;
				chunk_map[glm::vec2(x_chunk, y_chunk)].map.at(x % 16 + i * 256 + y % 16 * 16) = Block(glm::vec3(x + x_chunk * 16, i, y + y_chunk * 16));
			}
		}
	}

	chunk_map[glm::vec2(x_chunk, y_chunk)].max_height = current_max_height;
}

void ChunkManager::DeleteChunk(int x_chunk, int y_chunk)
{
	chunk_map.erase(glm::vec2(x_chunk, y_chunk));
}