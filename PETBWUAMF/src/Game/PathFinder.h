#pragma once
#include "SFML/Graphics.hpp"
#include <map>
#include <algorithm>

class PathFinder
{
public:
	PathFinder(int x, int y);
	~PathFinder();

	void addAllay(const sf::Vector2i & pos);															//sets this position as used by allaye
	void addEnemy(const sf::Vector2i & pos);															//sets this position as used by enymy

	bool isInArea(const sf::Vector2i & pos);				

	std::vector<sf::Vector2i> getGoodPositions(const sf::Vector2i & start, float move);					//get positions in range of move of unit on start position

private:
	int _xSize;
	int _ySize;

	std::vector<std::vector<int>> _matrix;

	void calculatePath(const sf::Vector2i & start, float move, std::vector<std::vector<float>> & positions);

	float getSquereDistance(const sf::Vector2i & first, const sf::Vector2i & second);



};

