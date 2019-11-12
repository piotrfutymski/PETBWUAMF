#pragma once
#include "SFML/Graphics.hpp"
#include <map>

class PathFinder
{
public:
	PathFinder(int x, int y);
	~PathFinder();

	void addAllay(const sf::Vector2i & pos);
	void addEnemy(const sf::Vector2i & pos);

	bool isInArea(const sf::Vector2i & pos);

	bool pathExist(const sf::Vector2i & start, const sf::Vector2i & target, float move);

	std::map<int, bool> getGoodPositions(const sf::Vector2i & start, int move);

private:
	int _xSize;
	int _ySize;

	std::vector<std::vector<int>> _matrix;

	bool _pathExist(const sf::Vector2i & start, const sf::Vector2i & target, float move, std::map<int, bool> & positions);

	float getSquereDistance(const sf::Vector2i & first, const sf::Vector2i & second);



};

