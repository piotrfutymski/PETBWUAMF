#pragma once
#include <SFML/Graphics.hpp>
#include "PathFinder.h"
#include "../Utility/Logger.h"
#include <array>

class Map
{
public:
	constexpr static int MAP_WIDTH = 16;
	constexpr static int MAP_HEIGHT = 10;

	using MapData_t = std::array<std::array<std::pair<size_t, int>, MAP_HEIGHT>, MAP_WIDTH>;		// Mo¿na dawaæ np. -2 dla kamieni i innych
		
	Map();
	~Map();

	//operations on map

	void setUnitPosition(size_t u, int o, const sf::Vector2i & pos);
	void removeUnitFromPosition(const sf::Vector2i & pos);
	bool moveUnitFromPosition(const sf::Vector2i & start, const sf::Vector2i & end);

	std::vector<size_t> getNeightbours(size_t u)const;
	std::vector< std::pair<size_t, int>> getNeightboursOfPos(const sf::Vector2i & pos)const;
	std::vector<sf::Vector2i> getPaths(size_t u, int move)const;
	std::vector<sf::Vector2i> posInFightAfterMove(size_t u, int move)const;

	size_t getDataFromPos(const sf::Vector2i & pos)const;

	sf::Vector2i findUnitPosition(size_t u)const;
	std::pair<sf::Vector2i, int> findUnit(size_t u)const;

private:

	MapData_t _mapData;

private:

	bool properPosition(const sf::Vector2i & pos)const;

	

};