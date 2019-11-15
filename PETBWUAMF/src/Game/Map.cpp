#include "Map.h"



Map::Map()
{
	for (int i = 0; i < MAP_WIDTH; i++)
		for (int j = 0; j < MAP_HEIGHT; j++)
			_mapData[i][j] = { -1, 0 };
}

Map::~Map()
{
}

void Map::setUnitPosition(size_t u, int o, const sf::Vector2i & pos)
{
	if (!this->properPosition(pos))
	{
		Logger::log("Trying to set unit at wrong position on Map");
		return;
	}
	if (o != 0 && o != 1)
	{
		Logger::log("Owner must be 1 or 0");
		return;
	}

	_mapData[pos.x][pos.y] = { u,o };

}

void Map::removeUnitFromPosition(const sf::Vector2i & pos)
{
	if (!this->properPosition(pos))
		return;

	_mapData[pos.x][pos.y] = {-1, 0};
}

void Map::moveUnitFromPosition(const sf::Vector2i & start, const sf::Vector2i & end)
{
	if (_mapData[end.x][end.y].first != -1)
	{
		Logger::log("Can't move unit to place with another unit");
		return;
	}

	auto u = _mapData[start.x][start.y];
	this->removeUnitFromPosition(start);
	this->setUnitPosition(u.first, u.second, end);
}

std::vector<size_t> Map::getNeightbours(size_t u)const
{
	auto res = std::vector<size_t>();
	auto pos = this->findUnitPosition(u);
	if (pos.x == -1)
		return res;

	for (int i = pos.x - 1; i <= pos.x + 1; i++)
	{
		for (int j = pos.y - 1; j < pos.y + 1; j++)
		{
			if (this->properPosition({ i,j }))
				if (_mapData[i][j].first != -1 && pos != sf::Vector2i{ i,j })
					res.push_back(_mapData[i][j].first);
		}		
	}
		

	return res;
}

std::vector<sf::Vector2i> Map::getPaths(size_t u, int move)const
{
	PathFinder pathFinder(MAP_WIDTH, MAP_HEIGHT);
	auto unit = this->findUnit(u);
	auto pos = unit.first;

	for (int i = 0; i < MAP_WIDTH; i++)
	{
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			if (_mapData[i][j].first != -1 && unit.second == _mapData[i][j].second)
				pathFinder.addAllay({ i,j });
			if (_mapData[i][j].first != -1 && unit.second != _mapData[i][j].second)
				pathFinder.addEnemy({ i,j });
		}
	}
		

	if (pos.x == -1)
		return {};
	return pathFinder.getGoodPositions(pos, move);

}

std::vector<sf::Vector2i> Map::posInFightAfterMove(size_t u, int move) const
{
	auto unit = this->findUnit(u);
	auto owner = unit.second;

	auto positions = this->getPaths(u, move);
	auto res = std::vector<sf::Vector2i>();

	for (auto & x : positions)
	{
		auto neights = this->getNeightboursOfPos(x);
		for (auto & n : neights)
		{
			if (n.second != owner)
			{
				res.push_back(x);
				break;
			}
		}
	}
	return res;
}


sf::Vector2i Map::findUnitPosition(size_t u)const
{
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			if (_mapData[i][j].first == u)
				return{ i,j };
		}		
	}
		

	return{ -1,-1 };

}

std::pair<sf::Vector2i, int> Map::findUnit(size_t u) const
{
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			if (_mapData[i][j].first == u)
				return { {i,j}, _mapData[i][j].second };
		}
			
	}	

	return { {-1,-1}, 0 };
}

bool Map::properPosition(const sf::Vector2i & pos)const
{
	if (pos.x >= 0 && pos.x < MAP_WIDTH && pos.y >= 0 && pos.y < MAP_HEIGHT)
		return true;
	return false;
}

std::vector<std::pair<size_t, int>> Map::getNeightboursOfPos(const sf::Vector2i & pos) const
{
	auto res =  std::vector<std::pair<size_t, int>>();
	if (pos.x == -1)
		return res;

	for (int i = pos.x - 1; i <= pos.x + 1; i++)
	{
		for (int j = pos.y - 1; j <= pos.y + 1; j++)
		{
			if (this->properPosition({ i,j }))
				if (_mapData[i][j].first != -1 && pos != sf::Vector2i{ i,j })
					res.push_back(_mapData[i][j]);
		}
	}
	return res;
}
