#pragma once
#include "GameObject.h"

class Buff : public GameObject<BuffPrototype>
{
public:

	Buff(const std::string & name, size_t u);
	~Buff();

	size_t getOwner()const;
	int getRestTime() const;
	bool onTurnEnd();

	void setBoostValue(float v);
	float getBoostValue()const;

private:
	
	size_t _unit;
	int _restTime;
	float _boostValue;


};