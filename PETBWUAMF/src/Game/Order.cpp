#include "Order.h"

Order::Order(const std::string & name, int owner)
	:GameObject<OrderPrototype>(name), _owner(owner)
{
	_useNum = this->getPrototype()->_useNum;
}

int Order::getOwner() const
{
	return _owner;
}

int Order::getCost() const
{
	return this->getPrototype()->_cost;
}

int Order::getRestUses() const
{
	return _useNum;
}

int Order::getTargetsCount() const
{
	return this->getPrototype()->_targetCount;
}

Order::Location Order::getLocation() const
{
	return _location;
}

void Order::changeLocation()
{
	if (_location == Order::Location::InDeck)
		_location = Order::Location::InHand;
	else
		_location = Order::Location::InDeck;
}

MoveRes Order::execute(Game * game, const Move & m)
{
	if(_useNum > 0)
		_useNum--;
	return this->getPrototype()->_execute(game, m);
}

bool Order::canBeUsed(const std::string & unitName, const std::string & unitType)
{
	if (_useNum == 0)
		return false;

	if (this->getPrototype()->_canBeUsedOnAllUnit)
		return true;

	auto possibleUnits = this->getPrototype()->_allowedUnits;
	auto possibleTypes = this->getPrototype()->_allowedTypes;
	bool a = std::find(possibleUnits.begin(), possibleUnits.end(), unitName) != possibleUnits.end();
	bool b = std::find(possibleTypes.begin(), possibleTypes.end(), unitType) != possibleTypes.end();
	if (a || b)
		return true;
	return false;
}

float Order::getChances(Game * game, const Move & m)
{
	auto t = this->getPrototype()->_target;
	if ((t == OrderPrototype::TargetType::AttackT || t == OrderPrototype::TargetType::ChargeT) && this->getPrototype()->_chances != nullptr)
	{
			return this->getPrototype()->_chances(game, m);
	}
	return -1;
}


