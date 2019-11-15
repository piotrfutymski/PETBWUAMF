#pragma once
#include "GameObject.h"
#include "Buff.h"
#include "Map.h"

class Unit : public GameObject<UnitPrototype>
{
public:

	enum class UParameter
	{
		Morale, Health, Attack, Protection, Armor, Defence, RangedAttack, ChargeDeffence, ChargeAttack, Range, Move
	};

	enum class UFlag : unsigned long long
	{
		None = 0,
		Ranged = 1,
		UnableToAttack = 2,
		UnableToMove = 4,

	};


	Unit(const std::string & name);
	~Unit() {};

	//getters and setters

	void setPosition(const sf::Vector2i & p);
	sf::Vector2i getPosition()const;

	void setOwner(int player);
	int getOwner()const;

	//Fights

	bool isInFight()const;
	bool isInFightWith(size_t id);
	void setInFightWith(const std::vector<size_t> & ids);
	void addInFightWith(size_t id);
	void removeInFightWith(size_t id);
	const std::vector<size_t> & getEnemyInFightWhith()const;

	//Parameters

	int getMorale()const;
	int getHealth()const;
	int getAttack()const;
	int getProtection()const;
	int getArmor() const;
	int getDefence() const;
	int getRangedAttack() const;
	int getChargeDefence() const;
	int getChargeAttack() const;
	int getRangedRange() const;
	int getMove()const;

	int getParameter(UParameter p)const;

	// flags
	
	bool hasFlag(UFlag f)const;

	// help functions

	float getDistanceTo(const Unit *enemy)const;

	//attacking

	void normalAttack(Unit *enemy);
	void rangedAttack(Unit *enemy);

	// LOG

	void getSimpleInfo() const;

private:

	// Unit statistic at this point

	int _attack;
	int _health;
	int _armor;
	int _defence;
	int _rangedAttack;
	int _rangedRange;
	int _chargeAttack;
	int _chargeDefence;
	int _move;
	int _morale;
	float _formationSize;

	// Flags

	UFlag _flags;
	
	// Unit situation at this point

	bool _isInFight{ false };
	bool _isAlive{ true };
	std::vector<size_t> _inFightAreaWith;
	sf::Vector2i _position{ 0,0 };
	int _owner{ 0 };

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