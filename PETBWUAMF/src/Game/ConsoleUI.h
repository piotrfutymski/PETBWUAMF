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

	void logState(const Game & game);
	void logStateUnits(const Game & game, int owner)const;
	void logStateOrders(const Game & game)const;

	void  makeMove(const Game & game);

	void SimpleMap(const Game & game);

	void AttackMap(const Game & game);

	void MoveMap(const Game & game, Order *order, int i);
	/*
	static void setParent(Game * g)
	{
		_game = g;
	};*/
private:
	std::vector<std::vector<char>> _map;
	std::vector<std::vector<char>> _colormap;


	char TypeUnitMap(const Game & game, const std::string type);
	void SimUnitsMap(const Game & game);
	void NumUnitsMap(const Game & game);
	void ConUnitMap(const Game & game);
	void SimMovMap(const Game & game, Order *order);
	void ConstructMap() const;
	void ClearMap();



};
//Game* _game = nullptr;
