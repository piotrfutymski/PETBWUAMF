#include "Game.h"

Game::Game()
{
}

void Game::init(const GameInitiator & i)
{
	Logger::log("---------------------------------------------------------");
	Logger::log("---------------Game initialization started---------------");
	Logger::log("---------------------------------------------------------");

	this->createObjects(i);
	this->newRound();
	this->newTurn();

	Logger::log("---------------------------------------------------------");
	Logger::log("--------------Game initialization completed--------------");
	Logger::log("---------------------------------------------------------");
}

void Game::playMove(const Move & m)
{
	//Jednostka wykonuje rozkaz
	this->executeOrder(m);
	this->endTurn();
	if (_unitsInMoraleOrder.size() == 0)
	{
		this->newRound();
	}
	this->newTurn();

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
	for (auto &x : _map.getNeightbours(u->getID()))
	{
		res.push_back(this->getObject<Unit>(x));
	}
	return res;
}

const std::vector<Unit*> Game::getNeightbours(Unit * u) const
{
	std::vector<Unit*> res{};
	for (auto &x : _map.getNeightbours(u->getID()))
	{
		res.push_back(const_cast<Unit*>(this->getObject<Unit>(x)));
	}
	return res;
}

const Map & Game::getMap() const
{
	return _map;
}

Map & Game::getMap()
{
	return _map;
}

void Game::createObjects(const GameInitiator & i)
{

	for (auto &u : i._units)
	{
		auto unit = this->createObject<Unit>(u.first);
		unit->setPosition(u.second);
		if (u.second.x < 2)
			unit->setOwner(0);
		else
			unit->setOwner(1);

		_map.setUnitPosition(unit->getID(), unit->getOwner(), unit->getPosition());
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
}

void Game::newRound()
{
	for (auto &u : _units)
	{
		_unitsInMoraleOrder.push_back(u.get());
	}

}

void Game::newTurn()
{
	std::sort(_unitsInMoraleOrder.begin(), _unitsInMoraleOrder.end(), [](Unit * a, Unit * b) {
		int am = a->getMorale();
		int bm = b->getMorale();
		return am > bm;
	});
	_activeUnit = *_unitsInMoraleOrder.begin();
	_activePlayer = _activeUnit->getOwner();

}

void Game::executeOrder(const Move & m)
{
	auto o = this->getObject<Order>(m.orderID);
	o->execute(_activeUnit, m);
}

void Game::endTurn()
{
	_unitsInMoraleOrder.erase(_unitsInMoraleOrder.begin());
}


const Unit * Game::getActiveUnit() const
{
	return _activeUnit;
}

Unit * Game::getActiveUnit()
{
	return _activeUnit;
}

int Game::getActivePlayer()const
{
	return _activePlayer;
}

