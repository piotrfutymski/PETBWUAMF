#include "GameInitiatior.h"


GameInitiator::GameInitiator()
{

	// przyk³adowe stworzenie initiatora (normalnie ma byæ na zewn¹trz klasy oczywiœcie)

	this->addUnitToFirstPlayer("Treasure Hunter", 1, 4);			// Wojownik w pierwszej lini na 4(pi¹tym polu)
	this->addUnitToFirstPlayer("Treasure Hunter", 1, 6);
	//this->addUnitToFirstPlayer("Lorhien Guard", 5, 5);
	this->addUnitToFirstPlayer("JorgvardScout", 0, 5);

	this->addUnitToSecondPlayer("Treasure Hunter", 1, 4);			// Wojownik w pierwszej lini na 4(pi¹tym polu)
	this->addUnitToSecondPlayer("Treasure Hunter", 1, 6);
	//this->addUnitToSecondPlayer("Palace Guard", 1, 5);
	this->addUnitToSecondPlayer("JorgvardScout", 0, 5);

	// I rozkazy

	this->addOrderToFirstPlayer("attack");
	this->addOrderToFirstPlayer("move");
	this->addOrderToFirstPlayer("charge");
	this->addOrderToFirstPlayer("prepare");
	this->addOrderToFirstPlayer("bleedingAttack");

	this->addOrderToSecondPlayer("attack");
	this->addOrderToSecondPlayer("move");
	this->addOrderToSecondPlayer("charge");
	this->addOrderToSecondPlayer("prepare");
	this->addOrderToSecondPlayer("bleedingAttack");
}

GameInitiator::~GameInitiator()
{
}

void GameInitiator::addUnitToFirstPlayer(const std::string & name, int line, int position)
{
	this->addUnit(name, {line,position });
}

void GameInitiator::addUnitToSecondPlayer(const std::string & name, int line, int position)
{
	this->addUnit(name, { Map::MAP_WIDTH - (1 + line),position });
}

void GameInitiator::addOrderToFirstPlayer(const std::string & name)
{
	_fPlayerOrders.push_back(name);
}

void GameInitiator::addOrderToSecondPlayer(const std::string & name)
{
	_sPlayerOrders.push_back(name);
}

void GameInitiator::addUnit(const std::string & name, const sf::Vector2i & p)
{
	_units.push_back({ name, p });
}
