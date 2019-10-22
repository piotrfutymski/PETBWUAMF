#include "Unit.h"


sf::Vector2i Unit::MAXPOS = { 16,10 };

Unit::Unit(const UnitPrototype * prototype)
{
}

Unit::Unit(const std::string & name)
{
}

const UnitPrototype * Unit::getPrototype()const
{
	return _prototype;
}

void Unit::setPosition(const sf::Vector2i & p)
{
	if (p.x < 0 || p.x >= MAXPOS.x || p.y < 0 || p.y >= MAXPOS.y)
		return;

	_position = p;
}

sf::Vector2i Unit::getPosition() const
{
	return _position;
}

void Unit::setOwner(int player)
{
	if (player == 0 || player == 1)
		_owner = player;
}

int Unit::getOwner() const
{
	return _owner;
}

void Unit::attack(Unit * enemy)
{
}
