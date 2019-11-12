#include "Game.h"

Game::Game()
{
}

void Game::init(const GameInitiator & i)
{
	Logger::log("---------------------------------------------------------");
	Logger::log("---------------Game initialization started---------------");
	Logger::log("---------------------------------------------------------");

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
		int am = a->getMorale();
		int bm = b->getMorale();
			return am > bm;
	});
	_activeUnit = *_unitsInMoraleOrder.begin();
	_activePlayer = _activeUnit->getOwner();

	Logger::log("---------------------------------------------------------");
	Logger::log("--------------Game initialization completed--------------");
	Logger::log("---------------------------------------------------------");
}

bool Game::playMove(const Move & m)
{

	auto o = this->getObject<Order>(m.orderID);

	o->execute(_activeUnit, m);
	_unitsInMoraleOrder.erase(_unitsInMoraleOrder.begin());
	if (_unitsInMoraleOrder.size() == 0)
	{
		for (auto &u : _units)
		{
			_unitsInMoraleOrder.push_back(u.get());
		}
	}
	std::sort(_unitsInMoraleOrder.begin(), _unitsInMoraleOrder.end(), [](Unit * a, Unit * b) {
		int am = a->getMorale();
		int bm = b->getMorale();
			return am > bm;
	});
	_activeUnit = *_unitsInMoraleOrder.begin();
	_activePlayer = _activeUnit->getOwner();

	return true;
}

bool Game::isEnded() const
{
	return _isEnded;
}


std::vector<Order*> Game::getPossibleOrders()
{
	auto res =  std::vector<Order*>();

	for (auto & o : _orders)
	{
		if (o->getOwner() == _activePlayer && o->canBeUsed(_activeUnit))
			res.push_back(o.get());
	}
	return res;
}

const std::vector<Order*> Game::getPossibleOrders() const
{
	auto res = std::vector<Order*>();

	for (auto & o : _orders)
	{
		if (o->getOwner() == _activePlayer && o->canBeUsed(_activeUnit))
			res.push_back(o.get());
	}
	return res;
}

std::vector<Unit*> Game::getNeightbours(Unit * u)
{
	auto res = std::vector<Unit*>();
	auto pos = u->getPosition();

	for(auto &x: _units)
	{
		auto tpos = x->getPosition();
		if ((tpos.x >= pos.x - 1 && tpos.x <= pos.x + 1) && (tpos.y >= pos.y - 1 && tpos.y <= pos.y + 1) && tpos != pos)
			res.push_back(x.get());
	}

	return res;

}


const Unit * Game::getActiveUnit() const
{
	return _activeUnit;
}

Unit * Game::getActiveUnit()
{
	return _activeUnit;
}

size_t Game::getActivePlayer()const
{
	return _activePlayer;
}

