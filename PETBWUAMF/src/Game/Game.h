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
#include "PathFinder.h"



class Game
{

private:
	template <typename T>
	struct isGameType : public std::conditional_t<
		std::is_same<T, Unit>::value || std::is_same<T, Order>::value,
		std::true_type,
		std::false_type>
	{};

public:

	enum AttackType{
		Normal, Charge, Ocassional
	};

	using OrderHolder_t = std::vector<std::unique_ptr<Order>>;
	using UnitHolder_t = std::vector<std::unique_ptr<Unit>>;

	//constructing

	Game();

	Game(const Game &) = delete;

	Game(Game &&) = delete;

	Game operator=(const Game &) = delete;

	//inits
	void init(const GameInitiator & i);

	//Application Layer functions:
	MoveRes playTurn(const Move & m);
	size_t swapOrder(size_t orderToSwap);

	//Application Layer getters:
	bool isGameEnded()const;
	size_t getActiveUnitID()const;
	int getActivePlayer()const;
	int getCommandPoints(int owner)const;

	std::vector<size_t> getOrdersInHand(int player)const;
	std::vector<size_t> getOrdersInDeck(int player)const;
	std::vector<size_t> getPossibleOrders(int player)const;
	std::vector<size_t> getSwapableOrders(int player)const;
	std::vector<Target> getPossibleTargets(size_t order)const;
	int getTargetCount(size_t)const;

	const Map & getMap()const;

	//Order functions:

	MoveRes moveUnit(size_t unitId, const sf::Vector2i & pos);
	MoveRes fight(size_t aggresor, size_t victim, const AttackType & t);
	MoveRes buff(const std::string & buffName, size_t buffTarget);
	MoveRes createUnit(const std::string & unitName, const sf::Vector2i  &pos);


private:

	OrderHolder_t _orders;			// all orders in game
	UnitHolder_t _units;			// all units in game

	Map _map;						// map

	//game parameters

	bool _isEnded{ false };
	std::vector<Unit *> _unitsInMoraleOrder;
	Unit * _activeUnit;
	int _activePlayer;
	int _player0CommandPoints;
	int _player1CommandPoints;

private:

	void createObjects(const GameInitiator & i);

	void newRound();
	void newTurn();
	MoveRes executeOrder(const Move & m);
	MoveRes endTurn();

	bool canBeUsed(Order * o)const;
	bool canBeSwaped(Order * o)const;

	std::vector<Target> getPossibleMoveTargets()const;
	std::vector<Target> getPossibleAttackTargets()const;
	std::vector<Target> getPossibleChargeTargets()const;
	std::vector<Target> getPossilbeBuffAllayTargets()const;
	std::vector<Target> getPossibleBuffEnemyTargets()const;
	std::vector<Target> getPossibleCreateTargets()const;

	void substractCommandPoints(int player, int count);



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

	template <typename T, typename... Args>
	typename  std::enable_if<Game::isGameType<T>::value, T>::type * createObject(const std::string & prototypeName, Args&&... args)
	{
		auto& holder = getHolder<T>();
		auto a = std::make_unique<T>(prototypeName, std::forward<Args>(args)...);
		holder.push_back(std::move(a));
		return (holder.end() - 1)->get();
	}

	template <typename T>
	void destroyObject(typename std::enable_if<Game::isGameType<T>::value, T>::type * obj)
	{
		auto& holder = getHolder<T>();
		holder.erase(_find<T>(obj->getID()));
	}

	template <typename T>
	typename std::enable_if<Game::isGameType<T>::value, T>::type * getObject(size_t id)
	{
		if (auto it = _find<T>(id); it != getHolder<T>().end())
			return it->get();
		return nullptr;
	}

	template <typename T>
	std::vector<std::unique_ptr< typename std::enable_if<Game::isGameType<T>::value, T>::type>> & getHolder()
	{
		if constexpr (std::is_same<T, Order>::value)
			return _orders;
		else if constexpr (std::is_same<T, Unit>::value)
			return _units;
	}

public:
	//templates

	template <typename T>
	const typename std::enable_if<Game::isGameType<T>::value, T>::type * getObject(size_t id)const
	{
		if (auto it = _find<T>(id); it != getHolder<T>().end())
			return it->get();
		return nullptr;
	}

	

	template <typename T>
	const std::vector<std::unique_ptr< typename std::enable_if<Game::isGameType<T>::value, T>::type>> & getHolder()const
	{
		if constexpr (std::is_same<T, Order>::value)
			return _orders;
		else if constexpr (std::is_same<T, Unit>::value)
			return _units;
	}


};
