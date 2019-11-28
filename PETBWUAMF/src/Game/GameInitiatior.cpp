#include "GameInitiatior.h"


GameInitiator::GameInitiator()
{

	// przyk³adowe stworzenie initiatora (normalnie ma byæ na zewn¹trz klasy oczywiœcie)

	this->addUnitToFirstPlayer("Heavy Spearman", 2, 4);
	this->addUnitToFirstPlayer("Heavy Spearman", 2, 5);
	this->addUnitToFirstPlayer("Heavy Spearman", 2, 3);
	this->addUnitToFirstPlayer("Heavy Swordman", 1, 6);
	this->addUnitToFirstPlayer("Heavy Swordman", 1, 2);
	this->addUnitToFirstPlayer("Lorhien Guard", 0, 5);
	this->addUnitToFirstPlayer("Heavy Crossbow Warden", 0, 4);
	this->addUnitToFirstPlayer("Heavy Crossbow Warden", 0, 3);

	this->addUnitToSecondPlayer("Light Militia", 2, 3);
	this->addUnitToSecondPlayer("Light Militia", 2, 4);
	this->addUnitToSecondPlayer("Light Militia", 2, 5);
	this->addUnitToSecondPlayer("Light Militia", 2, 6);
	this->addUnitToSecondPlayer("Southern Axeman", 2, 2);
	this->addUnitToSecondPlayer("Southern Axeman", 2, 7);

	this->addUnitToSecondPlayer("Southern Axeman", 0, 2);
	this->addUnitToSecondPlayer("Southern Axeman", 0, 7);
	this->addUnitToSecondPlayer("Gladiator", 0, 6);
	this->addUnitToSecondPlayer("Palace Guard", 0, 5);
	this->addUnitToSecondPlayer("Palace Guard", 0, 4);
	this->addUnitToSecondPlayer("Gladiator", 0, 3);

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
