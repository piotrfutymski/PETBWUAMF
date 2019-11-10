#include "Unit.h"

sf::Vector2i Unit::MAXPOS = { 15,9 };
int Unit::ROUND_SIZE = 2;
int Unit::FRONT_SIZE = 30;


Unit::Unit(const std::string & name)
	:GameObject<UnitPrototype>(name)
{

	_attack = this->getPrototype()->_attack;
	_defence = this->getPrototype()->_defence;
	_armor = this->getPrototype()->_armor;
	_health = this->getPrototype()->_health;

	_rangedAttack = this->getPrototype()->_rangedAttack;
	_chargeAttack = this->getPrototype()->_chargeAttack;
	_chargeDefence = this->getPrototype()->_chargeDefence;

	_move = this->getPrototype()->_move;
	_morale = this->getPrototype()->_morale;
}


void Unit::setPosition(const sf::Vector2i & p)
{
	if (p.x < 0 || p.x > MAXPOS.x || p.y < 0 || p.y > MAXPOS.y)
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

bool Unit::isRanged() const
{
	if (this->getPrototype()->_rangedAttack > 0)
		return true;
	return false;
}

bool Unit::isInFight() const
{
	return _isInFight;
}

bool Unit::isInFightWith(size_t id)
{
	for (auto u: _inFightAreaWith)
	{
		if (u == id)
			return true;
	}
	return false;
}

int Unit::getMorale() const
{
	return _morale;
}

int Unit::getMove()
{
	return _move;
}

void Unit::normalAttack(Unit *enemy)
{
	for (int round = 1; round <= ROUND_SIZE; round++)
	{
		if (!this->sideFight(enemy))
		{
			Logger::log("Attacking unit destroyed.");
			break;
		}
		if (!enemy->sideFight(this))
		{
			Logger::log("Defending unit destroyed.");
			break;
		}
	}

	//Is fight prawdopodobnie bêdzie ustawiane gdy jednostka dotknie innej
	/*this->_isInFight = true;
	enemy->_isInFight = true;
	return;*/

}

bool Unit::sideFight(Unit *enemy)
{
	this->casualties(enemy->normalRound(this));

	if (this->_isAlive)
		return 1;
	else
		return 0;
}

int Unit::normalRound(Unit *enemy)
{
	int front = this->refill();
	int killcount = 0;
	bool temp = false;
	std::pair<int, int> chances = normalChance(enemy);
	Logger::log(this->getPrototype()->getName() + " has chances: " +
		std::to_string(chances.first / 10) + "% " + std::to_string(chances.second / 10) + "% " +
		std::to_string(chances.first*chances.second / 10000) + "%");
	for (int unit = 1; unit <= front; unit++)
	{
		if ((rand() % 1000 + 1) < chances.first)
		{
			if (temp) Logger::log("Atack has not been parred, chance was " +
				std::to_string(chances.first / 10) + "%");
			if ((rand() % 1000 + 1) < chances.first)
			{
				if (temp)	Logger::log("Atack has not been defended, chance was " +
					std::to_string(chances.second / 10) + "%");
				killcount++;
			}
			else
				if (temp)	Logger::log("Atack has been defended, chance was " +
					std::to_string(chances.second / 10) + "%");
		}
		else
			if (temp) Logger::log("Atack has been parred, chance was " +
				std::to_string(chances.first / 10) + "%");

	}
	return killcount;
}


void Unit::casualties(int casualties)
{
	this->_health -= casualties;
	Logger::log(this->getPrototype()->getName() + " has suffered " + std::to_string(casualties) + " casualties");
	if (this->_health <= 0)
	{
		this->_health = 0;
		this->_isAlive = false;
	}
}

int Unit::refill()
{
	if (this->_health < FRONT_SIZE / this->_formationSize)
		return this->_health;
	else
		return FRONT_SIZE / this->_formationSize;
}

std::pair<int, int> Unit::normalChance(Unit *enemy)
{
	int pairing = (enemy->_attack + enemy->_defence) / 2;
	if (!enemy->_isInFight) pairing += enemy->_chargeDefence;

	int fullDefence = enemy->_defence + enemy->_armor;
	if (!enemy->_isInFight) fullDefence += enemy->_chargeDefence;

	float sumAttack = this->_attack;
	if (!this->_isInFight) sumAttack += this->_chargeAttack;

	int sumPairing = sumAttack + pairing;
	int sumDefence = sumAttack + fullDefence;

	int chance = (sumAttack / sumPairing) * 1000;
	int chance2 = (sumAttack / sumDefence) * 1000;

	return std::pair<int, int>(chance, chance2);

}


int Unit::rangedChance(Unit *target)
{
	int fullDefence = target->_armor * 2;
	if (!target->_isInFight) fullDefence += target->_chargeDefence / 2;

	float sumAttack = this->_rangedAttack;

	int sumDefence = sumAttack + fullDefence;

	int chance = (sumAttack / sumDefence) * 1000;

	return chance;
}


void Unit::rangedAttack(Unit *target)
{
	for (int round = 1; round <= ROUND_SIZE; round++)
	{

		target->casualties(this->rangedRound(target));
		if (!target->_isAlive)
		{
			Logger::log("Defending unit destroyed.");
			break;
		}
	}
	return;
}

bool Unit::canMove(const sf::Vector2i & p) const
{
	return false;
}

void Unit::move(const sf::Vector2i & p)
{
}

int Unit::getProtection() const
{
	return 0;
}


int Unit::rangedRound(Unit *target)
{
	int killcount = 0;
	bool temp = false;
	int chance = rangedChance(target);
	Logger::log(this->getPrototype()->getName() + " has chance: " +
		std::to_string(chance / 10) + "%");
	for (int unit = 1; unit <= this->_health / 2; unit++)
	{

		if ((rand() % 1000 + 1) < chance)
		{
			if (temp)	Logger::log("Atack has not been defended, chance was " +
				std::to_string(chance / 10) + "%");
			killcount++;
		}
		else
			if (temp)	Logger::log("Atack has been defended, chance was " +
				std::to_string(chance / 10) + "%");
	}
	return killcount;
}