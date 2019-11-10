#include "Order.h"

Order::Order(const std::string & name)
	:GameObject<OrderPrototype>(name)
{

}

int Order::getTargetsCount() const
{
	return this->getPrototype()->_targets.size();
}

void Order::setOwner(int player)
{
	if (player == 0 || player == 1)
		_owner = player;
}

int Order::getOwner() const
{
	return _owner;
}

bool Order::canBeUsed(Unit * u)const
{
	return this->getPrototype()->_canBeUsed(u);
}

OrderPrototype::Target Order::getTargetType(int n)const
{
	return this->getPrototype()->_targets[n];
}

bool Order::canBeATarget(Unit * u, int n, const sf::Vector2i & pos)const
{
	return this->getPrototype()->_isProperAsTargetP(u, n, pos);
}

bool Order::canBeATarget(Unit * u, int n, size_t unit)const
{
	return this->getPrototype()->_isProperAsTargetU(u, n, unit);
}

bool Order::execute(Unit *u, const Move & m)
{
	return this->getPrototype()->_execute(u, m);
}

