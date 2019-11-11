#pragma once
#include "GameObject.h"
#include "Move.h"

class Unit;


class Order : public GameObject<OrderPrototype>
{
public:
	Order(const std::string & name);
	~Order() {};

	enum class Location
	{
		InDeck, InHand, Used
	};

	void setOwner(int player);
	int getOwner()const;

	bool canBeUsed(Unit * u)const;

	OrderPrototype::Target getTargetType(int n)const;

	int getTargetsCount()const;

	bool canBeATarget(Unit *u, int n, const sf::Vector2i & pos)const;
	bool canBeATarget(Unit *u, int n, size_t unit)const;

	bool execute(Unit *u, const Move & m);

private:


	Location _location{ Location::InHand };

	int _owner{ 0 };

};