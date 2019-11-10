#pragma once
#include "GameObject.h"
#include "Buff.h"

class Unit : public GameObject<UnitPrototype>
{
public:

	static sf::Vector2i MAXPOS;

	using Buffs_t = std::vector<Buff*>;

	Unit(const std::string & name);
	~Unit() {};

	void setPosition(const sf::Vector2i & p);
	sf::Vector2i getPosition()const;

	void setOwner(int player);
	int getOwner()const;

	int getMorale()const;
	int getHealth()const;
	int getAttack()const;
	int getProtection()const;
	int getMove() const;
	int getArmor() const;
	int getDefence() const;
	int getRangedAttack() const;
	int getChargeDefence() const;
	int getChargeAttack() const;

	//attacking

	void normalAttack(Unit *enemy);
	void rangedAttack(Unit *enemy);
	// void chargeAttack(Unit *enemy);

	bool canMove(const sf::Vector2i & p)const;
	void move(const sf::Vector2i & p);



private:

	// Unit statistic at this point

	int _attack;
	int _health;
	int _armor;
	int _defence;

	int _rangedAttack;
	int _chargeAttack;
	int _chargeDefence;

	int _move;
	int _morale;

	float _formationSize {1};
	
	// Unit situation at this point

	bool _isInFight{ false };
	bool _isAlive{ true };

	sf::Vector2i _position{ 0,0 };
	int _owner{ 0 };

	//buffs

	Buffs_t _buffs;

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

};