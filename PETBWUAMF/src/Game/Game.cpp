#include "Game.h"

Game::Game()
{
}

void Game::init(const GameInitiator & i)
{
	Logger::log("Game initialization");

	Unit::setParent(this);
	Order::setParent(this);
	Buff::setParent(this);

	this->initPrototypes();


	for (auto &u : i._units)
	{
		auto unit = this->createObject<Unit>(u.first);
		unit->setPosition(u.second);
		_unitsInMoraleOrder.push_back(unit);
		if (u.second.x < 2)
			unit->setOwner(0);
		else
			unit->setOwner(1);
	}

	for (auto &o : i._fPlayerOrders)
	{
		auto order = this->createObject<Order>(o);
		order->setOwner(0);
	}
	for (auto &o : i._sPlayerOrders)
	{
		auto order = this->createObject<Order>(o);
		order->setOwner(1);
	}
	std::sort(_unitsInMoraleOrder.begin(), _unitsInMoraleOrder.end(), [](Unit * a, Unit * b) {
		return a->getMorale() > b->getMorale();
	});
	_activeUnit = *_unitsInMoraleOrder.begin();

}



bool Game::playMove(const Move & m)
{

	auto o = this->getObject<Order>(m.orderID);

	o->execute(_activeUnit, m);
	_unitsInMoraleOrder.erase(_unitsInMoraleOrder.begin());

	std::sort(_unitsInMoraleOrder.begin(), _unitsInMoraleOrder.end(), [](Unit * a, Unit * b) {
		return a->getMorale() > b->getMorale();
	});
	_activeUnit = *_unitsInMoraleOrder.begin();

	return true;
}

void Game::logState()const
{
	Logger::log("On board, there are thease units:");
	Logger::log("Player One Units:");
	for (auto &x : _units)
	{
		if (x->getOwner() == 0)
		{
			Logger::log(std::to_string(x->getID()) + ": " + x->getPrototype()->getName() + " on pos (" + std::to_string(x->getPosition().x) + "," + std::to_string(x->getPosition().y)+")");
		}
	}
	Logger::log("Player Two Units:");
	for (auto &x : _units)
	{
		if (x->getOwner() == 1)
		{
			Logger::log(std::to_string(x->getID()) + ": " + x->getPrototype()->getName() + " on pos (" + std::to_string(x->getPosition().x) + "," + std::to_string(x->getPosition().y) + ")");
		}
	}

	Logger::log("Player One Orders:");
	for (auto &x : _orders)
	{
		if (x->getOwner() == 0)
		{
			Logger::log(std::to_string(x->getID()) + ": " + x->getPrototype()->getName());
		}
	}

	Logger::log("Player Two Orders:");
	for (auto &x : _orders)
	{
		if (x->getOwner() == 1)
		{
			Logger::log(std::to_string(x->getID()) + ": " + x->getPrototype()->getName());
		}
	}

	Logger::log("U R playing unit with id: " + std::to_string(_activeUnit->getID()));
}

bool Game::isEnded() const
{
	return _isEnded;
}

void Game::logPossibleMoves()
{
	Logger::log("TODO\n");
}

Move Game::getMoveFromConsole()
{
	Move res;
	res.unitID = _activeUnit->getID();

	Logger::log("If you want to see possible moves - y, or just do move");
	auto a = std::getchar();
	if (a == 'y')
		logPossibleMoves();

	Order * order = nullptr;
	int oID;
	while(1)
	{
		Logger::log("Pick order id");
		std::cin >> oID;
		order = this->getObject<Order>(oID);
		if (order == nullptr)
		{
			Logger::log("Order doesn't exist");
			continue;
		}
		if (order->canBeUsed(_activeUnit))
		{
			Logger::log("Choosed order: " + oID);
			Logger::log("\n");
			break;
		}
		Logger::log("Order can't be used");
	}
	res.orderID = oID;
	
	for (size_t i = 0; i < order->getTargetsCount(); i++)
	{
		if (order->getTargetType(i) == OrderPrototype::Target::Position_target)
		{
			Logger::log("Choose Position (int) (int)");
			int x, y;
			std::cin >> x;
			std::cin>> y;
			res.positions.push_back({ x,y });
		}
		else
		{
			Logger::log("Choose Target ID (int)");
			int id;
			std::cin >> id;
			res.units.push_back(id);
		}
	}

	return res;

	
}
