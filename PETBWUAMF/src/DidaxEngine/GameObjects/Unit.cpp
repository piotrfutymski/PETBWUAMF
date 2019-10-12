#include "Unit.h"

namespace Didax
{

Unit::Unit(Engine * eng, UnitPrototype * prototype):GameObject(eng)
{
	_prototype = prototype;
	_attack = _prototype->_attack;
	_defence = _prototype->_defence;
	_health = _prototype->_health;

	_distanceUnit = _prototype->_distanceUnit;

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
	URep->setDefence(UnitRepresentation::ParameterColor::white, _defence);
	URep->setHealth(UnitRepresentation::ParameterColor::white, _health);
	URep->setPosition(pos);
	URep->setReadyToChoose(UnitRepresentation::BorderColor::yellow);
	return res;
}

}