#include "Unit.h"

namespace Didax
{

int Unit::frontSize = 30;
int Unit::roundSize = 2;

Unit::Unit(Engine * eng, UnitPrototype * prototype):GameObject(eng)
{
	_prototype = prototype;
	_attack = _prototype->_attack;
	_defence = _prototype->_defence;
	_armor = _prototype->_armor;
	_health = _prototype->_health;

	_rangedAttack = _prototype->_rangedAttack;
	_chargeAttack = _prototype->_chargeAttack;
	_chargeDefence = _prototype->_chargeDefence;

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
	int pairing = (enemy->_attack + enemy->_defence) / 2;
	if (!enemy->_isInFight) pairing = +enemy->_chargeDefence;

	int fullDefence = enemy->_defence + enemy->_armor;
	if (!enemy->_isInFight) fullDefence = +enemy->_chargeDefence;

	int sumAttack = this->_attack;
	if (!this->_isInFight) sumAttack += sumAttack + this->_chargeAttack;

	int sumPairing = sumAttack + pairing;
	int sumDefence = sumAttack + fullDefence;

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
	URep->setDefence(UnitRepresentation::ParameterColor::white, (_defence+_armor));
	URep->setHealth(UnitRepresentation::ParameterColor::white, _health);
	URep->setPosition(pos);
	return res;
}

}