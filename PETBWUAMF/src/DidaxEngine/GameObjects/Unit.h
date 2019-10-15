#pragma once
#include "GameObject.h"
#include "../GUI/UnitRepresentation.h"
#include <time.h>

namespace Didax
{

class Unit :
	public GameObject
{
public:
	Unit(Engine * eng, UnitPrototype * prototype);
	~Unit();

	Canvas * setOnTable(AssetMeneger * assets, int pos);

private:

	UnitPrototype * _prototype;

	int _attack;
	int _health;
	int _armor;
	int _defence;

	int _rangedAttack;
	int _chargeAttack;
	int _chargeDefence;

	std::string _description;

	bool _isInFight;
	int _position;
	int front;

	void UnitFight(Unit *enemy);
	void UnitRound(Unit *enemy);
	void UnitRefill();

	static int roundSize;
	static int frontSize;
};

}