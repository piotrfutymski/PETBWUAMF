#include "ConsoleUI.h"



ConsoleUI::ConsoleUI()
{
}

void ConsoleUI::logState(const Game & game)
{
	Logger::log("---------------------------------------------------------");
	Logger::log("------------------------New Turn-------------------------");
	Logger::log("---------------------------------------------------------");
	this->logStateUnits(game, game.getActivePlayer());
	this->logStateUnits(game, (game.getActivePlayer()+1)%2);
	this->logStateOrders(game);
	this->SimpleMap(game);
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



void ConsoleUI::ClearMap()
{
	int sizeX = Unit::MAXPOS.x;
	int sizeY = Unit::MAXPOS.y;
	//char map[16][10];
	_map.clear();
	_colormap.clear();
	for (int x = 0; x <= sizeX; x++)
	{
		_map.push_back(std::vector<char>());
		_colormap.push_back(std::vector<char>());
		for (int y = 0; y <= sizeY; y++)
		{
			_map[x].push_back('O');
			_colormap[x].push_back('W');
		}
	}
}
void ConsoleUI::SimpleMap(const Game & game)
{
	this->ClearMap();

	this->SimUnitsMap(game);

	this->ConUnitMap(game);

	this->ConstructMap();

}

void ConsoleUI::MoveMap(const Game & game, Order *order, int i)
{
	this->ClearMap();

	this->SimUnitsMap(game);
	
	this->SimMovMap(game, order);

	this->ConUnitMap(game);

	this->ConstructMap();
}

void ConsoleUI::AttackMap(const Game & game)
{
	this->ClearMap();

	this->NumUnitsMap(game);

	this->ConUnitMap(game);

	this->ConstructMap();
}

void ConsoleUI::ConstructMap()
{
	COORD savedcoords = GetCursorPos();
	if (savedcoords.Y - _lastcoords.Y < Unit::MAXPOS.x + 4)
		SetCursorPos(_lastcoords);
	CursorByUp();
	CursorToRight();
	int sizeX = Unit::MAXPOS.x;
	int sizeY = Unit::MAXPOS.y;
	Logger::logW("    |");
	for (int y = 0; y <= sizeY; y++)
	{
		//Logger::logW(std::to_string(y));
		if (y < 10)
			Logger::logW(std::to_string(y));
		else
			Logger::logW(y - 10 + 'A');
		Logger::logW("|");
	}
	CursorToRight();

	Logger::logW("  |");
	for (int y = 0; y <= sizeY+2; y++)
	{
		Logger::logW("X|");
	}
	CursorToRight();
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
			if (_colormap[x][y] == 'Y')
				std::cout << yellow;

			else if (_colormap[x][y] == 'B')
				std::cout << blue;

			else if (_colormap[x][y] == 'R')
				std::cout << red;

			else if (_colormap[x][y] == 'G')
				std::cout << green;
			Logger::logW(_map[x][y]);
			std::cout << white;
			Logger::logW("|");
		}
		Logger::logW("X|");
		CursorToRight();
	}
	//Logger::log("|X|X|X|X|X|X|X|X|X|X|X|X|");
	Logger::logW("  |");
	for (int y = 0; y <= sizeY + 2; y++)
	{
		Logger::logW("X|");
	}
	SetCursorPos(savedcoords);
	_lastcoords = savedcoords;
}

void ConsoleUI::SimUnitsMap(const Game & game)
{
	for (auto &unit : game.getHolder<Unit>())
	{
		if (unit->getOwner() == game.getActivePlayer())
			this->_colormap[unit->getPosition().x][unit->getPosition().y] = 'B';
		else
			this->_colormap[unit->getPosition().x][unit->getPosition().y] = 'R';

		this->_map[unit->getPosition().x][unit->getPosition().y] =
			TypeUnitMap(game, unit->getPrototype()->_unitType);

	}
}
void ConsoleUI::NumUnitsMap(const Game & game)
{
	for (auto &unit : game.getHolder<Unit>())
	{
		if (unit->getOwner() == game.getActivePlayer())
		{
			this->_map[unit->getPosition().x][unit->getPosition().y] = 
				TypeUnitMap(game, unit->getPrototype()->_unitType);
			this->_colormap[unit->getPosition().x][unit->getPosition().y] = 'B';
		}

		else
		{
			this->_colormap[unit->getPosition().x][unit->getPosition().y] = 'R';
			if (unit->getID() <= 9)
				this->_map[unit->getPosition().x][unit->getPosition().y] = unit->getID() + '0';
			else
				this->_map[unit->getPosition().x][unit->getPosition().y] = unit->getID() - 10 + 'a';
		}

	}
}
void ConsoleUI::ConUnitMap(const Game & game)
{
	this->_colormap[game.getActiveUnit()->getPosition().x][game.getActiveUnit()->getPosition().y] = 'Y';
}

void ConsoleUI::SimMovMap(const Game & game, Order *order)
{
	for (auto x : order->getProperTargets(game.getActiveUnit(), 0))
	{
		//this->_map[x.pos.x][x.pos.y] = 'M';
		this->_colormap[x.pos.x][x.pos.y] = 'G';
	}
}
char ConsoleUI::TypeUnitMap(const Game & game, const std::string type)
{

	if (type == "Infantry")
		return 'I';
	else if (type == "Ranged")
		return 'R';
	else if (type == "EliteInfantry")
		return 'G';
	else
		return '?';
}
ConsoleUI::~ConsoleUI()
{
}

COORD ConsoleUI::GetCursorPos()
{
	COORD cords;
	CONSOLE_SCREEN_BUFFER_INFO buffer_info = CONSOLE_SCREEN_BUFFER_INFO();
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &buffer_info);
	cords = buffer_info.dwCursorPosition;
	return cords;
}

void ConsoleUI::SetCursorPos(COORD cords)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cords);
}
void ConsoleUI::CursorToRight()
{
	COORD cords;
	cords = GetCursorPos();
	cords.Y++;
	cords.X = 60;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cords);
}
void ConsoleUI::CursorByUp()
{
	COORD cords;
	cords = GetCursorPos();
	cords.Y -= Unit::MAXPOS.x;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cords);
}