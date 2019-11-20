#include "Game.h"

Game::Game()
{
}

void Game::init(const GameInitiator & i)
{

	this->createObjects(i);
	this->newRound();
	this->newTurn();

}

MoveRes Game::playTurn(const Move & m)
{
	auto res = this->executeOrder(m);
	res = res + this->endTurn();
	if (_unitsInMoraleOrder.size() == 0)
	{
		this->newRound();
	}
	this->newTurn();
	
	return res;
}

size_t Game::swapOrder(size_t orderToSwap)
{
	auto toSwap = this->getObject<Order>(orderToSwap);
	if (toSwap == nullptr)
		throw;
	auto inHand = this->getOrdersInHand(_activePlayer);
	auto inDeck = this->getOrdersInDeck(_activePlayer);
	if (std::find_if(inHand.begin(), inHand.end(), [orderToSwap](size_t * num) {
		return orderToSwap == *num; }) == inHand.end())throw;
	
	if (inDeck.empty())
		throw;

	auto n = rand() % inDeck.size();
	auto res = *(inDeck.begin() + n);
	
	if (toSwap->getRestUses() == 0)
		this->destroyObject<Order>(toSwap);
	else
		toSwap->changeLocation();

	this->getObject<Order>(res)->changeLocation();
	return res;
}

bool Game::isGameEnded() const
{
	return _isEnded;
}

size_t Game::getActiveUnitID() const
{
	return _activeUnit->getID();
}

int Game::getActivePlayer()const
{
	return _activePlayer;
}

int Game::getCommandPoints(int owner) const
{
	if (owner == 0)
		return _player0CommandPoints;
	else
		return _player1CommandPoints;
}


std::vector<size_t> Game::getOrdersInHand(int player) const
{
	auto res = std::vector<size_t>{};

	for (auto & x : _orders)
	{
		if (x->getLocation() == Order::Location::InHand && x->getOwner() == player)
			res.push_back(x->getID());
	}
	return res;
}

std::vector<size_t> Game::getOrdersInDeck(int player) const
{
	auto res = std::vector<size_t>{};
	for (auto & x : _orders)
	{
		if (x->getLocation() != Order::Location::InHand && x->getOwner() == player)
			res.push_back(x->getID());
	}
	return res;
}

std::vector<size_t> Game::getPossibleOrders(int player) const
{
	auto res = std::vector<size_t>();

	for (auto & o : _orders)
	{
		auto prot = o->getPrototype();
		if (o->getOwner() == player && this->canBeUsed(o.get()))
			res.push_back(o->getID());
	}
	return res;
}

std::vector<size_t> Game::getSwapableOrders(int player) const
{
	auto res = std::vector<size_t>();
	for (auto & o : _orders)
	{
		auto prot = o->getPrototype();
		if (o->getOwner() == player && this->canBeSwaped(o.get()))
			res.push_back(o->getID());
	}
	return res;

}

std::vector<Target> Game::getPossibleTargets(size_t order) const
{
	switch (this->getObject<Order>(order)->getPrototype()->_target)
	{
	case OrderPrototype::TargetType::AttackT:
		return this->getPossibleAttackTargets();
		break;
	case OrderPrototype::TargetType::BuffAllayT:
		return this->getPossilbeBuffAllayTargets();
		break;
	case OrderPrototype::TargetType::BuffEnemyT:
		return this->getPossibleBuffEnemyTargets();
		break;
	case OrderPrototype::TargetType::BuffT:
		return {};
		break;
	case OrderPrototype::TargetType::ChargeT:
		return this->getPossibleChargeTargets();
		break;
	case OrderPrototype::TargetType::CreateT:
		return this->getPossibleCreateTargets();
		break;
	case OrderPrototype::TargetType::MoveT:
		return this-> getPossibleMoveTargets();
		break;
	default:
		return{};
	}
}

int Game::getTargetCount(size_t o) const
{
	this->getObject<Order>(o)->getPrototype()->_targetCount;
}

const Map & Game::getMap()const
{
	return _map;
}

MoveRes Game::moveUnit(size_t unitId, const sf::Vector2i & pos)
{
	auto res = MoveRes{};
	auto unit = this->getObject<Unit>(unitId);
	_map.moveUnit(unit, pos);
	MoveRes::MoveEvent evnt;
	evnt.position = pos;
	evnt.time = 10;
	evnt.type = MoveRes::EventType::Moved;
	evnt.unit = unitId;
	res.events.push_back(std::move(evnt));

	for (auto & enemy : _map.getEnymeNeightbours(unit))
	{
		if (!enemy->hasFlag(Unit::UFlag::Ranged))
		{
			auto m = this->fight(enemy->getID(), unit->getID(), AttackType::Ocassional);
			m.events[0].time = 2;
			m.events[1].time = 2;
			m.events[2].time = 4;
			res = res + m;
		}
	}
	return res;

}

MoveRes Game::fight(size_t aggresor, size_t victim, const AttackType & t)
{
	auto res = MoveRes{};
	auto aggresUnit = this->getObject<Unit>(aggresor);
	auto victUnit = this->getObject<Unit>(victim);

	MoveRes::MoveEvent evnt;
	evnt.time = 15;
	evnt.type = MoveRes::EventType::Attacking;
	evnt.unit = aggresor;
	res.events.push_back(std::move(evnt));
	evnt.time = 15;
	evnt.type = MoveRes::EventType::BeingAttacked;
	evnt.unit = victim;
	res.events.push_back(std::move(evnt));

	int dmg;

	if (t == AttackType::Charge)
		dmg = aggresUnit->chargeAttack(victUnit);
	else if (t == AttackType::Normal)
		dmg = aggresUnit->attack(victUnit);
	else if (t == AttackType::Ocassional)
		dmg = aggresUnit->ocassionalAttack(victUnit);

	evnt.time = 20;
	evnt.type = MoveRes::EventType::DMGTaken;
	evnt.unit = victim;
	evnt.dmg = dmg;
	res.events.push_back(std::move(evnt));
	return res;

}

MoveRes Game::buff(const std::string & buffName, size_t buffTarget)
{
	auto res = MoveRes{};
	auto target = this->getObject<Unit>(buffTarget);

	auto buff = target->addBuff(buffName);

	MoveRes::MoveEvent evnt;
	evnt.time = 25;
	if(buff->isGood())
		evnt.type = MoveRes::EventType::Buff;
	else
		evnt.type = MoveRes::EventType::Debuff;
	evnt.unit = buffTarget;
	res.events.push_back(std::move(evnt));
	return res;
}

MoveRes Game::createUnit(const std::string & unitName, const sf::Vector2i & pos)
{
	auto res = MoveRes{};
	auto unit = this->createObject<Unit>(unitName, _activePlayer);
	_map.setNewUnit(unit, pos);

	MoveRes::MoveEvent evnt;
	evnt.time = 1;
	evnt.type = MoveRes::EventType::UnitCreated;
	evnt.unit = unit->getID();
	evnt.position = pos;
	res.events.push_back(std::move(evnt));
	return res;
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

		_map.setNewUnit(unit->getID(), unit->getOwner(), unit->getPosition());
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

MoveRes Game::endTurn()
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
			_map.destroyUnit((*it)->getPosition());
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



int Game::getCommandPoints(int owner) const
{
	return 0;
}


