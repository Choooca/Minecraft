#pragma once
#include "../render/render.hpp"
#include <vector>

struct BlockType
{
	int top_tex;
	int side_tex;
	int bottom_tex;
};

void create_mesh(RenderData *render_data, int map[], size_t array_size, int grid_x_size, int grid_y_size, int grid_z_size);
void add_face(std::vector<float> &vertices, const float face[], size_t face_size, glm::vec3 face_pos, float tex_index);
float *translate_face(const float face[], size_t size, glm::vec3 translate_vec);

// Texture index : 0 = Dirt, 1 = top_grass, 2 = side_grass

inline constexpr float back_face[36] = {
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f};

inline constexpr float front_face[36] = {
	-0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f};

inline constexpr float left_face[36] = {
	-0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f};

inline constexpr float right_face[36] = {
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f};

inline constexpr float bottom_face[36] = {
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f};

inline constexpr float top_face[36] = {
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f};
