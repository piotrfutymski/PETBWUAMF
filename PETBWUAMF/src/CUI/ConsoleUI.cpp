#include "ConsoleUI.h"



ConsoleUI::ConsoleUI()
{
	_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cords;
	cords.X = 180;
	cords.Y = 200;
	_SMALL_RECT rect;
	rect.Left = 0;
	rect.Top = 0;
	rect.Right = 179;
	rect.Bottom = 100;

	if (!SetConsoleScreenBufferSize(_hConsole, cords))
	{
		GetLastError();
	}

	if (!SetConsoleWindowInfo(_hConsole, true, &rect))
	{
		GetLastError();
	}
}

void ConsoleUI::logState(const Game & game, Reporter & reporter)
{
	this->ChangeColumn(0);

	this->logStateUnits(game, game.getActivePlayer());
	this->logStateUnits(game, (game.getActivePlayer()+1)%2);
	this->logStateOrders(game);
	this->SimpleMap(game);
	this->logStateTurn(game, reporter);
	this->WriteLine("------------------------New Turn-------------------------");
	this->WriteLine("---------------------------------------------------------");
	this->WriteLine("---------------------------------------------------------");
	this->WriteLine("---------------------------------------------------------");
	this->WriteLine(game.getObject<Unit>(game.getActiveUnitID())->getPrototype()->getName() + "'s Turn.");
}

void ConsoleUI::logStateUnits(const Game & game, int owner)
{
	int old = this->_column;
	ChangeColumn(1);
	WriteLine("---------------------------------------------------------");
	WriteLine("---------------------Player " + std::to_string(owner) + " Units----------------------");
	WriteLine("---------------------------------------------------------");
	for (auto &x : game.getHolder<Unit>())
	{
		if (x->getOwner() == owner)
		{
			//Write("ID:" + std::to_string(x->getID()) + " Name: ");
			//x->getSimpleInfo();
			WriteLine(std::to_string(x->getID()) + ": " + x->getPrototype()->getName() + " on pos (" + std::to_string(x->getPosition().x) + "," + std::to_string(x->getPosition().y) + ")");
			WriteLine("Attack: " + std::to_string(x->getAttack()) + " Defence: " + std::to_string(x->getDefence()) + " Health: " + std::to_string(x->getHealth()));
			WriteLine("---------------------------------------------------------");
		}
	}
	ChangeColumn(old);
}
void ConsoleUI::logStateOrders(const Game & game)
{
	int old = this->_column;
	ChangeColumn(1);
	auto owner = game.getActivePlayer();
	WriteLine("---------------------------------------------------------");
	WriteLine("--------------------Player " + std::to_string(owner) + " Orders----------------------");
	WriteLine("---------------------------------------------------------");
	for (auto &x : game.getHolder<Order>())
	{
		if (x->getOwner() == owner)
		{
			WriteLine(std::to_string(x->getID()) + ": " + x->getPrototype()->getName());
			WriteLine("---------------------------------------------------------");
		}
	}
	ChangeColumn(old);
}
void ConsoleUI::logStateTurn(const Game & game, Reporter & reporter)
{
	auto info = reporter.getLastTurn();
	WriteLine("---------------------------------------------------------");
	/*for (auto moves : info._unitsMoved)
	{
		WriteLine(game.getObject<Unit>(moves.first)->getPrototype()->getName() 
			+ " moved to " + std::to_string(moves.second.x) + ":" + std::to_string(moves.second.y));
	}
	WriteLine("---------------------------------------------------------");
	for (auto moves : info._demageDealt)
	{
		WriteLine(game.getObject<Unit>(std::get<0>(moves))->getPrototype()->getName()
			+ " has dealt " + std::to_string(-1 * std::get<2>(moves)) + " casualties to " + game.getObject<Unit>(std::get<1>(moves))->getPrototype()->getName());
	}
	WriteLine("---------------------------------------------------------");
	for (auto moves : info._buffs)
	{
		WriteLine(game.getObject<Unit>(std::get<0>(moves))->getPrototype()->getName()
			+ "'s "+ "something increased by " + std::to_string(std::get<2>(moves)));
	}
	WriteLine("---------------------------------------------------------");
	for (auto moves : info._deBuffs)
	{
		WriteLine(game.getObject<Unit>(std::get<0>(moves))->getPrototype()->getName()
			+ "'s " + "something decreased by " + std::to_string(std::get<2>(moves)));
	}*/
	WriteLine("---------------------------------------------------------");
}

void  ConsoleUI::makeMove(const Game & game)
{
	int old = this->_column;
	ChangeColumn(0);
	WriteLine("---------------------------------------------------------");
	WriteLine("----------------------Make a move------------------------");
	WriteLine("---------------------------------------------------------");
	const Unit * x = game.getObject<Unit>(game.getActiveUnitID());
	Write("ID:" + std::to_string(x->getID()) + " Name: ");
	WriteLine(std::to_string(x->getID()) + ": " + x->getPrototype()->getName() + " on pos (" + std::to_string(x->getPosition().x) + "," + std::to_string(x->getPosition().y) + ")");
	WriteLine("Attack: " + std::to_string(x->getAttack()) + " Protection: " + std::to_string(x->getDefence()) + " Health: " + std::to_string(x->getHealth()));
	WriteLine("---------------------------------------------------------");
	for (auto &o : game.getPossibleOrders(game.getActivePlayer()))
	{
		auto x = game.getObject<Order>(o);
		Write(std::to_string(x->getID()) + ": " + x->getPrototype()->getName() + " ");
	}
	WriteLine("");
	WriteLine("---------------------------------------------------------");
	ChangeColumn(old);
}



void ConsoleUI::ClearMap()
{
	int sizeX = Map::MAP_WIDTH;
	int sizeY = Map::MAP_HEIGHT;
	//char map[16][10];
	_map.clear();
	_colormap.clear();
	for (int x = 0; x < sizeX; x++)
	{
		_map.push_back(std::vector<char>());
		_colormap.push_back(std::vector<char>());
		for (int y = 0; y < sizeY; y++)
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

void ConsoleUI::MoveMap(const Game & game, Order *order)
{
	this->ClearMap();

	this->SimUnitsMap(game);
	
	this->SimMovMap(game, order);

	this->ConUnitMap(game);

	this->ConstructMap();
}

void ConsoleUI::AttackMap(const Game & game, Order *order)
{
	this->ClearMap();

	this->SimUnitsMap(game);

	this->NumUnitsMap(game, order);

	this->ConUnitMap(game);

	this->ConstructMap();
}

void ConsoleUI::ChargeMap(const Game & game, Order *order, Move & res)
{
	this->ClearMap();

	this->SimUnitsMap(game);

	this->ConUnitMap(game);
	
	this->_colormap[res.positions[0].x][res.positions[0].y] = 'M';

	this->CharUnitsMap(game, order, res);

	this->ConstructMap();

}

void ConsoleUI::ConstructMap()
{
	int old = this->_column;
	ChangeColumn(2);
	CursorByUp();
	int sizeX = Map::MAP_WIDTH;
	int sizeY = Map::MAP_HEIGHT;
	Write("    |");
	for (int y = 0; y < sizeY; y++)
	{
		//Logger::logW(std::to_string(y));
		if (y < 10)
			Write(std::to_string(y));
		else
			Write(y - 10 + 'A');
		Write("|");
	}
	WriteLine("");

	Write("  |");
	for (int y = 0; y < sizeY+2; y++)
	{
		Write("X|");
	}
	WriteLine("");
	//Logger::log("   XXXXXXXXXXXX");
	for (int x = 0; x < sizeX; x++)
	{
		if (x < 10)
			Write(std::to_string(x) + " ");
		else
			Write(std::to_string(x));
		Write("|X|");
		for (int y = 0; y < sizeY; y++)
		{
			if (_colormap[x][y] == 'Y')
				std::cout << yellow;

			else if (_colormap[x][y] == 'B')
				std::cout << blue;

			else if (_colormap[x][y] == 'R')
				std::cout << red;
			else if (_colormap[x][y] == 'M')
				std::cout << magenta;
			else if (_colormap[x][y] == 'G')
				std::cout << green;
			Write(_map[x][y]);
			std::cout << white;
			Write("|");
		}
		Write("X|");
		WriteLine("");
	}
	//Logger::log("|X|X|X|X|X|X|X|X|X|X|X|X|");
	Write("  |");
	for (int y = 0; y < sizeY + 2; y++)
	{
		Write("X|");
	}
	ChangeColumn(old);
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
void ConsoleUI::NumUnitsMap(const Game & game, Order *order)
{
	for (auto x : game.getPossibleTargets(order->getID()))
	{
		this->_colormap[x.position.x][x.position.y] = 'G';
		//this->_colormap[unit->getPosition().x][unit->getPosition().y] = 'R';

		int targetID = (int)game.getUnitOnPosition(x.position);
		if (targetID <= 9)
			this->_map[x.position.x][x.position.y] = targetID + '0';
		else
			this->_map[x.position.x][x.position.y] = targetID - 10 + 'a';
	}
}
void ConsoleUI::CharUnitsMap(const Game & game, Order *order,Move & res)
{
	for (auto x : game.getPossibleTargets(order->getID()))
	{
		this->_colormap[x.position.x][x.position.y] = 'G';
		//this->_colormap[unit->getPosition().x][unit->getPosition().y] = 'R';
		int targetID = (int)game.getUnitOnPosition(x.position);
		if (targetID <= 9)
			this->_map[x.position.x][x.position.y] = targetID + '0';
		else
			this->_map[x.position.x][x.position.y] = targetID - 10 + 'a';
	}
}
void ConsoleUI::ConUnitMap(const Game & game)
{
	auto unit = game.getObject<Unit>(game.getActiveUnitID());
	this->_colormap[unit->getPosition().x][unit->getPosition().y] = 'Y';
}

void ConsoleUI::SimMovMap(const Game & game, Order *order)
{
	for (auto x : game.getPossibleTargets(order->getID()))
	{
		//this->_map[x.pos.x][x.pos.y] = 'M';
		this->_colormap[x.position.x][x.position.y] = 'G';
	}
}
char ConsoleUI::TypeUnitMap(const Game & game, const std::string type)
{

	if (type == "Infantry")
		return 'I';
	 if (type == "Archer")
		return 'A';
	if (type == "EliteInfantry" || type== "Guard")
		return 'G';
	if (type == "Spearman")
		return 'W';
	if (type == "Axeman")
		return 'E';
	if (type == "Crossbowman")
		return 'C';
	if (type == "Javelinman")
		return 'J';
	else
		return '?';
}
ConsoleUI::~ConsoleUI()
{
}




COORD ConsoleUI::GetCursorPos()
{
	COORD cords;
	CONSOLE_SCREEN_BUFFER_INFO buffer_info;
	GetConsoleScreenBufferInfo(_hConsole, &buffer_info);
	cords = buffer_info.dwCursorPosition;
	return cords;
}

void ConsoleUI::SetCursorPos(COORD cords)
{
	SetConsoleCursorPosition(_hConsole, cords);
}
void ConsoleUI::ChangeColumn(int column)
{
	COORD cords;
	cords = GetCursorPos();

	colEnd[this->_column] = cords.Y;


	_column = column;


	cords.Y = colEnd[this->_column];
	cords.X = column * 60;
	SetConsoleCursorPosition(_hConsole, cords);
}
void ConsoleUI::endl()
{
	COORD cords = GetCursorPos();
	//std::cout << std::endl;
	cords.Y++;
	cords.X = _column * 60;
	SetConsoleCursorPosition(_hConsole, cords);
}
void ConsoleUI::CursorByUp()
{
	COORD cords = GetCursorPos();
	cords.Y = 0;
	SetConsoleCursorPosition(_hConsole, cords);
}

void ConsoleUI::Write(const char & msg)
{
	Logger::logW(msg);
}
void ConsoleUI::Write(const std::string & msg)
{
	Logger::logW(msg);
}
void ConsoleUI::WriteLine(const std::string & msg)
{
	Logger::logW(msg);
	endl();
}
void ConsoleUI::WriteLine(const char & msg)
{
	Logger::logW(msg);
	endl();
}
void ConsoleUI::clear()
{
	COORD coordScreen = { 0, 0 };    // home for the cursor 
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;

	// Get the number of character cells in the current buffer. 

	if (!GetConsoleScreenBufferInfo(_hConsole, &csbi))
	{
		return;
	}

	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	// Fill the entire screen with blanks.

	if (!FillConsoleOutputCharacter(_hConsole,        // Handle to console screen buffer 
		(TCHAR) ' ',     // Character to write to the buffer
		dwConSize,       // Number of cells to write 
		coordScreen,     // Coordinates of first cell 
		&cCharsWritten))// Receive number of characters written
	{
		return;
	}

	// Get the current text attribute.

	if (!GetConsoleScreenBufferInfo(_hConsole, &csbi))
	{
		return;
	}

	// Set the buffer's attributes accordingly.

	if (!FillConsoleOutputAttribute(_hConsole,         // Handle to console screen buffer 
		csbi.wAttributes, // Character attributes to use
		dwConSize,        // Number of cells to set attribute 
		coordScreen,      // Coordinates of first cell 
		&cCharsWritten)) // Receive number of characters written
	{
		return;
	}

	// Put the cursor at its home coordinates and resets all columns.

	colEnd[0] = 0;
	colEnd[1] = 0;
	colEnd[2] = 0;

	SetConsoleCursorPosition(_hConsole, coordScreen);
}
