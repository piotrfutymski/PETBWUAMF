#include "Buff.h"

Buff::Buff(const std::string & name, size_t u)
	:GameObject<BuffPrototype>(name), _owner(u)
{

	_time = this->getPrototype()->_time;
	_isInstant = this->getPrototype()->_instant;

	for (auto &a : this->getPrototype()->_actions)
	{
		_actions.push_back({ BuffType(a.type),a.value,a.add,a.onStart,a.onEnd });
	}
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
void Buff::setBoostValue(float v)
{
	_boostValue = v;
}

float Buff::getBoostValue() const
{
	return _boostValue;
}

