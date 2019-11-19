#pragma once
#include <array>
#include <SFML/Graphics.hpp>
#include "../Utility/Logger.h"

#include "PathFinder.h"
#include "Unit.h"




class Map			// important - only map can change unit position!!! (and it is only thing it makes with unit)
{
public:

	constexpr static int MAP_WIDTH = 16;
	constexpr static int MAP_HEIGHT = 10;
	
	enum class SpotContent {
		Empty, Unit, Player0ControlZone, Player1ControlZone, DuoControlZone
	};

	struct Spot
	{
		Unit * unit{ nullptr };
		SpotContent content;
		sf::Vector2i position;
	};

	using MapData_t = std::array<std::array<Spot, MAP_HEIGHT>, MAP_WIDTH>;		
		
	Map();
	~Map();

	//operations on map
	//setting Info

	void setNewUnit(Unit * u, const sf::Vector2i & pos);						// set unit on proper position on map
	void destroyUnit(Unit * u);													// destroy unit from map
	void moveUnit(Unit * u, const sf::Vector2i & newPosition);					// move unit to new position

	//geting Info

	std::vector<Unit *> getNeightbours(Unit * u)const;							// get units in neightbourhood of given unit
	std::vector<Unit *> getAllayedNeightbours(Unit * u)const;					// get only allayed neightbours
	std::vector<Unit *> getEnymeNeightbours(Unit * u)const;						// get only enymy neightbours
	std::vector<Unit *> getNeightbours(const sf::Vector2i & pos)const;			// get neightbours of given position

	const Spot operator[](const sf::Vector2i & pos)const;						// get some map info about position
	std::vector<Spot> getPaths(Unit * u)const;									// get possible positions for unit move
	std::vector<Spot> getPathsEndingInZoneOfControle(Unit * u)const;			// get posiible postions for unit move where unit end in enymy zone of controle 
	std::vector<Spot> getPositionsInZoneOfControle(int player)const;			// get all spot in given player control zone
	std::vector<Spot> getPositionsWithUnit()const;								// get all positions contatining unit

private:

	MapData_t _mapData;

private:

	bool properPosition(const sf::Vector2i & pos)const;
	bool inArea(const sf::Vector2i & pos)const;
	void setZoneForUnit(Unit * u);
	void resetZoneForUnit(Unit * u);

	std::vector<Spot> getPositionsWihtContent(const SpotContent & content)const;

};