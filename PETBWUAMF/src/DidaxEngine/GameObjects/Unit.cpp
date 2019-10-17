#include "Unit.h"

namespace Didax
{

Unit::Unit(UnitPrototype * prototype, AssetMeneger * assets)
{
	_prototype = prototype;
	_attack = _prototype->_attack;
	_health = _prototype->_health;
	_defense = _prototype->_defense;
	this->createGUI<UnitRepresentation>("UnitRepresentation", assets);
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

const UnitPrototype * Unit::getPrototype() const
{
	return _prototype;
}

int Unit::getPositionOnBord(int side) const
{
	return (side * 8 + _position);
}


void Unit::setOnTable(AssetMeneger * assets, int side, Canvas * parent, const std::function<void(Unit * u)> & hi, const std::function<void(Unit *)> & ho)
{
	this->openGUI(parent, assets, { [hi,this]() {hi(this); } , [ho, this]() {ho(this); } });
	auto URep = this->getGUI<UnitRepresentation>();
	URep->setUnit(_prototype->_texture, assets);
	URep->setAttack(this->getParameterColorA(), _attack);
	URep->setDefence(this->getParameterColorD(), _defense);
	URep->setHealth(this->getParameterColorH(), _health);
	URep->setPosition(this->getPositionOnBord(side));

}

void Unit::setHoverInHoverOutEffects(const std::function<void(Unit * u)> & hi, const std::function<void(Unit *)> & ho)
{
	_representation->setOnHoverInToButton("unit", [hi,this]() {hi(this); });
	_representation->setOnHoverOutToButton("unit", [ho, this]() {ho(this); });
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