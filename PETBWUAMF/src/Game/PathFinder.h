#pragma once
#include "SFML/Graphics.hpp"
#include <map>
#include <algorithm>

class PathFinder
{
public:
	PathFinder(int x, int y);
	~PathFinder();

	void addAllay(const sf::Vector2i & pos);
	void addEnemy(const sf::Vector2i & pos);

	bool isInArea(const sf::Vector2i & pos);

	std::vector<sf::Vector2i> getGoodPositions(const sf::Vector2i & start, int move);

private:
	int _xSize;
	int _ySize;

	std::vector<std::vector<int>> _matrix;

	void calculatePath(const sf::Vector2i & start, float move, std::vector<std::vector<float>> & positions);

	float getSquereDistance(const sf::Vector2i & first, const sf::Vector2i & second);



};

