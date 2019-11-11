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

class Game
{
private:
	template <typename T>
	struct isGameType : public std::conditional_t<
		std::is_same<T, Unit>::value || std::is_same<T, Order>::value || std::is_same<T, Buff>::value,
		std::true_type,
		std::false_type>
	{};

public:

	using OrderHolder_t = std::vector<std::unique_ptr<Order>>;
	using UnitHolder_t = std::vector<std::unique_ptr<Unit>>;
	using BuffHolder_t = std::vector<std::unique_ptr<Buff>>;

	Game();

	Game(const Game &) = delete;

	Game(Game &&) = delete;

	Game operator=(const Game &) = delete;

	void init(const GameInitiator & i);

	void initPrototypes();

	bool playMove(const Move & m);

	void logState(int owner)const;
	void logStateUnits(int owner)const;
	void logStateOrders(int owner)const;
	bool isEnded()const;

	void logPossibleMoves();

	Move getMoveFromConsole();
	void makeMove();
	void logSimpleMap()const;

private:
	//templates
	template <typename T>
	typename std::vector<std::unique_ptr<T>>::const_iterator _find(size_t id)const
	{
		const auto & holder = getHolder<T>();
		return std::find_if(holder.begin(), holder.end(), [=](const auto & arg) {
			return arg->getID() == id;
		});
	}

	template <typename T>
	typename  std::vector<std::unique_ptr<T>>::iterator _find(size_t id)
	{
		auto & holder = getHolder<T>();
		return std::find_if(holder.begin(), holder.end(), [=](const auto & arg) {
			return arg->getID() == id;
		});
	}

public:
	//templates

	template <typename T>
	typename  std::enable_if<Game::isGameType<T>::value, T>::type * createObject(const std::string & prototypeName)
	{
		auto& holder = getHolder<T>();
		auto a = std::make_unique<T>(prototypeName);
		holder.push_back(std::move(a));
		return (holder.end() - 1)->get();
	}

	template <typename T>
	typename std::enable_if<Game::isGameType<T>::value, T>::type * getObject(size_t id)
	{
		if (auto it = _find<T>(id); it != getHolder<T>().end())
			return it->get();
		return nullptr;
	}

	template <typename T>
	const typename std::enable_if<Game::isGameType<T>::value, T>::type * getObject(size_t id)const
	{
		if (auto it = _find<T>(id); it != getHolder<T>().end())
			return it->get();
		return nullptr;
	}

	template <typename T>
	std::vector<std::unique_ptr< typename std::enable_if<Game::isGameType<T>::value, T>::type>> & getHolder() // MÓJ MAJESTAT KU*WA
	{
		if constexpr (std::is_same<T, Order>::value)
			return _orders;
		else if constexpr (std::is_same<T, Unit>::value)
			return _units;
		else if constexpr (std::is_same<T, Buff>::value)
			return _buffs;
	}

	template <typename T>
	const std::vector<std::unique_ptr< typename std::enable_if<Game::isGameType<T>::value, T>::type>> & getHolder()const
	{
		if constexpr (std::is_same<T, Order>::value)
			return _orders;
		else if constexpr (std::is_same<T, Unit>::value)
			return _units;
		else if constexpr (std::is_same<T, Buff>::value)
			return _buffs;
	}


private:

	OrderHolder_t _orders;			// all orders in game
	UnitHolder_t _units;			// all units in game
	BuffHolder_t _buffs;			//all buffs in game

	Map _map;						// map

	//game parameters

	bool _isEnded{ false };

	std::vector<Unit *> _unitsInMoraleOrder;

	Unit * _activeUnit;

	size_t _activePlayer;

	int _player0CommandPoints;
	int _player1CommandPoints;


};
