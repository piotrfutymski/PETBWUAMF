#pragma once
#include "GameObject.h"


class Buff : public GameObject<BuffPrototype>
{
public:

	enum class BuffType{
		 None, Morale, Health, Attack, Armor, Defence, RangedAttack, ChargeDeffence, ChargeAttack, Range, Move,
		 Bleeding
	};

	struct BuffAction {
		BuffType type;
		float value;
		bool add;							// add or remove
		bool onStart;
		bool onEnd;
	};

	Buff(const std::string & name, size_t u);
	~Buff();

	bool isGood()const;
	bool isInstant()const;
	bool endTurn();								// true = destroy me
	bool hasType(BuffType type)const;

	std::vector<BuffAction> & getActions();
	const std::vector<BuffAction> & getActions()const;
	BuffAction & getActionOfType(BuffType t);
	const BuffAction & getActionOfType(BuffType t)const;


private:
	
	size_t _owner;

	bool _isInstant;
	int _time;

	std::vector<BuffAction> _actions;


};