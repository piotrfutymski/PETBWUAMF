#pragma once
#include "GameObject.h"

class Buff : public GameObject<BuffPrototype>
{
public:

	Buff(const std::string & name);
	~Buff();
private:
	int health;



};