#include "ConsoleUI.h"



ConsoleUI::ConsoleUI()
{
}

void ConsoleUI::logState(const Game & game)const
{
	Logger::log("---------------------------------------------------------");
	Logger::log("------------------------New Turn-------------------------");
	Logger::log("---------------------------------------------------------");
	this->logStateUnits(game, game.getActivePlayer());
	this->logStateUnits(game, (game.getActivePlayer()+1)%2);
	this->logStateOrders(game);
	this->logSimpleMap(game);
	Logger::log("---------------------------------------------------------");
	Logger::log(game.getActiveUnit()->getPrototype()->getName() + "'s Turn.");
}

void ConsoleUI::logStateUnits(const Game & game, int owner)const
{
	Logger::log("---------------------------------------------------------");
	Logger::log("---------------------Player " + std::to_string(owner) + " Units----------------------");
	Logger::log("---------------------------------------------------------");
	for (auto &x : game.getHolder<Unit>())
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
void ConsoleUI::logStateOrders(const Game & game)const
{
	auto owner = game.getActivePlayer();
	Logger::log("---------------------------------------------------------");
	Logger::log("--------------------Player " + std::to_string(owner) + " Orders----------------------");
	Logger::log("---------------------------------------------------------");
	for (auto &x : game.getHolder<Order>())
	{
		if (x->getOwner() == owner)
		{
			Logger::log(std::to_string(x->getID()) + ": " + x->getPrototype()->getName());
			Logger::log("---------------------------------------------------------");
		}
	}
}


void  ConsoleUI::makeMove(const Game & game)
{
	Logger::log("---------------------------------------------------------");
	Logger::log("----------------------Make a move------------------------");
	Logger::log("---------------------------------------------------------");


	Logger::logW("ID:" + std::to_string(game.getActiveUnit()->getID()) + " Name: ");
	game.getActiveUnit()->getSimpleInfo();
	for (auto &x : game.getPossibleOrders())
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
void ConsoleUI::logSimpleMap(const Game & game)const
{
	auto map = logStartMap();


	for (auto &unit : game.getHolder<Unit>())
	{
		if (unit->getOwner() == 0)
			map[unit->getPosition().x][unit->getPosition().y] = 'F';
		else
			map[unit->getPosition().x][unit->getPosition().y] = 'S';
	}
	map[game.getActiveUnit()->getPosition().x][game.getActiveUnit()->getPosition().y] = 'A';

	logConstructMap(map);

}

void ConsoleUI::logMoveMap(const Game & game, Order *order, int i)const
{
	auto map = logStartMap();

	for (auto x : order->getProperTargets(game.getActiveUnit(), i))
	{
		map[x.pos.x][x.pos.y] = 'M';
	}

	for (auto &unit : game.getHolder<Unit>())
	{
		if (unit->getOwner() == 0)
			map[unit->getPosition().x][unit->getPosition().y] = 'F';
		else
			map[unit->getPosition().x][unit->getPosition().y] = 'S';
	}
	map[game.getActiveUnit()->getPosition().x][game.getActiveUnit()->getPosition().y] = 'A';

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
