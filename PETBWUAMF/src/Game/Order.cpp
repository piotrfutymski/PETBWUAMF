#include "Order.h"

Order::Order(const std::string & name)
	:GameObject<OrderPrototype>(name)
{

}

int Order::getTargetsCount() const
{
	return this->getPrototype()->_targets.size();
}

std::vector<OrderPrototype::Target> Order::getProperTargets(Unit *u, int n) const
{
	return std::move(this->getPrototype()->_getProperTargets(u, n));
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

bool Order::execute(Unit *u, const Move & m)
{
	return this->getPrototype()->_execute(u, m);
}

