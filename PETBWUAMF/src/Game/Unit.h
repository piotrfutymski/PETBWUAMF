#pragma once
#include "GameObject.h"
#include "Buff.h"


class Unit : public GameObject<UnitPrototype>
{
public:

	enum class UParameter
	{
		Morale, Health, Attack, Armor, Defence, RangedAttack, ChargeDeffence, ChargeAttack, Range, Move, BleedingModificator
	};

	enum class UFlag : unsigned long long
	{
		None = 0,
		Ranged = 1,
		UnableToAttack = 2,
		UnableToMove = 4,
		Bleeding = 8,
		Fleeing = 16,
		Overheald = 32

	};


	Unit(const std::string & name, int owner);
	~Unit() {};

	//getters and setters

	void setPosition(const sf::Vector2i & p);
	sf::Vector2i getPosition()const;

	int getOwner()const;

	//Fights

	bool isInFight()const;
	bool isInFightWith(const Unit * u)const;
	const std::vector<Unit *> & getEnemyInFightWhith()const;


	void setInFightWith(const std::vector<Unit *> & ids);
	void addInFightWith(Unit * u);
	void removeInFightWith(Unit * u);
	void clearInFightWith();


	//Parameters

	const float & operator[](const UParameter & p)const;
	float & operator[](const UParameter & p);

	void upgradeParameter(const UParameter & p, float value);

	// flags
	
	bool hasFlag(UFlag f)const;

	// functions

	bool isDead()const;
	float getDistanceTo(const Unit *enemy)const;

	void addBleeding(float bl);

	void addBuff(const std::string & name);
	void removeBuff(const std::string & name);
	void removeAllBuffs();
	void endTurn();

	//attacking

	void normalAttack(Unit *enemy);
	void rangedAttack(Unit *enemy);

	//

	float attack(Unit * enemy);
	float ocassionalAttack(Unit * enemy);
	float chargeAttack(Unit *enemy);
	float chanceToHitRenged(Unit *enemy);

	// LOG

	void getSimpleInfo() const;

private:

	// Unit statistic at this point

	float _attack;
	float _health;
	float _armor;
	float _defence;
	float _rangedAttack;
	float _range;
	float _chargeAttack;
	float _chargeDefence;
	float _move;
	float _morale;
	float _bleedingModificator;
	//

	//
	float _formationSize;

	// Flags

	UFlag _flags;
	
	// Unit situation at this point

	bool _isInFight{ false };

	bool _isAlive{ true };

	std::vector<Unit *> _inFightAreaWith;

	std::vector<std::unique_ptr<Buff>> _buffs;

	sf::Vector2i _position{ 0,0 };

	int _owner{ 0 };

	float _bleeding;

	//statics

	static int FRONT_SIZE;
	static int ROUND_SIZE;

private:

	bool sideFight(Unit *enemy);
	void casualties(int casualties);
	int normalRound(Unit *enemy);
	int refill();
	std::pair<int, int> normalChance(Unit *enemy);
	int rangedChance(Unit *target);
	int rangedRound(Unit *target);
	const float& parameterFromEnum(const UParameter & p)const;
	float& parameterFromEnum(const UParameter & p);

	void bleeding();
	float attack(Unit * enemy, float attack, float defence);

public:

	
};

inline Unit::UFlag operator| (Unit::UFlag a, Unit::UFlag b)
{
	return static_cast<Unit::UFlag>(static_cast<int>(a) | static_cast<int>(b));
}

inline Unit::UFlag operator& (Unit::UFlag a, Unit::UFlag b)
{
	return static_cast<Unit::UFlag>(static_cast<int>(a) & static_cast<int>(b));
}

inline Unit::UFlag operator~ (Unit::UFlag a)
{
	return static_cast<Unit::UFlag>(static_cast<int>(~a));
}