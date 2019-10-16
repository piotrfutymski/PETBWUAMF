#pragma once
#include "Widgets/Widgets.h"
#include "GameObjects/Unit.h"
#include "GameObjects/Order.h"

namespace Didax
{

	class Board;
	class AssetMeneger;
	class Unit;
	class Order;

class Player
{
public:
	friend class Engine;


	using UnitsHolder_t = std::vector<Unit *>;
	using OrdersHolder_t = std::vector<Order *>;

	Player();
	~Player();

	void init(Board * b, AssetMeneger * a);

	void setUnitsAndOrdersAsAllay(Canvas * root);
	void setUnitsAsEnemy(Canvas * root);
	void setOrdersAsChoosable();

	void addUnit(Unit * u);
	void addOrder(Order * o);

private:

	Board * _board;
	AssetMeneger * _assets;

	UnitsHolder_t _playerUnits;
	OrdersHolder_t _playerOrders;

private:

	void setUnitsOnSide(int s, Canvas * root);


};



}