#pragma once
#include "GameObject.h"


class Buff : public GameObject<BuffPrototype>
{
public:

	enum class BuffType{
		 Morale, Health, Attack, Armor, Defence, RangedAttack, ChargeDeffence, ChargeAttack, Range, Move,
		 Bleeding
	};

	struct BuffAction {
		BuffType type;
		float value;
	};

	Buff(const std::string & name, size_t u);
	~Buff();

	bool isGood()const;
	bool isInstant()const;
	bool endTurn();								// true = destroy me
	bool onRemove();							

	const std::vector<BuffAction> & getActions()const;


private:
	
	size_t _owner;

	bool _isInstant;
	int _time;

	std::vector<BuffAction> _actions;


};