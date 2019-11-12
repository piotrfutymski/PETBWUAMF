#pragma once
#include <memory>
#include <vector>
#include <algorithm> 
#include <functional>
#include <type_traits>
#include "GameInitiatior.h"
#include "Move.h"
#include "Map.h"
#include "Order.h"
#include "Unit.h"
#include "PathFinder.h"
#include "ConsoleColor.h"
#include "Game.h"

class ConsoleUI
{
public:
	ConsoleUI();
	virtual ~ConsoleUI();

	void logState(const Game & game)const;
	void logStateUnits(const Game & game, int owner)const;
	void logStateOrders(const Game & game)const;

	void  makeMove(const Game & game);

	void logSimpleMap(const Game & game) const;

	void logMoveMap(const Game & game, Order *order, int i) const;
	/*
	static void setParent(Game * g)
	{
		_game = g;
	};*/
private:

	void logConstructMap(std::vector<std::vector<char>> map) const;
	std::vector<std::vector<char>> logStartMap() const;



};
//Game* _game = nullptr;
