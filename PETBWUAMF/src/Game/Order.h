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

	OrderPrototype::TargetType getTargetType(int n)const;

	int getTargetsCount()const;

	std::vector<OrderPrototype::Target> getProperTargets(Unit *u, int n)const;

	bool execute(Unit *u, const Move & m);

private:


	Location _location{ Location::InHand };

	int _owner{ 0 };

};