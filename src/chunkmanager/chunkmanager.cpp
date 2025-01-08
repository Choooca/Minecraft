#include "chunkmanager.hpp"

ChunkManager::ChunkManager()
{
	RenderInit();
	InitTexture("C://LearnCpp//Minecraft//textures//texture_tile.jpg", &dirt_texture);
	RenderInitCube(&cube_render_data);
}

void ChunkManager::RenderInit()
{
	shader = new Shader("C:/LearnCpp/Minecraft/shader/default.vert", "C:/LearnCpp/Minecraft/shader/default.frag");

	shader_loc.projection = glGetUniformLocation(shader->ID, "projection");
	shader_loc.model = glGetUniformLocation(shader->ID, "model");
	shader_loc.view = glGetUniformLocation(shader->ID, "view");

	mvp_mat.projection = glm::mat4(1.0f);
	mvp_mat.projection = glm::perspective(glm::radians(60.0f), 1920.f / 1080.f, .1f, 1000.f);
}

void ChunkManager::Update(Camera &cam)
{
	Render(cam);
}

void ChunkManager::Render(Camera &cam)
{
	mvp_mat.view = glm::mat4(1.0f);
	mvp_mat.view = glm::lookAt(cam.pos, cam.pos + cam.fwd, cam.up);

	shader->use();

	glBindVertexArray(cube_render_data.VAO);

	glUniformMatrix4fv(shader_loc.projection, 1, GL_FALSE, glm::value_ptr(mvp_mat.projection));
	glUniformMatrix4fv(shader_loc.view, 1, GL_FALSE, glm::value_ptr(mvp_mat.view));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, dirt_texture);

	for (auto &[key, chunk] : chunk_map)
	{
		glm::mat4 model_mat = glm::translate(glm::mat4(1.0f), glm::vec3(key.x * CHUNK_SIZE, 0, key.y * CHUNK_SIZE));
		shader->setMat4("model", model_mat);
		chunk.Draw(shader);
	}

	glUseProgram(0);
	glBindVertexArray(0);
}

void ChunkManager::GenerateChunk(int x_chunk, int y_chunk)
{
	if (ChunkManager::chunk_map.find(glm::vec2(x_chunk, y_chunk)) != ChunkManager::chunk_map.end())
		return;

	chunk_map[glm::vec2(x_chunk, y_chunk)] = Chunk(x_chunk, y_chunk);
}

void ChunkManager::DeleteChunk(int x_chunk, int y_chunk)
{
	chunk_map.erase(glm::vec2(x_chunk, y_chunk));
}