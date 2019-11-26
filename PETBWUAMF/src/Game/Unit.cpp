#include "Unit.h"

int Unit::ROUND_SIZE = 1;
int Unit::FRONT_SIZE = 30;


Unit::Unit(const std::string & name, int owner)
	:GameObject<UnitPrototype>(name), _owner(owner)
{
	_attack = this->getPrototype()->_attack;
	_defence = this->getPrototype()->_defence;
	_armor = this->getPrototype()->_armor;
	_health = this->getPrototype()->_health;


	_rangedAttack = this->getPrototype()->_rangedAttack;
	_range = this->getPrototype()->_range;
	_chargeAttack = this->getPrototype()->_chargeAttack;
	_chargeDefence = this->getPrototype()->_chargeDefence;


	_move = this->getPrototype()->_move;
	_morale = this->getPrototype()->_morale;
	//
	_formationSize = this->getPrototype()->_formationSize;

	_flags = UFlag::None;
	if (_rangedAttack > 0)
		_flags = UFlag::Ranged;
}


void Unit::setPosition(const sf::Vector2i & p)
{
	_position = p;
}

sf::Vector2i Unit::getPosition() const
{
	return _position;
}

int Unit::getOwner() const
{
	return _owner;
}

bool Unit::isInFight() const
{
	return _isInFight;
}

bool Unit::isInFightWith(const Unit * u) const
{
	for (auto unit : _inFightAreaWith)
	{
		if (unit == u)
			return true;
	}
	return false;
}

const std::vector<Unit *>& Unit::getEnemyInFightWhith() const
{
	return _inFightAreaWith;
}

void Unit::setInFightWith(const std::vector<Unit *> & ids)
{
	_inFightAreaWith = ids;
	if (ids.size() > 0)
		_isInFight = true;
	else
		_isInFight = false;
}

void Unit::addInFightWith(Unit * u)
{
	if (std::find(_inFightAreaWith.begin(), _inFightAreaWith.end(), u) == _inFightAreaWith.end())
		_inFightAreaWith.push_back(u);
	_isInFight = true;
}

void Unit::removeInFightWith(Unit * u)
{
	if (auto it = std::find(_inFightAreaWith.begin(), _inFightAreaWith.end(), u); it != _inFightAreaWith.end())
		_inFightAreaWith.erase(it);

	if (_inFightAreaWith.empty())
		_isInFight = false;
}

void Unit::clearInFightWith()
{
	_inFightAreaWith.clear();
	_isInFight = false;
}

void Unit::upgradeParameter(const UParameter & p, float value)
{
	this->parameterFromEnum(p) += value;
}

int Unit::getMorale() const
{
	return _morale;
}

int Unit::getHealth() const
{
	return _health;
}

int Unit::getAttack() const
{
	return _attack;
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

int Unit::getChargeDefence() const
{
	return _chargeDefence;
}

int Unit::getChargeAttack() const
{
	return _chargeAttack;
}

int Unit::getRange() const
{
	return _range;
}

int Unit::getMove() const
{
	return _move;
}


bool Unit::hasFlag(UFlag f) const
{
	return (bool)(f & _flags);
}

void Unit::addFlag(UFlag f)
{
	_flags = _flags | f;
}

void Unit::removeFlag(UFlag f)
{
	_flags = _flags & ~f;
}

bool Unit::isDead() const
{
	if (_health <= 0)
		return true;
	return false;
}

float Unit::getDistanceTo(const Unit *enemy)const
{
	float x = enemy->_position.x - this->_position.x;
	float y = enemy->_position.y - this->_position.y;
	return std::sqrt(x * x + y * y);
}

Buff * Unit::addBuff(const std::string & name)
{
	auto buff = std::make_unique<Buff>(name, this->getID());

	if (!buff->isEffect())
		this->upgradeParameter(buff->getParameterToBoost(), buff->getValue());
	else
	{
		if (buff->getType() == BuffPrototype::BuffType::Bleeding)
			this->addFlag(UFlag::Bleeding);
		else if (buff->getType() == BuffPrototype::BuffType::UnableToAttack)
			this->addFlag(UFlag::UnableToAttack);
	}
	_buffs.push_back(std::move(buff));	
	return _buffs.back().get();
}

bool Unit::hasBuff(const std::string & name)
{
	for (auto& buff : _buffs)
	{
		if (buff->getPrototype()->getName() == name)
			return true;
	}
	return false;
}

std::vector<std::unique_ptr<Buff>>::iterator Unit::removeBuff(const std::string & name)
{
	auto buffIT = std::find_if(_buffs.begin(), _buffs.end(), [&name](const std::unique_ptr<Buff> & b) {
		return (b->getPrototype()->getName() == name);
	});

	if (buffIT == _buffs.end())
		return buffIT;

	return this->removeBuff( buffIT);
}

std::vector<std::unique_ptr<Buff>>::iterator Unit::removeBuff(std::vector<std::unique_ptr<Buff>>::iterator it)
{
	auto buff = it->get();

	if (!buff->isEffect())
		this->upgradeParameter(buff->getParameterToBoost(), -buff->getValue());
	else
	{
		if (buff->getType() == BuffPrototype::BuffType::Bleeding)
			this->removeFlag(UFlag::Bleeding);
		else if (buff->getType() == BuffPrototype::BuffType::UnableToAttack)
			this->removeFlag(UFlag::UnableToAttack);
	}
	return _buffs.erase(it);
}


void Unit::removeAllBuffs()
{
	while (!_buffs.empty())
	{
		this->removeBuff(_buffs.end()-1);
	}
}

MoveRes Unit::endTurn()
{
	auto res = this->playEffects();
	this->endbuffs();
	return std::move(res);
}

void Unit::normalAttack(Unit *enemy)
{
	for (int round = 1; round <= ROUND_SIZE; round++)
	{
		if (!this->sideFight(enemy))
			break;
		if (!enemy->sideFight(this))
			break;
	}
}

void Unit::rangedAttack(Unit *target)
{
	for (int round = 1; round <= ROUND_SIZE; round++)
	{
		target->casualties(this->rangedRound(target));
		if (!target->_isAlive)
			break;
	}
}

float Unit::attack(Unit * enemy)
{
	if (this->hasFlag(UFlag::Ranged))
	{
		if (rand() % 100 > this->chanceToHitRenged(enemy) * 100)
			return this->attack(enemy, _rangedAttack, enemy->_defence);
	}
	else
		return this->attack(enemy, _attack, enemy->_defence);
}

float Unit::ocassionalAttack(Unit * enemy)
{
	return this->attack(enemy, _attack / 2, enemy->_defence);
}

float Unit::chargeAttack(Unit * enemy)
{
	return this->attack(enemy, _chargeAttack, enemy->_chargeDefence);
}

float Unit::chanceToHitRenged(Unit * enemy)
{
	auto d = enemy->_defence;
	auto a = _attack;
	auto dist = this->getDistanceTo(enemy);
	return (1 - ((float)(d) / (float)(3 * a + 3 * d)))*(3 * _range - dist) / (float)(3 * _range);
}

void Unit::getSimpleInfo() const
{
	Logger::log(this->getPrototype()->getName() + " on pos (" + std::to_string(this->getPosition().x) + "," + std::to_string(this->getPosition().y) + ")");
	Logger::log("Attack: " + std::to_string(_attack) + " Defence: " + std::to_string(_defence) + " Health: " + std::to_string(_health));
	Logger::log("---------------------------------------------------------");
}

/// End of pulic functions ///

bool Unit::sideFight(Unit *enemy)
{
	this->casualties(enemy->normalRound(this));

	if (this->_isAlive)
		return 1;
	else
		return 0;
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

const int & Unit::parameterFromEnum(const UParameter & p)const
{
	if (p == UParameter::Morale)
		return _morale;
	else if (p == UParameter::Armor)
		return _armor;
	else if (p == UParameter::Attack)
		return _attack;
	else if (p == UParameter::ChargeAttack)
		return _chargeAttack;
	else if (p == UParameter::ChargeDeffence)
		return _chargeDefence;
	else if (p == UParameter::Defence)
		return _defence;
	else if (p == UParameter::Health)
		return _health;
	else if (p == UParameter::Move)
		return _move;
	else if (p == UParameter::Range)
		return _range;
	else if (p == UParameter::RangedAttack)
		return _rangedAttack;
}

int & Unit::parameterFromEnum(const UParameter & p)
{
	if (p == UParameter::Morale)
		return _morale;
	else if (p == UParameter::Armor)
		return _armor;
	else if (p == UParameter::Attack)
		return _attack;
	else if (p == UParameter::ChargeAttack)
		return _chargeAttack;
	else if (p == UParameter::ChargeDeffence)
		return _chargeDefence;
	else if (p == UParameter::Defence)
		return _defence;
	else if (p == UParameter::Health)
		return _health;
	else if (p == UParameter::Move)
		return _move;
	else if (p == UParameter::Range)
		return _range;
	else if (p == UParameter::RangedAttack)
		return _rangedAttack;
}

MoveRes Unit::playEffects()
{
	if (this->hasFlag(UFlag::Bleeding))
	{
		return this->bleeding();
	}
	return{};
}

void Unit::endbuffs()
{
	auto it = _buffs.begin();
	while (it != _buffs.end())
	{
		if (it->get()->endTurn())
		{
			it = this->removeBuff(it);
		}
		else
			++it;
	}
}


MoveRes Unit::bleeding()
{
	MoveRes res{};

	for (auto & buff : _buffs)
	{
		if (buff->getType() == BuffPrototype::BuffType::Bleeding)
		{
			MoveRes::MoveEvent e;
			this->_health -= buff->getValue();

			e.dmg = buff->getValue();
			e.type = MoveRes::EventType::DMGTaken;
			e.unit = this->getID();
			e.time = 27;
			res.events.push_back(std::move(e));
		}
	}

	return res;
}

float Unit::attack(Unit * enemy, float attack, float defence)
{
	auto base = (4.f / 10.f);
	auto add = (6.f / 10.f)*(attack - defence) / (attack + defence);

	float mini, maxi;

	if (add > 0)
	{
		base += add;
		mini = base;
		maxi = 1;
	}
	else
	{
		mini = base;
		maxi = 1 + add;
	}

	auto nonconst = (rand() % 100 * (maxi - mini)) / 100;

	auto dmg = (base + nonconst) * _attack;

	if (dmg > enemy->_armor)
		dmg -= enemy->_armor / 2;
	else
		dmg /= 2;

	dmg /= 3;

	enemy->_health -= dmg;
	return dmg;
}





