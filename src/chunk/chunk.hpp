#pragma once
#include "../perlin/perlin.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../block/block.hpp"
#include "../camera/camera.hpp"
#include "../shader/shader.hpp"
#include "../render/render.hpp"
#include <unordered_map>
#include <array>

struct Vec2Hash
{
	std::size_t operator()(const glm::vec2 &v) const
	{
		return std::hash<float>()(v.x) ^ (std::hash<float>()(v.y) << 1);
	}
};

struct Vec2Equal
{
	bool operator()(const glm::vec2 &a, const glm::vec2 &b) const
	{
		return a.x == b.x && a.y == b.y;
	}
};

struct Chunk
{
	int max_height;
	std::array<Block, 256 * 16 * 16> map;
};

using ChunkMap = std::unordered_map<glm::vec2, Chunk, Vec2Hash, Vec2Equal>;

class ChunkManager
{
public:
	ChunkMap chunk_map;

	void DestroyAroundPlayer();
	void CreateAroundPlayer();

	void Update();

	void GenerateChunk(int x_chunck, int y_chunck);
	void DeleteChunk(int x_chunck, int y_chunck);

	ChunkManager();

private:
	struct MVPMat
	{
		glm::mat4 projection;
		glm::mat4 view;
		glm::mat4 model;
	};
	struct MVPLoc
	{
		unsigned int projection;
		unsigned int model;
		unsigned int view;
	};

	void UpdateChunk();
	void Render();
	void RenderInit();

	unsigned int dirt_texture;

	Shader *shader;
	MVPMat mvp_mat;
	MVPLoc shader_loc;
	RenderData cube_render_data;
};