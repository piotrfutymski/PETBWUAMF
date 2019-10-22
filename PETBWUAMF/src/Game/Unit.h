#pragma once
#include "../Assets/AssetMeneger.h"

class Unit
{
public:

	Unit(const UnitPrototype * prototype);
	Unit(const std::string & name);

	const UnitPrototype * getPrototype()const;

	void setPosition(const sf::Vector2i & p);
	sf::Vector2i getPosition()const;

	void setOwner(int player);
	int getOwner()const;

	void attack(Unit *enemy);


private:

	const UnitPrototype * _prototype;			

	// Unit statistic at this point

	int _attack;
	int _health;
	int _armor;
	int _defence;
	int _rangedAttack;
	int _chargeAttack;
	int _chargeDefence;
	int _front;
	
	// Unit situation at this point

	bool _isInFight{ false };
	bool _isAlive{ true };

	sf::Vector2i _position{ 0,0 };
	int _owner{ 0 };

	//statics

	static sf::Vector2i MAXPOS;


};