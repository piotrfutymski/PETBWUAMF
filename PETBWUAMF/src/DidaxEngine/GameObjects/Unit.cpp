#include "Unit.h"

namespace Didax
{

Unit::Unit(Engine * eng, UnitPrototype * prototype):GameObject(eng)
{
	_prototype = prototype;
	_attack = _prototype->_attack;
	_defense = _prototype->_defense;
	_armor = _prototype->_armor;
	_health = _prototype->_health;

	_rangedAttack = _prototype->_rangedAttack;
	_chargeAttack = _prototype->_chargeAttack;
	_chargeDefense = _prototype->_chargeDefense;

	_description = _prototype->_description;
}


Unit::~Unit()
{
}

Canvas * Unit::setOnTable(AssetMeneger * assets, int pos)
{
	_position = pos;
	auto res = this->addGUI<UnitRepresentation>("UnitRepresentation", assets);
	auto URep = this->getGUI<UnitRepresentation>("UnitRepresentation");
	URep->setUnit(_prototype->_texture, assets);
	URep->setAttack(UnitRepresentation::ParameterColor::white, _attack);
	URep->setDefence(UnitRepresentation::ParameterColor::white, (_defense+_armor));
	URep->setHealth(UnitRepresentation::ParameterColor::white, _health);
	URep->setPosition(pos);
	return res;
}

}