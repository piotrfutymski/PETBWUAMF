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
	void init(Game * g);

	void logState(int owner)const;
	void logStateUnits(int owner)const;
	void logStateOrders(int owner)const;

	void  makeMove();

	void logSimpleMap() const;

	void logMoveMap(Order *order, int i) const;
	/*
	static void setParent(Game * g)
	{
		_game = g;
	};*/
private:

	 Game * _game;

	void logConstructMap(std::vector<std::vector<char>> map) const;
	std::vector<std::vector<char>> logStartMap() const;



};
//Game* _game = nullptr;
