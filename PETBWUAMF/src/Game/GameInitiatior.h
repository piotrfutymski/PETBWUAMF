#pragma once
#include <vector>
#include "Unit.h"
#include "SFML/Graphics.hpp"

class Game;

class GameInitiator
{
public:

	friend class Game;

	GameInitiator();
	~GameInitiator();

	void addUnitToFirstPlayer(const std::string & name, int line, int position);
	void addUnitToSecondPlayer(const std::string & name, int line, int position);
	void addOrderToFirstPlayer(const std::string & name);
	void addOrderToSecondPlayer(const std::string & name);

private:

	std::vector<std::pair<std::string, sf::Vector2i>> _units;
	std::vector<std::string> _fPlayerOrders;
	std::vector<std::string> _sPlayerOrders;

	void addUnit(const std::string & name, const sf::Vector2i &);

};