#pragma once
#include <memory>
#include <vector>
#include <algorithm> 
#include <functional>
#include "GameInitiatior.h"
#include "Move.h"
#include "Map.h"
#include "Order.h"
#include "Unit.h"


class Game
{
public:

	using OrderHolder_t = std::vector<std::unique_ptr<Order>>;
	using UnitHolder_t = std::vector<std::unique_ptr<Unit>>;

	Game();

	Game(const Game &) = delete;

	Game(Game &&) = delete;

	Game operator=(const Game &) = delete;

	void init(const GameInitiator & i);

	void playMove(const Move & m);

	void logState()const;

	Order * getOrder(const std::function<bool(Order* o)> & condition);

	std::vector<Order *> getOrders(const std::function<bool(Order* o)> & condition);

	Unit * getUnit(const std::function<bool(Unit* o)> & condition);

	std::vector<Unit *> getUnits(const std::function<bool(Unit* o)> & condition);

private:

	OrderHolder_t _orders;			// all orders in game
	UnitHolder_t _units;			// all units in game

	Map _map;						// map



};
