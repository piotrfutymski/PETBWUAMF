#pragma once
#include "../Assets/AssetMeneger.h"
#include "Buff.h"

class Game;

class Unit
{
public:

	using Buffs_t = std::vector<std::unique_ptr<Buff>>;

	Unit(const std::string & name);

	const UnitPrototype * getPrototype()const;

	void setPosition(const sf::Vector2i & p);
	sf::Vector2i getPosition()const;

	void setOwner(int player);
	int getOwner()const;

	//attacking

	void normalAttack(Unit *enemy);
	void rangedAttack(Unit *enemy);
	// void chargeAttack(Unit *enemy);

	bool canMove(const sf::Vector2i & p)const;
	void move(const sf::Vector2i & p);

	int getProtection();


private:

	Game * _game;

	const UnitPrototype * _prototype;			
	// Unit statistic at this point

	int _attack;
	int _health;
	int _armor;
	int _defence;

	int _rangedAttack;
	int _chargeAttack;
	int _chargeDefence;

	int _move;

	float _formationSize {1};
	
	// Unit situation at this point

	bool _isInFight{ false };
	bool _isAlive{ true };

	sf::Vector2i _position{ 0,0 };
	int _owner{ 0 };

	//buffs

	Buffs_t _buffs;

	//statics

	static sf::Vector2i MAXPOS;
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