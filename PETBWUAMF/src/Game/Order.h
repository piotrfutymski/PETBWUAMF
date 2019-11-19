#pragma once
#include "GameObject.h"
#include "Move.h"
#include "MoveRes.h"

class Unit;


class Order : public GameObject<OrderPrototype>
{
public:
	Order(const std::string & name, int owner);
	~Order() {};

	enum class Location
	{
		InDeck, InHand
	};

	enum class Target
	{
		size_t
	};

	int getOwner()const;
	bool canBeUsed(Unit * u)const;

	int getTargetsCount()const;

	MoveRes execute(Unit *u, const Move & m);

private:

	Location _location{ Location::InHand };

	int _owner{ 0 };

	int _cost;
	int _useNum;


};