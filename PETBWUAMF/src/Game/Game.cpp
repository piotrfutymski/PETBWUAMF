#include "Game.h"

Game::Game()
{
}

void Game::init(const GameInitiator & i)
{
}

void Game::playMove(const Move & m)
{
}

void Game::logState()const
{
}

Order * Game::getOrder(const std::function<bool(Order* o)> & condition)
{
	for (auto & o : _orders)
	{
		auto o_ptr = o.get();
		if (condition(o_ptr))
			return o_ptr;
	}

	return nullptr;
}

std::vector<Order*> Game::getOrders(const std::function<bool(Order*o)>& condition)
{
	auto res = std::vector<Order*>();
	
	for (auto & o : _orders)
	{
		auto o_ptr = o.get();
		if (condition(o_ptr))
			res.push_back(o_ptr);
	}
	return res;
}

Unit * Game::getUnit(const std::function<bool(Unit*o)>& condition)
{
	for (auto &u : _units)
	{
		auto u_ptr = u.get();
		if (condition(u_ptr))
			return u_ptr;
	}

	return nullptr;
}

std::vector<Unit*> Game::getUnits(const std::function<bool(Unit*o)>& condition)
{
	auto res = std::vector<Unit*>();

	for (auto & u : _units)
	{
		auto u_ptr = u.get();
		if (condition(u_ptr))
			res.push_back(u_ptr);
	}
	return res;
}
