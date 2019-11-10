#pragma once
#include "SFML/Graphics.hpp"

class PathFinder
{
public:
	PathFinder(int x, int y);
	~PathFinder();

	void addAllay(const sf::Vector2i & pos);
	void addEnemy(const sf::Vector2i & pos);

	bool isInArea(const sf::Vector2i & pos);

	bool pathExist(const sf::Vector2i & start, const sf::Vector2i & target, float move);

private:
	int _xSize;
	int _ySize;

	std::vector<std::vector<int>> _matrix;



};