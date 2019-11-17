#pragma once
#include "../Game/Game.h"
#include "ConsoleColor.h"
#include "../Utility/Reporter.h"

class ConsoleUI
{
public:
	ConsoleUI();
	virtual ~ConsoleUI();

	void logState(const Game & game, Reporter & reporter);
	void logStateUnits(const Game & game, int owner);
	void logStateOrders(const Game & game);
	void logStateTurn(const Game & game, Reporter & reporter);
	void  makeMove(const Game & game);
	void  logActiveUnit(const Game & game);


	void SimpleMap(const Game & game);

	void AttackMap(const Game & game, Order *order);

	void MoveMap(const Game & game, Order *order);

	void ChargeMap(const Game & game, Order *order, Move & res);
	/*
	static void setParent(Game * g)
	{
		_game = g;
	};*/
	void clear();
private:

	int colEnd[3];
	int _column;
	std::vector<std::vector<char>> _map;
	std::vector<std::vector<char>> _colormap;
	COORD _lastcoords;
	HANDLE _hConsole;
	char TypeUnitMap(const Game & game, const std::string type);
	void SimUnitsMap(const Game & game);
	void NumUnitsMap(const Game & game, Order *order);
	void CharUnitsMap(const Game & game, Order *order, Move & res);
	void ConUnitMap(const Game & game);
	void SimMovMap(const Game & game, Order *order);
	void ConstructMap();
	void ClearMap();

	COORD GetCursorPos();
	void SetCursorPos(COORD cords);
	void ChangeColumn(int column = 0);
	void CursorByUp();


	void Write(const std::string & msg);
	void Write(const char & msg);
	void WriteLine(const std::string & msg);
	void WriteLine(const char & msg);
	void endl();

};
//Game* _game = nullptr;
