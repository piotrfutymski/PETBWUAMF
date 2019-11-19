#include "Order.h"

Order::Order(const std::string & name, int owner)
	:GameObject<OrderPrototype>(name)
{
	_owner = owner;

	cost = this->getPrototype().
}

int Order::getTargetsCount() const
{
	return this->getPrototype()->_targets.size();
}

std::vector<OrderPrototype::Target> Order::getProperTargets(const Unit *u, int n, const Move & m) const
{
	return std::move(this->getPrototype()->_getProperTargets(u, n, m));
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

OrderPrototype::TargetType Order::getTargetType(int n)const
{
	return this->getPrototype()->_targets[n];
}

MoveRes Order::execute(Unit *u, const Move & m)
{
	return this->getPrototype()->_execute(u, m);
}

