#pragma once
#include "GameObject.h"

class Buff : public GameObject<BuffPrototype>
{
public:

	enum class BuffType{

	};

	Buff(const std::string & name, size_t u);
	~Buff();

	bool isGood()const;
	bool isInstant()const;


private:
	
	size_t owner;

	bool isInstant;
	bool isToNextTurn;


};