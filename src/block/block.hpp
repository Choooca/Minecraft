#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <functional>

class Block
{
public:
	glm::vec3 position;

	static std::vector<Block *> list;

	static Block *CreateBlock();
	static Block *CreateBlock(glm::vec3 pos);

private:
	Block();
	Block(glm::vec3 pos);
};