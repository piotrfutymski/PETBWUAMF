#include "Unit.h"

namespace Didax
{

Unit::Unit(Engine * eng, UnitPrototype * prototype):GameObject(eng)
{
	_prototype = prototype;
	_attack = _prototype->_attack;
	_health = _prototype->_health;
	_defense = _prototype->_defense;

}

Unit::~Unit()
{
}

void Unit::setPosition(int pos)
{
	_position = pos;
}

void Unit::setOwner(int o)
{
	_owner = o;
}

int Unit::getPositionOnBord(int side) const
{
	return (side * 8 + _position);
}


Canvas * Unit::setOnTable(AssetMeneger * assets, int side)
{
	auto res = this->openGUI<UnitRepresentation>("UnitRepresentation", assets);
	auto URep = this->getGUI<UnitRepresentation>("UnitRepresentation");
	URep->setUnit(_prototype->_texture, assets);
	URep->setAttack(this->getParameterColorA(), _attack);
	URep->setDefence(this->getParameterColorD(), _defense);
	URep->setHealth(this->getParameterColorH(), _health);
	URep->setPosition(this->getPositionOnBord(side));
	return res;
}

UnitRepresentation::ParameterColor Unit::getParameterColorA()
{
	if (_prototype->_attack == _attack)
		return UnitRepresentation::ParameterColor::white;
	else if (_prototype->_attack > _attack)
		return UnitRepresentation::ParameterColor::red;
	else
		return UnitRepresentation::ParameterColor::green;
}

UnitRepresentation::ParameterColor Unit::getParameterColorD()
{
	if (_prototype->_defense == _defense)
		return UnitRepresentation::ParameterColor::white;
	else if (_prototype->_defense > _defense)
		return UnitRepresentation::ParameterColor::red;
	else
		return UnitRepresentation::ParameterColor::green;
}

UnitRepresentation::ParameterColor Unit::getParameterColorH()
{
	if (_prototype->_health == _health)
		return UnitRepresentation::ParameterColor::white;
	else if (_prototype->_health > _health)
		return UnitRepresentation::ParameterColor::red;
	else
		return UnitRepresentation::ParameterColor::green;
}


}