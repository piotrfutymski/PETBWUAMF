#pragma once
#include "../Game/Game.h"
#include "ConsoleColor.h"
#include "../Utility/Reporter.h"

class ConsoleUI
{
public:
	ConsoleUI();
	virtual ~ConsoleUI();

	void logState(const Game & game, Reporter & reporter);		/* Prints state of the game*/
	void logStateUnits(const Game & game, int owner);			/* Prints state of all units in the game*/
	void logStateOrders(const Game & game);						/* Prints state of active player's all orders*/
	void logStateTurn(const Game & game, Reporter & reporter);	/* Prints actions which happened in previous turn*/
	void  makeMove(const Game & game);							/* Prints possible actions by player*/
	void  logActiveUnit(const Game & game);						/* Prints state of active unit*/


	void SimpleMap(const Game & game);							/* Creates map including only units*/

	void AttackMap(const Game & game, Order *order);			/* Creates map including possible targets and units */

	void MoveMap(const Game & game, Order *order);				/* Creates map including possible move targets and units */

	void ChargeMap(const Game & game, Order *order, Move & res);/* Creates map including possible charge targets and units */
	void clear();												/* Clears out the UI */
private:

	int colEnd[3];
	int _column;
	std::vector<std::vector<char>> _map;
	std::vector<std::vector<char>> _colormap;
	COORD _lastcoords;
	HANDLE _hConsole;
	char TypeUnitMap(const Game & game, const std::string type);/* Returns unit ID char */
	void SimUnitsMap(const Game & game);						/* Adds units by type to map */
	void NumUnitsMap(const Game & game, Order *order);			/* Adds attack targets to map */
	void CharUnitsMap(const Game & game, Order *order, Move & res);/* Adds charge targets to map */
	void ConUnitMap(const Game & game);							/* Adds controlled unit to map */
	void SimMovMap(const Game & game, Order *order);			/* Adds move targets to map */
	void ConstructMap();										/* Prints map to third column */
	void ClearMap();											/* Clears out the map*/

	COORD GetCursorPos();										/* Returns cursor position */
	void SetCursorPos(COORD cords);								/* Sets cursor position */
	void ChangeColumn(int column = 0);							/* Change currently used column */
	void CursorByUp();											/* Returns cursor position to top */


	void Write(const std::string & msg);						
	void Write(const char & msg);
	void WriteLine(const std::string & msg);
	void WriteLine(const char & msg);
	void endl();

};
//Game* _game = nullptr;
