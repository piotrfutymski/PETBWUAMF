#include "PathFinder.h"

PathFinder::PathFinder(int x, int y)
{
	_xSize = x;
	_ySize = y;

	_matrix.resize(x);
	for (auto & x : _matrix)
	{
		x.resize(y);
	}

}

PathFinder::~PathFinder()
{
}

void PathFinder::addAllay(const sf::Vector2i & pos)
{
	_matrix[pos.x][pos.y] = 1;
}

void PathFinder::addEnemy(const sf::Vector2i & pos)
{
	for (int i = pos.x-1; i <= pos.x +1; i++)
	{
		for (int j = pos.y - 1; j <= pos.y + 1; j++)
		{
			if (this->isInArea({ i,j }) && _matrix[i][j]!=1)
				_matrix[i][j] = 2;
		}
	}
	_matrix[pos.x][pos.y] = 1;
}

bool PathFinder::isInArea(const sf::Vector2i & pos)
{
	if (pos.x >= 0 && pos.x < _xSize && pos.y >= 0 && pos.y < _ySize)
		return true;
	return false;
}

bool PathFinder::pathExist(const sf::Vector2i & start, const sf::Vector2i & target, float move)
{
	auto ref = std::map<int, bool>();
	auto ref2 = std::vector<sf::Vector2i>();
	return _pathExist(start, target, move, ref,ref2);

}

std::map<int, bool> PathFinder::getGoodPositions(const sf::Vector2i & start, int move)
{
	auto notChecked = std::vector<sf::Vector2i>();
	for (int i = 0; i < _xSize; i++)
	{
		for (int j = 0; j < _ySize; j++)
		{
			notChecked.push_back({ i,j });
		}
	}

	auto res = std::map<int, bool>();
	
	while (notChecked.size() > 0)
	{
		auto it = res.find({notChecked.back().x * 1000+notChecked.back().y});
		if (it == res.end())
		{
			auto copy = *this;
			copy._pathExist(start, notChecked.back(), move, res, notChecked);
		}
	}
	return res;
}

bool PathFinder::_pathExist(const sf::Vector2i & start, const sf::Vector2i & target, float move, std::map<int, bool>& positions, std::vector<sf::Vector2i> & notChecked)
{
	if (start == target && move >= 0)
	{
		positions[target.x*1000 + target.y] = true;
		notChecked.erase(std::remove(notChecked.begin(), notChecked.end(), target), notChecked.end());
		return true;
	}
	if (move <= 0 || this->getSquereDistance(start, target) > move *move)
	{
		if(positions[target.x * 1000 + target.y]!=true)
			positions[target.x * 1000 + target.y] = false;
		notChecked.erase(std::remove(notChecked.begin(), notChecked.end(), target), notChecked.end());
		return false;
	}

	for (int i = start.x - 1; i <= start.x + 1; i++)
	{
		for (int j = start.y - 1; j <= start.y + 1; j++)
		{
			if (i == start.x && j == start.y)
				continue;
			if (this->isInArea({ i,j }) && _matrix[i][j] == 0)
			{
				PathFinder p = *this;
				p.addAllay(start);
				if (i == start.x || j == start.y)
				{
					if (p._pathExist({ i,j }, target, move - 1, positions, notChecked))
					{
						return true;
					}
				}
				else if (p._pathExist({ i,j }, target, move - 1.41, positions, notChecked))
				{
					return true;
				}
		
						
			}
			else if (this->isInArea({ i,j }) && _matrix[i][j] == 2)
			{
				PathFinder p = *this;
				p.addAllay(start);
				if (i == start.x || j == start.y)
				{
					if (p.pathExist({ i,j }, target, std::min(move - 1, 0.0f)))
					{
						return true;
					}
				}
				else if (p.pathExist({ i,j }, target, std::min(move - 1, 0.0f)))
				{
					return true;
				}
			
			}
		}
	}

	if (positions[target.x * 1000 + target.y] != true)
		positions[target.x * 1000 + target.y] = false;
	notChecked.erase(std::remove(notChecked.begin(), notChecked.end(), target), notChecked.end());
	return false;
}

float PathFinder::getSquereDistance(const sf::Vector2i & first, const sf::Vector2i & second)
{
	return (first.x - second.x)*(first.x - second.x) + (first.y - second.y)*(first.y - second.y);
}


