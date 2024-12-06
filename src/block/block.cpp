#include "block.hpp"

std::vector<Block *> Block::list;

Block::Block() {};
Block::Block(glm::vec3 pos) : position(pos) {};

Block *Block::CreateBlock()
{
	Block *newBlock = new Block;
	list.push_back(newBlock);
	return newBlock;
}

Block *Block::CreateBlock(glm::vec3 pos)
{
	Block *newBlock = new Block(pos);
	list.push_back(newBlock);
	return newBlock;
}