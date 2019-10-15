#include "Unit.h"

namespace Didax
{

int Unit::frontSize = 30;
int Unit::roundSize = 2;

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

	_isInFight = false;
}


Unit::~Unit()
{
}

void Unit::UnitFight(Unit *enemy)
{
	for (int round = 1; round <= roundSize; round++)
	{
		this->UnitRefill();
		enemy->UnitRefill();
		this->UnitRound(enemy);
	}

}
void Unit::UnitRound(Unit *enemy)
{
	int pairing = enemy->_attack + enemy->_defense / 2;
	int sumPairing = this->_attack + pairing;
	for (int unit = 1; unit <= this->front; unit++)
	{
		
	}
}
void Unit::UnitRefill()
{
	if (_health > frontSize)
	{
		front = frontSize;
		_health -= frontSize;
	}
	else
	{
		front = _health;
		_health = 0;
	}
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