#include "ConsoleUI.h"



ConsoleUI::ConsoleUI()
{
}



void ConsoleUI::logState(int owner)const
{
	Logger::log("---------------------------------------------------------");
	Logger::log("------------------------New Turn-------------------------");
	Logger::log("---------------------------------------------------------");
	this->logStateUnits(owner);
	this->logStateUnits((owner + 1) % 2);
	this->logStateOrders(owner);
	this->logSimpleMap();
	Logger::log("---------------------------------------------------------");
	Logger::log(this->_game->getActiveUnit()->getPrototype()->getName() + "'s Turn.");
}

void ConsoleUI::logStateUnits(int owner)const
{
	Logger::log("---------------------------------------------------------");
	Logger::log("---------------------Player " + std::to_string(owner) + " Units----------------------");
	Logger::log("---------------------------------------------------------");
	for (auto &x : this->_game->getHolder())
	{
		if (x->getOwner() == owner)
		{
			Logger::logW("ID:" + std::to_string(x->getID()) + " Name: ");
			x->getSimpleInfo();
			/*Logger::log(std::to_string(x->getID()) + ": " + x->getPrototype()->getName() + " on pos (" + std::to_string(x->getPosition().x) + "," + std::to_string(x->getPosition().y) + ")");
			Logger::log("Attack: " + std::to_string(x->getAttack()) + " Protection: " + std::to_string(x->getProtection()) + " Health: " + std::to_string(x->getHealth()));
			Logger::log("---------------------------------------------------------");*/
		}
	}
}
void ConsoleUI::logStateOrders(int owner)const
{
	Logger::log("---------------------------------------------------------");
	Logger::log("--------------------Player " + std::to_string(owner) + " Orders----------------------");
	Logger::log("---------------------------------------------------------");
	for (auto &x : _orders)
	{
		if (x->getOwner() == owner)
		{
			Logger::log(std::to_string(x->getID()) + ": " + x->getPrototype()->getName());
			Logger::log("---------------------------------------------------------");
		}
	}
}


void  ConsoleUI::makeMove()
{
	Logger::log("---------------------------------------------------------");
	Logger::log("----------------------Make a move------------------------");
	Logger::log("---------------------------------------------------------");


	Logger::logW("ID:" + std::to_string(_activeUnit->getID()) + " Name: ");
	_activeUnit->getSimpleInfo();
	for (auto &x : this->getPossibleOrders())
	{
		Logger::logW(std::to_string(x->getID()) + ": " + x->getPrototype()->getName() + " ");
	}
	Logger::log("");
	Logger::log("---------------------------------------------------------");
}

std::vector<std::vector<char>> ConsoleUI::logStartMap()const
{
	int sizeX = Unit::MAXPOS.x;
	int sizeY = Unit::MAXPOS.y;
	std::vector<std::vector<char>> map;
	//char map[16][10];
	for (int x = 0; x <= sizeX; x++)
	{
		map.push_back(std::vector<char>());
		for (int y = 0; y <= sizeY; y++)
		{
			map[x].push_back('O');
		}
	}
	return map;
}
void ConsoleUI::logSimpleMap()const
{
	auto map = logStartMap();


	for (auto &unit : _units)
	{
		if (unit->getOwner() == 0)
			map[unit->getPosition().x][unit->getPosition().y] = 'F';
		else
			map[unit->getPosition().x][unit->getPosition().y] = 'S';
	}
	map[_activeUnit->getPosition().x][_activeUnit->getPosition().y] = 'A';

	logConstructMap(map);

}

void ConsoleUI::logMoveMap(Order *order, int i)const
{
	auto map = logStartMap();

	for (auto x : order->getProperTargets(_activeUnit, i))
	{
		map[x.pos.x][x.pos.y] = 'M';
	}

	for (auto &unit : _units)
	{
		if (unit->getOwner() == 0)
			map[unit->getPosition().x][unit->getPosition().y] = 'F';
		else
			map[unit->getPosition().x][unit->getPosition().y] = 'S';
	}
	map[_activeUnit->getPosition().x][_activeUnit->getPosition().y] = 'A';

	logConstructMap(map);
}

void ConsoleUI::logConstructMap(std::vector<std::vector<char>> map) const
{
	int sizeX = Unit::MAXPOS.x;
	int sizeY = Unit::MAXPOS.y;
	Logger::logW("    |");
	for (int y = 0; y <= sizeY; y++)
	{
		Logger::logW(std::to_string(y));
		Logger::logW("|");
	}
	Logger::log("");
	Logger::log("  |X|X|X|X|X|X|X|X|X|X|X|X|");
	//Logger::log("   XXXXXXXXXXXX");
	for (int x = 0; x <= sizeX; x++)
	{
		if (x < 10)
			Logger::logW(std::to_string(x) + " ");
		else
			Logger::logW(std::to_string(x));
		Logger::logW("|X|");
		for (int y = 0; y <= sizeY; y++)
		{
			if (map[x][y] == 'A')
				std::cout << yellow;

			else if (map[x][y] == 'F')
				std::cout << blue;

			else if (map[x][y] == 'S')
				std::cout << red;

			else if (map[x][y] == 'M')
				std::cout << green;
			Logger::logW(map[x][y]);
			std::cout << white;
			Logger::logW("|");
		}
		Logger::logW("X|");
		Logger::log("");
	}
	//Logger::log("|X|X|X|X|X|X|X|X|X|X|X|X|");
	Logger::log("  |X|X|X|X|X|X|X|X|X|X|X|X|");
}



ConsoleUI::~ConsoleUI()
{
}
