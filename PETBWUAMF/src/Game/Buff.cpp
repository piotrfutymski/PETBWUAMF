#include "Buff.h"

Buff::Buff(const std::string & name, size_t u)
	:GameObject<BuffPrototype>(name), _owner(u)
{

	_time = this->getPrototype()->_time;
	_value = this->getPrototype()->_value;
}


Buff::~Buff()
{
}

bool Buff::isGood() const
{
	return this->getPrototype()->_isGood;
}

bool Buff::isInstant() const
{
	return _time < 0;
}

bool Buff::isEffect() const
{
	if (this->getPrototype()->_type == BuffPrototype::BuffType::ParameterBoost)
		return false;
	return true;
}

float Buff::getValue() const
{
	return _value;
}

void Buff::setValue(float v)
{
	_value = v;
}

int Buff::getTime() const
{
	return _time;
}

UParameter Buff::getParameterToBoost() const
{
	return this->getPrototype()->_parameterToBoost;
}

BuffPrototype::BuffType Buff::getType() const
{
	return this->getPrototype()->_type;
}

bool Buff::endTurn()
{
	if(this->getPrototype()->onTurnEnd(_value))
		return true;
	if (_time == 0)
		return true;
	if (_time > 0)
		_time--;
	return false;

}

