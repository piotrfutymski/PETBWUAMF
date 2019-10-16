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

void Didax::Player::setUnitsAndOrdersAsAllay(Canvas * root)
{
	this->setUnitsOnSide(0, root);
	int p = 0;
	for (size_t i = 0; i < _playerOrders.size(); i++)
	{
		if (_playerOrders[i]->isInHand())
		{
			root->addChild(_playerOrders[i]->show(_assets, p));
			p++;
		}
	}

}

void Didax::Player::setUnitsAsEnemy(Canvas * root)
{
	this->setUnitsOnSide(1, root);
}

void Didax::Player::setOrdersAsChoosable()
{
	for (size_t i = 0; i < _playerOrders.size(); i++)
	{
		if (_playerOrders[i]->isInHand())
		{
			_playerOrders[i]->setAsChoosable();
		}
	}
}

void Didax::Player::addUnit(Unit * u)
{
	_playerUnits.push_back(u);
}

void Didax::Player::addOrder(Order * o)
{
	_playerOrders.push_back(o);
}

void Didax::Player::setUnitsOnSide(int s, Canvas * root)
{
	for (size_t i = 0; i < _playerUnits.size(); i++)
	{
		root->addChild(_playerUnits[i]->setOnTable(_assets, s));
	}

}
