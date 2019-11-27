#include "Map.h"



Map::Map()
{
	for (int i = 0; i < MAP_WIDTH; i++)
		for (int j = 0; j < MAP_HEIGHT; j++)
			_mapData[i][j] = { nullptr, SpotContent::Empty, {i,j} };
}

Map::~Map()
{
}

void Map::setNewUnit(Unit * u, const sf::Vector2i & pos)
{
	if (!this->properPosition(pos))
	{
		Logger::log("Trying to set new unit at wrong position on Map");
		throw;
	}

	u->setPosition(pos);
	_mapData[pos.x][pos.y].unit = u;
	_mapData[pos.x][pos.y].content = SpotContent::Unit;

	this->setZoneForUnit(u);

}

void Map::destroyUnit(Unit * u)
{
	auto pos = u->getPosition();
	_mapData[pos.x][pos.y].unit = nullptr;
	_mapData[pos.x][pos.y].content = SpotContent::Empty;
	this->resetZoneForUnit(u);
	u->clearInFightWith();
}

void Map::moveUnit(Unit * u, const sf::Vector2i & newPosition)
{
	this->destroyUnit(u);
	this->setNewUnit(u, newPosition);
}

const std::vector<Unit *> Map::getNeightbours(Unit * u)const
{
	return this->getNeightbours(u->getPosition());
}


bool Map::properPosition(const sf::Vector2i & pos)const
{
	if (this->inArea(pos) && _mapData[pos.x][pos.y].content != SpotContent::Unit)
		return true;
	return false;
}

bool Map::inArea(const sf::Vector2i & pos) const
{
	if (pos.x >= 0 && pos.x < MAP_WIDTH && pos.y >= 0 && pos.y < MAP_HEIGHT)
		return true;
	return false;
}

void Map::setZoneForUnit(Unit * u)
{
	auto pos = u->getPosition();
	auto owner = u->getOwner();
	SpotContent zoneType = SpotContent::Player0ControlZone;
	SpotContent enZoneType = SpotContent::Player1ControlZone;
	if (owner == 1)
		std::swap(zoneType, enZoneType);

	for (int i = pos.x - 1; i <= pos.x + 1; i++)
	{
		for (int j = pos.y - 1; j <= pos.y + 1; j++)
		{
			if (this->properPosition({ i,j }))
			{
				if (_mapData[i][j].content == SpotContent::Empty)
					_mapData[i][j].content = zoneType;
				if (_mapData[i][j].content == enZoneType)
					_mapData[i][j].content = SpotContent::DuoControlZone;
			}
			else if(this->inArea({i,j}))
			{
				if (_mapData[i][j].unit->getOwner() != u->getOwner())
				{
					u->addInFightWith(_mapData[i][j].unit);
					_mapData[i][j].unit->addInFightWith(u);
				}
			}
		}
	}
}

void Map::resetZoneForUnit(Unit * u)
{
	auto pos = u->getPosition();

	for (int i = pos.x - 1; i <= pos.x + 1; i++)
	{
		for (int j = pos.y - 1; j <= pos.y + 1; j++)
		{
			if (this->properPosition({ i,j }))
			{
				bool f = false;
				bool s = false;
				auto neights = this->getNeightbours({ i,j });
				for (auto x : neights)
				{
					if(x->getOwner() != u->getOwner())
						x->removeInFightWith(u);
					if (x->getOwner() == 0)
						f = true;
					if (x->getOwner() == 1)
						s = true;
				}
				if (f && s)
					_mapData[i][j].content = SpotContent::DuoControlZone;
				else if (f)
					_mapData[i][j].content = SpotContent::Player0ControlZone;
				else if (s)
					_mapData[i][j].content = SpotContent::Player1ControlZone;
				else
					_mapData[i][j].content = SpotContent::Empty;
			}
		}
	}

}

const std::vector<Map::Spot> Map::getPositionsWihtContent(const SpotContent & content) const
{
	auto res = std::vector<Spot>();

	for (int i = 0; i < MAP_WIDTH; i++)
	{
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			if (_mapData[i][j].content == content)
				res.push_back(_mapData[i][j]);
		}
	}

	return res;
}

const std::vector<Unit*> Map::getAllayedNeightbours(Unit * u) const
{
	auto res = this->getNeightbours(u);
	auto it = res.begin();
	auto owner = u->getOwner();
	while (it != res.end())
	{
		if ((*it)->getOwner() != owner)
			it = res.erase(it);
		else
			++it;
	}
	return res;
}

const std::vector<Unit*> Map::getEnymeNeightbours(Unit * u) const
{
	auto res = this->getNeightbours(u);
	auto it = res.begin();
	auto owner = u->getOwner();
	while (it != res.end())
	{
		if ((*it)->getOwner() == owner)
			it = res.erase(it);
		else
			++it;
	}
	return res;
}

const std::vector<Unit *> Map::getNeightbours(const sf::Vector2i & pos) const
{
	auto res = std::vector<Unit *>();
	for (int i = pos.x - 1; i <= pos.x + 1; i++)
	{
		for (int j = pos.y - 1; j < pos.y + 1; j++)
		{
			if (this->inArea({ i,j })&& !(i==pos.x && j== pos.y))
				if (_mapData[i][j].unit != nullptr)
					res.push_back(_mapData[i][j].unit);
		}
	}

	return res;
}

const Map::Spot Map::operator[](const sf::Vector2i & pos) const
{
	return _mapData[pos.x][pos.y];
}

const std::vector<Map::Spot> Map::getPaths(Unit * u, float move) const
{
	auto res = std::vector<Spot>{};

	auto owner = u->getOwner();
	PathFinder pathFinder(MAP_WIDTH, MAP_HEIGHT);

	for (int i = 0; i < MAP_WIDTH; i++)
	{
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			if (_mapData[i][j].content == SpotContent::Unit)
			{
				if(_mapData[i][j].unit->getOwner() == owner)
					pathFinder.addAllay({ i,j });
				else
					pathFinder.addEnemy({ i,j });
			}			
		}
	}

	if (move == 0)
		move = (float)(u->getMove());

	for (auto & x : pathFinder.getGoodPositions(u->getPosition(), move))
	{
		res.push_back(_mapData[x.x][x.y]);
	}
	return res;
}

const std::vector<Map::Spot> Map::getPathsEndingInZoneOfControle(Unit * u) const
{
	auto res = this->getPaths(u);
	auto owner = u->getOwner();
	auto it = res.begin();
	SpotContent enZoneType = SpotContent::Player1ControlZone;
	if (owner == 1)
		enZoneType = SpotContent::Player0ControlZone;

	while (it != res.end())
	{
		if (it->content != enZoneType && it->content != SpotContent::DuoControlZone)
			it = res.erase(it);
		else
			++it;
	}
	return res;
}

const std::vector<Map::Spot> Map::getPositionsInZoneOfControle(int player) const
{
	auto duo = this->getPositionsWihtContent(SpotContent::DuoControlZone);
	std::vector<Map::Spot> single;
	if (player == 0)
		single = this->getPositionsWihtContent(SpotContent::Player0ControlZone);
	else
		single = this->getPositionsWihtContent(SpotContent::Player1ControlZone);

	single.insert(single.end(), duo.begin(), duo.end());
	return single;
}

const std::vector<Map::Spot> Map::getPositionsWithUnit() const
{
	return this->getPositionsWihtContent(SpotContent::Unit);
}
