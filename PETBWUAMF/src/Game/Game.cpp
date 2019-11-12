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

	std::sort(_unitsInMoraleOrder.begin(), _unitsInMoraleOrder.end(), [](Unit * a, Unit * b) {
		int am = a->getMorale();
		int bm = b->getMorale();
			return am > bm;
	});
	_activeUnit = *_unitsInMoraleOrder.begin();

	return true;
}

void Game::logState(int owner)const
{
	Logger::log("---------------------------------------------------------");
	Logger::log("------------------------New Turn-------------------------");
	Logger::log("---------------------------------------------------------");
	this->logStateUnits(owner);
	this->logStateUnits((owner+1)%2);
	this->logStateOrders(owner);
	this->logSimpleMap();
	Logger::log("---------------------------------------------------------");
	Logger::log(_activeUnit->getPrototype()->getName() + "'s Turn.");
}

void Game::logStateUnits(int owner)const
{
	Logger::log("---------------------------------------------------------");
	Logger::log("---------------------Player " + std::to_string(owner) + " Units----------------------");
	Logger::log("---------------------------------------------------------");
	for (auto &x : _units)
	{
		if (x->getOwner() == owner)
		{
			Logger::logW("ID:" + std::to_string(x->getID()) + " Name: ");
			x->getSimpleInfo();
			/*Logger::log(std::to_string(x->getID()) + ": " + x->getPrototype()->getName() + " on pos (" + std::to_string(x->getPosition().x) + "," + std::to_string(x->getPosition().y) + ")");
			Logger::log("Attack: " + std::to_string(x->getAttack()) + " Protection: " + std::to_string(x->getProtection()) + " Health: " + std::to_string(x->getHealth()));
			Logger::log("---------------------------------------------------------");*/
		}
	}
}
void Game::logStateOrders(int owner)const
{
	Logger::log("---------------------------------------------------------");
	Logger::log("--------------------Player " + std::to_string(owner) + " Orders----------------------");
	Logger::log("---------------------------------------------------------");
	for (auto &x : _orders)
	{
		if (x->getOwner() == owner)
		{
			Logger::log(std::to_string(x->getID()) + ": " + x->getPrototype()->getName());
			Logger::log("---------------------------------------------------------");
		}
	}
}
bool Game::isEnded() const
{
	return _isEnded;
}

void Game::logPossibleMoves()
{
	Logger::log("TODO\n");
}
std::vector<std::vector<char>> Game::logStartMap()const
{
	int sizeX = Unit::MAXPOS.x;
	int sizeY = Unit::MAXPOS.y;
	std::vector<std::vector<char>> map;
	//char map[16][10];
	for (int x = 0; x <= sizeX; x++)
	{
		map.push_back(std::vector<char>());
		for (int y = 0; y <= sizeY; y++)
		{
			map[x].push_back('O');
		}
	}
	return map;
}
void Game::logSimpleMap()const
{
	auto map = logStartMap();


	for (auto &unit : _units)
	{
		if (unit->getOwner()==0)
			map[unit->getPosition().x][unit->getPosition().y] = 'F';
		else
			map[unit->getPosition().x][unit->getPosition().y] = 'S';
	}
	map[_activeUnit->getPosition().x][_activeUnit->getPosition().y] = 'A';

	logConstructMap(map);

}

void Game::logMoveMap(Order *order, int i)const
{
	auto map = logStartMap();

	for (auto x : order->getProperTargets(_activeUnit, i))
	{
		map[x.pos.x][x.pos.y] = 'M';
	}

	for (auto &unit : _units)
	{
		if (unit->getOwner() == 0)
			map[unit->getPosition().x][unit->getPosition().y] = 'F';
		else
			map[unit->getPosition().x][unit->getPosition().y] = 'S';
	}
	map[_activeUnit->getPosition().x][_activeUnit->getPosition().y] = 'A';

	logConstructMap(map);
}

void Game::logConstructMap(std::vector<std::vector<char>> map) const
{
	int sizeX = Unit::MAXPOS.x;
	int sizeY = Unit::MAXPOS.y;
	Logger::logW("    |");
	for (int y = 0; y <= sizeY; y++)
	{
		Logger::logW(std::to_string(y));
		Logger::logW("|");
	}
	Logger::log("");
	Logger::log("  |X|X|X|X|X|X|X|X|X|X|X|X|");
	//Logger::log("   XXXXXXXXXXXX");
	for (int x = 0; x <= sizeX; x++)
	{
		if (x < 10)
			Logger::logW(std::to_string(x) + " ");
		else
			Logger::logW(std::to_string(x));
		Logger::logW("|X|");
		for (int y = 0; y <= sizeY; y++)
		{
			if (map[x][y] == 'A')
				std::cout << yellow;

			else if (map[x][y] == 'F')
				std::cout << blue;

			else if (map[x][y] == 'S')
				std::cout << red;

			else if (map[x][y] == 'M')
				std::cout << green;
			Logger::logW(map[x][y]);
			std::cout << white;
			Logger::logW("|");
		}
		Logger::logW("X|");
		Logger::log("");
	}
	//Logger::log("|X|X|X|X|X|X|X|X|X|X|X|X|");
	Logger::log("  |X|X|X|X|X|X|X|X|X|X|X|X|");
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
void  Game::makeMove()
{
	Logger::log("---------------------------------------------------------");
	Logger::log("----------------------Make a move------------------------");
	Logger::log("---------------------------------------------------------");


	Logger::logW("ID:" + std::to_string(_activeUnit->getID()) + " Name: ");
	_activeUnit->getSimpleInfo();
	for (auto &x : this->getPossibleOrders())
	{
		Logger::logW(std::to_string(x->getID()) + ": " + x->getPrototype()->getName() + " ");
	}
	Logger::log("");
	Logger::log("---------------------------------------------------------");
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
