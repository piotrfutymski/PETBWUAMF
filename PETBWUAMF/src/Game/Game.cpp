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

MoveRes Game::playMove(const Move & m)
{
	//Jednostka wykonuje rozkaz
	auto res = this->executeOrder(m);
	this->endTurn();
	if (_unitsInMoraleOrder.size() == 0)
	{
		this->newRound();
	}
	this->newTurn();
	
	return res;

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
		auto prot = o->getPrototype();
		if (o->getOwner() == _activePlayer && prot->_canBeUsed(_activeUnit))
			res.push_back(o.get());
	}
	return res;
}

const std::vector<Order*> Game::getPossibleOrders() const
{
	auto res = std::vector<Order*>();

	for (auto & o : _orders)
	{
		auto prot = o->getPrototype();
		if (o->getOwner() == _activePlayer && prot->_canBeUsed(_activeUnit))
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

Buff * Game::addBuff(const std::string & s, size_t unit)
{
	auto b = this->createObject<Buff>(s, unit);
	if (b == nullptr)
		return b;
	if (b->getRestTime() == -1)
	{
		this->destroyObject<Buff>(b);
		return nullptr;
	}
	return b;
}

void Game::createObjects(const GameInitiator & i)
{

	for (auto &u : i._units)
	{
		auto unit = this->createObject<Unit>(u.first);
		unit->setPosition(u.second);
		if (u.second.x < 8)
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

MoveRes Game::executeOrder(const Move & m)
{
	auto o = this->getObject<Order>(m.orderID);
	return o->execute(_activeUnit, m);
}

void Game::endTurn()
{
	_unitsInMoraleOrder.erase(_unitsInMoraleOrder.begin());
	auto it = _units.begin();
	while (it != _units.end())
	{
		if ((*it)->isDead())
		{
			auto itt = std::find(_unitsInMoraleOrder.begin(), _unitsInMoraleOrder.end(), it->get());
			if(itt != _unitsInMoraleOrder.end())
				_unitsInMoraleOrder.erase(std::remove(_unitsInMoraleOrder.begin(), _unitsInMoraleOrder.end(), it->get()));
			_map.removeUnitFromPosition((*it)->getPosition());
			it = _units.erase(it);
		}
		else
			it++;
	}
	auto bt = _buffs.begin();
	while (bt != _buffs.end())
	{
		if ((*bt)->getOwner() == _activeUnit->getID())
		{
			if ((*bt)->onTurnEnd())
				bt = _buffs.erase(bt);
			else
				bt++;
		}
		else
			bt++;
	}
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

