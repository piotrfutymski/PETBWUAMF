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

	return true;
}

bool Game::isEnded() const
{
	return _isEnded;
}

void Game::logPossibleMoves()
{
	Logger::log("TODO\n");
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


Unit * Game::getActiveUnit()
{
	return _activeUnit;
}

size_t Game::getActivePlayer()
{
	return _activePlayer;
}

Move Game::getMoveFromConsole()
{
	Move res;
	res.unitID = _activeUnit->getID();
	_activePlayer = _activeUnit->getOwner();
	this->logState(_activePlayer);

	this->makeMove();
	/*pomoc jest dla slabych							xDDDD
	auto a = std::getchar();
	if (a == 'y')
		logPossibleMoves(); */
	Order * order = nullptr;
	int oID;
	while (1)
	{
		Logger::log("----------------------Pick order id----------------------");
		std::cin >> oID;
		order = this->getObject<Order>(oID);
		if (order == nullptr)
		{
			Logger::log("-------------------Order doesn't exist-------------------");
			continue;
		}
		if (order->canBeUsed(_activeUnit))
		{
			Logger::log("----------------------Choosed order: " + std::to_string(oID) + "-------------------");
			break;
		}
		Logger::log("-------------------Order can't be used-------------------");
	}
	res.orderID = oID;
	Logger::log("---------------------------------------------------------");
	for (size_t i = 0; i < order->getTargetsCount(); i++)
	{
		if (order->getTargetType(i) == OrderPrototype::TargetType::Position_target)
		{
			logMoveMap(order, i);
			Logger::log("--------------------Possible positions(int) (int)--------");
			for (auto x: order->getProperTargets(_activeUnit, i))
			{
				Logger::log(std::to_string(x.pos.x)+";"+std::to_string(x.pos.y));
			}

			Logger::log("----------------------Choose Position (int) (int)--------");
			int x, y;
			std::cin >> x;
			std::cin >> y;
			res.positions.push_back({ x,y });
			Logger::log("---------------------------------------------------------");
		}
		else
		{
			Logger::log("------------------Choose Target ID (int)-----------------");
			if (_activePlayer == 1)
				logStateUnits(0);
			else
				logStateUnits(1);
			int id;
			std::cin >> id;
			res.units.push_back(id);
			Logger::log("---------------------------------------------------------");
		}
	}
	return res;

	
}
