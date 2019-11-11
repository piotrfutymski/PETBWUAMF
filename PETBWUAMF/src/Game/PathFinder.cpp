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
	if (pos.x > 0 && pos.x < _xSize && pos.y > 0 && pos.y < _ySize)
		return true;
	return false;
}

bool PathFinder::pathExist(const sf::Vector2i & start, const sf::Vector2i & target, float move)
{
	if (start == target && move >= 0)
		return true;
	if (move <= 0)
		return false;

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
					if (p.pathExist({ i,j }, target, move - 1))
						return true;
					else if (p.pathExist({ i,j }, target, move - 1.41))
						return true;
			}
			else if (this->isInArea({ i,j }) && _matrix[i][j] == 2)
			{
				PathFinder p = *this;
				p.addAllay(start);
				if (i == start.x || j == start.y)
					if (p.pathExist({ i,j }, target, std::min(move - 1, 0.0f)))
						return true;
					else if (p.pathExist({ i,j }, target, std::min(move - 1, 0.0f)))
						return true;
			}
		}
	}

	return false;


}
