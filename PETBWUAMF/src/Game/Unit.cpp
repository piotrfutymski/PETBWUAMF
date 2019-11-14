#include "Unit.h"

//sf::Vector2i Unit::MAXPOS = { 15,9 };
int Unit::ROUND_SIZE = 1;
int Unit::FRONT_SIZE = 30;


Unit::Unit(const std::string & name)
	:GameObject<UnitPrototype>(name)
{
	_attack = this->getPrototype()->_attack;
	_defence = this->getPrototype()->_defence;
	_armor = this->getPrototype()->_armor;
	_health = this->getPrototype()->_health;


	_rangedAttack = this->getPrototype()->_rangedAttack;
	_rangedRange = this->getPrototype()->_rangedRange;
	_chargeAttack = this->getPrototype()->_chargeAttack;
	_chargeDefence = this->getPrototype()->_chargeDefence;


	_move = this->getPrototype()->_move;
	_morale = this->getPrototype()->_morale;
	_formationSize = this->getPrototype()->_formationSize;
}


void Unit::setPosition(const sf::Vector2i & p)
{
	if (p.x < 0 || p.x > Map::MAP_WIDTH || p.y < 0 || p.y > Map::MAP_HEIGHT)
		return;

	_position = p;
}

sf::Vector2i Unit::getPosition() const
{
	return _position;
}
bool Unit::isInFight() const
{
	return _isInFight;
}


bool Unit::isInFightWith(size_t id)
{
	for (auto u : _inFightAreaWith)
	{
		if (u == id)
			return true;
	}
	return false;
}

void Unit::setInFightWith(const std::vector<size_t> & ids)
{
	_inFightAreaWith = ids;
	if (ids.size() > 0)
		_isInFight = true;
	else
		_isInFight = false;
}

void Unit::addInFightWith(size_t id)
{
	if (_inFightAreaWith.size() == 0)
		_isInFight = true;
	if (auto it = std::find(_inFightAreaWith.begin(), _inFightAreaWith.end(), id); it == _inFightAreaWith.end())
	{
		_inFightAreaWith.push_back(id);
	}
}

void Unit::removeInFightWith(size_t id)
{
	if (auto it = std::find(_inFightAreaWith.begin(), _inFightAreaWith.end(), id); it != _inFightAreaWith.end())
	{
		_inFightAreaWith.erase(it);
	}
	if (_inFightAreaWith.size() == 0)
		_isInFight = false;
	
}

const std::vector<size_t>& Unit::getEnemyInFightWhith() const
{
	return _inFightAreaWith;
}

bool Unit::isRanged() const
{
	if (this->getPrototype()->_rangedAttack > 0)
		return true;
	return false;
}

int Unit::getProtection() const
{
	return _armor + _defence;
}
int Unit::getHealth() const
{
	return _health;
}
int Unit::getMorale() const
{
	return _morale;
}
int Unit::getAttack() const
{
	return _attack;
}
int Unit::getOwner() const
{
	return _owner;
}
void Unit::setOwner(int player)
{
	if (player == 0 || player == 1)
		_owner = player;
}
int Unit::getMove()const
{
	return _move;
}
int Unit::getArmor() const
{
	return _armor;
}
int Unit::getDefence() const
{
	return _defence;
}
int Unit::getRangedAttack() const
{
	return _rangedAttack;
}
int Unit::getRangedRange() const
{
	return _rangedRange;
}
int Unit::getChargeDefence() const
{
	return _chargeDefence;
}
int Unit::getChargeAttack() const
{
	return _chargeAttack;
}

void Unit::getSimpleInfo() const
{
	Logger::log(this->getPrototype()->getName() + " on pos (" + std::to_string(this->getPosition().x) + "," + std::to_string(this->getPosition().y) + ")");
	Logger::log("Attack: " + std::to_string(_attack) + " Protection: " + std::to_string(this->getProtection()) + " Health: " + std::to_string(_health));
	Logger::log("---------------------------------------------------------");
}

float Unit::getDistanceTo(const Unit *enemy)const
{
	float x = enemy->_position.x - this->_position.x;
	float y = enemy->_position.y - this->_position.y;
	return std::sqrt(x * x + y * y);
}

void Unit::normalAttack(Unit *enemy)
{
	//
	Logger::log("-------------------Attack in progress--------------------");
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
	Logger::log("---------------------Attack finished---------------------");
	Logger::log("----------------Press something to continue--------------");
	std::getchar();
	//Is fight prawdopodobnie b�dzie ustawiane gdy jednostka dotknie innej
	/*this->_isInFight = true;
	enemy->_isInFight = true;
	return;*/

}
void Unit::rangedAttack(Unit *target)
{
	Logger::log("---------------Ranged Attack in progress-----------------");
	for (int round = 1; round <= ROUND_SIZE; round++)
	{

		target->casualties(this->rangedRound(target));
		if (!target->_isAlive)
		{
			Logger::log("Defending unit destroyed.");
			break;
		}
	}
	Logger::log("----------------Ranged Attack finished-------------------");
	Logger::log("----------------Press something to continue--------------");
	std::getchar();
	return;
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

bool Unit::canMove(const sf::Vector2i & p) const
{
	return false;
}

void Unit::move(const sf::Vector2i & p)
{
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