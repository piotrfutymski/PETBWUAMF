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
	auto el = this->endTurn();
	res = res + el;
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
	if (std::find_if(inHand.begin(), inHand.end(), [orderToSwap](size_t num) {
		return (orderToSwap == num); }) == inHand.end())throw;
	
	if (inDeck.empty())
		throw;

	auto n = rand() % inDeck.size();
	auto res = *(inDeck.begin() + n);
	
	if (toSwap->getRestUses() == 0)
		this->destroyObject<Order>(toSwap);
	else
		toSwap->changeLocation();

	this->getObject<Order>(res)->changeLocation();
	this->substractCommandPoints(_activePlayer, 2);
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
		if (o->getOwner() == player && o->getLocation() == Order::Location::InHand && this->canBeUsed(o.get()))
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
		if (o->getOwner() == player && o->getLocation() == Order::Location::InHand && this->canBeSwaped(o.get()))
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
	return this->getObject<Order>(o)->getPrototype()->_targetCount;
}

const Map & Game::getMap()const
{
	return _map;
}

size_t Game::getUnitOnPosition(const sf::Vector2i & pos) const
{
	return _map[pos].unit->getID();
}

MoveRes Game::moveUnit(size_t unitId, const sf::Vector2i & pos)
{
	auto res = MoveRes{};
	auto unit = this->getObject<Unit>(unitId);
	MoveRes::MoveEvent evnt;
	evnt.position = pos;
	evnt.time = 10;
	evnt.type = MoveRes::EventType::Moved;
	evnt.unit = unitId;
	res.events.push_back(std::move(evnt));

	for (auto & enemy : _map.getEnymeNeightbours(unit))
	{
		if (!enemy->hasFlag(UFlag::Ranged))
		{
			auto m = this->fight(enemy->getID(), unit->getID(), AttackType::Ocassional);
			m.events[0].time = 2;
			m.events[1].time = 2;
			if(m.events.size()>2)
				m.events[2].time = 4;
			res = res + m;
		}
	}
	_map.moveUnit(unit, pos);
	return res;

}
/*
MoveRes Game::fight(size_t aggresor, size_t victim, const AttackType & t)
{
	auto aggresUnit = this->getObject<Unit>(aggresor);
	auto victUnit = this->getObject<Unit>(victim);

	return this->fight(aggresor, victim,const AttackType & t);
}
*/
MoveRes Game::fight(size_t aggresor, size_t victim, const AttackType & t)
{
	//Przed atakiem
	auto res = MoveRes{};
	auto aggresUnit = this->getObject<Unit>(aggresor);
	auto victUnit = this->getObject<Unit>(victim);

	
	MoveRes::MoveEvent evnt;
	evnt.time = 15;
	evnt.type = MoveRes::EventType::BeingAttacked;
	evnt.unit = victim;
	res.events.push_back(std::move(evnt));

	Unit::AttackRes dmg;
	//Atak
	if (t == AttackType::Charge)
		dmg = aggresUnit->chargeAttack(victUnit);
	else if (t == AttackType::Ocassional)
		dmg = aggresUnit->occasionAttack(victUnit);
	else if (t == AttackType::Normal)
		dmg = aggresUnit->normalAttack(victUnit);
	//Po Ataku
	/*
	if (dmg.type == Unit::AttackResType::Miss)
	{
		evnt.time = 15;
		evnt.unit = aggresor;
		evnt.type = MoveRes::EventType::Miss;
		res.events.push_back(std::move(evnt));
		return res;
	}
	*/
	evnt.time = 20;
	evnt.type = MoveRes::EventType::DMGTaken;
	evnt.unit = victim;
	evnt.dmg = dmg.value;
	res.events.push_back(std::move(evnt));
	if (dmg.valueSecond != 0)
	{
		evnt.time = 20;
		evnt.type = MoveRes::EventType::DMGTaken;
		evnt.unit = aggresor;
		evnt.dmg = dmg.valueSecond;
		res.events.push_back(std::move(evnt));
	}

	if (dmg.type == Unit::AttackResType::Draw)
	{
		evnt.time = 15;
		evnt.unit = aggresor;
		evnt.type = MoveRes::EventType::Hitting;
		res.events.push_back(std::move(evnt));
		return res;
	}
	else if (dmg.type == Unit::AttackResType::Win)
	{
		evnt.time = 15;
		evnt.unit = aggresor;
		evnt.type = MoveRes::EventType::CriticalHit;
		res.events.push_back(std::move(evnt));
		return res;
	}
	else
	{
		evnt.time = 15;
		evnt.unit = aggresor;
		evnt.type = MoveRes::EventType::Miss;
		res.events.push_back(std::move(evnt));
		return res;
	}
}

MoveRes Game::buff(const std::string & buffName, size_t buffTarget, float value)
{
	auto res = MoveRes{};
	auto target = this->getObject<Unit>(buffTarget);

	auto buff = target->addBuff(buffName);
	if (value != 0)
		buff->setValue(value);
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
/*
float Game::chances(size_t aggresor, size_t victim, const AttackType & t) const
{
	auto aggresUnit = this->getObject<Unit>(aggresor);
	auto victUnit = this->getObject<Unit>(victim);

	if (t == AttackType::Normal)
		return this->chances(aggresor, victim, aggresUnit->getAttack(),  victUnit->getDefence());
	else if (t == AttackType::Charge)
		return this->chances(aggresor, victim, aggresUnit->getAttack(), victUnit->getChargeDefence());
	else
		return this->chances(aggresor, victim, aggresUnit->getAttack(), victUnit->getDefence());


}

float Game::chances(size_t aggresor, size_t victim, int at, int d) const
{
	auto aggresUnit = this->getObject<Unit>(aggresor);
	auto victUnit = this->getObject<Unit>(victim);
	return aggresUnit->chanceToHit(victUnit, at, d);
}
*/
float Game::chances(size_t aggresor, size_t victim, const AttackType & t) const
{
	auto aggresUnit = this->getObject<Unit>(aggresor);
	auto victUnit = this->getObject<Unit>(victim);

	if (t == AttackType::Normal)
	{
		auto pair = aggresUnit->normalChance(victUnit);
		return ((pair.first / 1000.0) * (pair.second / 1000.0));
	}

	else if (t == AttackType::Charge)
	{
		auto pair = aggresUnit->chargeChance(victUnit);
		return ((pair.first / 1000.0) * (pair.second / 1000.0));
	}

	else
	{
		auto pair = aggresUnit->normalChance(victUnit);
		return ((pair.first / 1000.0) * (pair.second / 1000.0));
	}



}
void Game::createObjects(const GameInitiator & i)
{

	for (auto &u : i._units)
	{
		Unit * unit;
		if (u.second.x < 8)
			unit = this->createObject<Unit>(u.first, 0);
		else
			unit = this->createObject<Unit>(u.first, 1);

		_map.setNewUnit(unit, u.second);
	}

	for (auto &o : i._fPlayerOrders)
		auto order = this->createObject<Order>(o, 0);

	for (auto &o : i._sPlayerOrders)
		auto order = this->createObject<Order>(o, 1);
}

void Game::newRound()
{
	for (auto &u : _units)
	{
		_unitsInMoraleOrder.push_back(u.get());
	}

	_player0CommandPoints = 16;
	_player1CommandPoints = 16;

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
	this->substractCommandPoints(_activePlayer, o->getCost());
	return o->execute(this, m);

}

MoveRes Game::endTurn()
{
	MoveRes::MoveEvent evnt;

	auto res = _activeUnit->endTurn();

	_unitsInMoraleOrder.erase(_unitsInMoraleOrder.begin());
	auto it = _units.begin();
	while (it != _units.end())
	{
		if ((*it)->isDead())
		{
			auto itt = std::find(_unitsInMoraleOrder.begin(), _unitsInMoraleOrder.end(), it->get());
			if(itt != _unitsInMoraleOrder.end())
				_unitsInMoraleOrder.erase(std::remove(_unitsInMoraleOrder.begin(), _unitsInMoraleOrder.end(), it->get()));
			_map.destroyUnit((*it).get());
			
			evnt.time = 30;
			evnt.type = MoveRes::EventType::UnitDestroyed;
			evnt.unit = evnt.unit = (*it)->getID();
			res.events.push_back(std::move(evnt));
			it = _units.erase(it);
		}
		else
			it++;
	}
	return res;
}

bool Game::canBeUsed(Order * o) const
{
	int cP = _player0CommandPoints;
	if (_activePlayer == 1)
		cP = _player1CommandPoints;

	if (o->getCost() > cP || (this->getPossibleTargets(o->getID()).empty() && o->getPrototype()->_target != OrderPrototype::TargetType::BuffT))
		return false;
	return o->canBeUsed(_activeUnit->getPrototype()->getName(), _activeUnit->getPrototype()->_unitType);
}

bool Game::canBeSwaped(Order * o) const
{
	int cP = _player0CommandPoints;
	if (_activePlayer == 1)
		cP = _player1CommandPoints;

	if (2 > cP || this->getOrdersInDeck(_activePlayer).empty())
		return false;
	return true;
}

std::vector<Target> Game::getPossibleMoveTargets() const
{
	auto res = std::vector<Target>();

	for (auto & spot : _map.getPaths(_activeUnit))
	{
		res.push_back({ {}, spot.position });
	}

	return res;
}

std::vector<Target> Game::getPossibleAttackTargets() const
{
	auto res = std::vector<Target>();
	if (_activeUnit->hasFlag(UFlag::Ranged) && _activeUnit->isInFight() == false)
	{
		for (auto & unit : _units)
		{
			if (unit->getOwner() != _activeUnit->getOwner() && _activeUnit->getDistanceTo(unit.get()) <= _activeUnit->getRange())
				res.push_back({ unit->getID(), {} });
		}
	}
	else
	{
		for (auto & unit : _activeUnit->getEnemyInFightWhith())
			res.push_back({ unit->getID(), {} });
	}
	return res;
}

std::vector<Target> Game::getPossibleChargeTargets() const
{
	auto res = std::vector<Target>();
	if (_activeUnit->isInFight())
		return res;

	for (auto & spot : _map.getPathsEndingInZoneOfControle(_activeUnit))
	{
		for (auto & unit : _map.getNeightbours(spot.position))
		{
			if(unit->getOwner() != _activeUnit->getOwner())
				res.push_back({ unit->getID(), spot.position });
		}		
	}

	return res;

}

std::vector<Target> Game::getPossilbeBuffAllayTargets() const
{
	auto res = std::vector<Target>();
	for (auto & unit : _units)
	{
		if (unit->getOwner() == _activeUnit->getOwner())
			res.push_back({ unit->getID(), {} });
	}
	return res;
}

std::vector<Target> Game::getPossibleBuffEnemyTargets() const
{
	auto res = std::vector<Target>();
	for (auto & unit : _units)
	{
		if (unit->getOwner() != _activeUnit->getOwner())
			res.push_back({ unit->getID(), {} });
	}
	return res;
}

std::vector<Target> Game::getPossibleCreateTargets() const
{
	auto res = std::vector<Target>();

	for (auto & spot : _map.getPaths(_activeUnit, 1.5))
	{
		res.push_back({ {}, spot.position });
	}

	return res;
}

void Game::substractCommandPoints(int player, int count)
{
	if (player == 0)
		_player0CommandPoints -= count;
	else
		_player1CommandPoints -= count;
}
