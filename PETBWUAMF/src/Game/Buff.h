#pragma once
#include "GameObject.h"
#include "Move.h"


class Buff : public GameObject<BuffPrototype>
{
public:

	Buff(const std::string & name, size_t u);
	~Buff();

	bool isGood()const;
	bool isInstant()const;
	bool isEffect()const;
	float getValue()const;
	void setValue(float v);
	int getTime()const;
	UParameter getParameterToBoost()const;
	BuffPrototype::BuffType getType()const;


	bool endTurn();								// true = destroy me

private:
	
	size_t _owner;
	int _time;
	float _value;

};