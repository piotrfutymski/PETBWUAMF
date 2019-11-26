#pragma once
#include "GameObject.h"
#include "Buff.h"
#include "Move.h"


class Unit : public GameObject<UnitPrototype>
{
public:

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

	void upgradeParameter(const UParameter & p, float value);

	int getMorale()const;
	int getHealth()const;
	int getAttack()const;
	int getArmor() const;
	int getDefence() const;
	int getRangedAttack() const;
	int getChargeDefence() const;
	int getChargeAttack() const;
	int getRange() const;
	int getMove()const;

	// flags
	
	bool hasFlag(UFlag f)const;
	void addFlag(UFlag f);
	void removeFlag(UFlag f);

	// functions

	bool isDead()const;
	float getDistanceTo(const Unit *enemy)const;

	Buff * addBuff(const std::string & name);
	bool hasBuff(const std::string & name);
	std::vector<std::unique_ptr<Buff>>::iterator removeBuff(const std::string & name);
	std::vector<std::unique_ptr<Buff>>::iterator removeBuff(std::vector<std::unique_ptr<Buff>>::iterator it);
	void removeAllBuffs();
	MoveRes endTurn();

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

	int _attack;
	int _health;
	int _armor;
	int _defence;
	int _rangedAttack;
	int _range;
	int _chargeAttack;
	int _chargeDefence;
	int _move;
	int _morale;

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
	const int& parameterFromEnum(const UParameter & p)const;
	int& parameterFromEnum(const UParameter & p);

	MoveRes playEffects();
	void endbuffs();

	MoveRes bleeding();
	float attack(Unit * enemy, float attack, float defence);

public:

	
};

inline UFlag operator| (UFlag a, UFlag b)
{
	return static_cast<UFlag>(static_cast<int>(a) | static_cast<int>(b));
}

inline UFlag operator& (UFlag a, UFlag b)
{
	return static_cast<UFlag>(static_cast<int>(a) & static_cast<int>(b));
}

inline UFlag operator~ (UFlag a)
{
	return static_cast<UFlag>(static_cast<int>(~a));
}