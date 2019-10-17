#include "Player.h"

Didax::Player::Player()
{
}

Didax::Player::~Player()
{
}

void Didax::Player::init(Board * b, AssetMeneger * a)
{
	_board = b;
	_assets = a;
}

void Didax::Player::setUnitsAndOrdersAsAllay(Canvas * root, const std::vector<std::function<void(Order *)>> & funcO, const std::vector<std::function<void(Unit *)>> & funcU)
{
	this->setUnitsOnSide(0, root, funcU);
	int p = 0;
	for (size_t i = 0; i < _playerOrders.size(); i++)
	{
		if (_playerOrders[i]->isInHand())
		{
			_playerOrders[i]->showInHand(_assets, p, root, funcO[0], funcO[1]);
			p++;
		}
	}

}

void Didax::Player::setUnitsAsEnemy(Canvas * root, const std::vector<std::function<void(Unit *)>> & funcU)
{
	this->setUnitsOnSide(1, root, funcU);
}

void Didax::Player::setOrdersWaitingForChoose(const std::function<void(Order *)> & f)
{
	for (size_t i = 0; i < _playerOrders.size(); i++)
	{
		if (_playerOrders[i]->isInHand())
		{
			_playerOrders[i]->setAsChoosable(f);
		}
	}
}

void Didax::Player::setForWaitingOnOrderTarget(Order * o)
{
}

void Didax::Player::addUnit(Unit * u)
{
	_playerUnits.push_back(u);
}

void Didax::Player::addOrder(Order * o)
{
	_playerOrders.push_back(o);
}

void Didax::Player::setUnitsOnSide(int s, Canvas * root, const std::vector<std::function<void(Unit *)>> & funcU)
{
	for (size_t i = 0; i < _playerUnits.size(); i++)
	{
		_playerUnits[i]->setOnTable(_assets, s, root, funcU[0], funcU[1]);
	}

}
