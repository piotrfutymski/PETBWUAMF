#pragma once
#include "GameObject.h"
#include "Move.h"

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

	int getOwner()const;
	int getCost()const;
	int getRestUses()const;
	int getTargetsCount()const;
	Location getLocation()const;

	void changeLocation();

	MoveRes execute(Game * game, const Move & m);
	bool canBeUsed(const std::string &  unitName, const std::string & unitType);
	float getChances(Game * game, const Move & m);

private:

	Location _location{ Location::InHand };

	int _owner;
	int _useNum;


};