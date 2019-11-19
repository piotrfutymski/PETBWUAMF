#include "Buff.h"

Buff::Buff(const std::string & name, size_t u)
	:GameObject<BuffPrototype>(name)
{
	_unit = u;
	_restTime = this->getPrototype()->_time;
	this->getPrototype()->_onBegin(u, this);

}


Buff::~Buff()
{
}


size_t Buff::getOwner() const
{
	return _unit;
}

int Buff::getRestTime() const
{
	return _restTime;
}

bool Buff::onTurnEnd()
{
	this->getPrototype()->_onTurnEnd(_unit, this);
	if (_restTime <= 0)
	{
		this->getPrototype()->_onEnd(_unit, this);
		return true;
	}
	_restTime--;
	return false;
}
void Buff::setBoostValue(int v)
{
	_boostValue = v;
}

int Buff::getBoostValue() const
{
	return _boostValue;
}

