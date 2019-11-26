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
	if (!this->isInArea(pos))
		return;
	_matrix[pos.x][pos.y] = 1;
}

void PathFinder::addEnemy(const sf::Vector2i & pos)
{
	if (!this->isInArea(pos))
		return;
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


std::vector<sf::Vector2i> PathFinder::getGoodPositions(const sf::Vector2i & start, float move)
{
	auto temp = std::vector<std::vector<float>>();
	for (int i = 0; i < _xSize; i++)
	{
		temp.push_back(std::vector<float>());
		for (int j = 0; j < _ySize; j++)
			temp[i].push_back(-1);
	}

	this->calculatePath(start, (float)move, temp);
	auto res = std::vector<sf::Vector2i>{};
	
	for (int i = 0; i < _xSize; i++)
		for (int j = 0; j < _ySize; j++)
			if(temp[i][j] >= 0)
				res.push_back({i, j});
	return res;
}

void PathFinder::calculatePath(const sf::Vector2i & start, float move, std::vector<std::vector<float>>& positions)
{
	if (move <0)
		return;
	if (move < 1)
	{
		positions[start.x][start.y] = move;
		return;
	}
	positions[start.x][start.y] = move;


	for (int i = start.x - 1; i <= start.x + 1; i++)
	{
		for (int j = start.y - 1; j <= start.y + 1; j++)
		{
			if (i == start.x && j == start.y)
				continue;
			if (!this->isInArea({ i,j }))
				continue;
			if (_matrix[i][j] == 1)
				continue;
			if (_matrix[i][j] == 0)
			{
				if (i == start.x || j == start.y)
				{
					if (positions[i][j] < move - 1.f)
					{
						PathFinder p = *this;
						for (int u = start.x - 1; u <= start.x + 1; u++)
						{
							for (int v = start.y - 1; v <= start.y + 1; v++)
								if (u != i || v != j)
									p.addAllay({ u,v });
						}
						p.calculatePath({ i,j }, move - 1.f, positions);
					}
				}
				else
				{
					if (positions[i][j] < move - 1.41f)
					{
						PathFinder p = *this;
						for (int u = start.x - 1; u <= start.x + 1; u++)
						{
							for (int v = start.y - 1; v <= start.y + 1; v++)
								if (u != i || v != j)
									p.addAllay({ u,v });
						}
						p.calculatePath({ i,j }, move - 1.41f, positions);
					}
				}
					
			}
			else if ( _matrix[i][j] == 2)
			{
				PathFinder p = *this;
				p.addAllay(start);
				if (i == start.x || j == start.y)
					p.calculatePath({ i,j }, std::min(move - 1.f, 0.0f),positions);
				else
					p.calculatePath({ i,j }, std::min(move - 1.41f, 0.0f), positions);
			}
		}
	}
}

float PathFinder::getSquereDistance(const sf::Vector2i & first, const sf::Vector2i & second)
{
	return (first.x - second.x)*(first.x - second.x) + (first.y - second.y)*(first.y - second.y);
}


