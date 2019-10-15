#pragma once
#include "GameObject.h"
#include "../GUI/UnitRepresentation.h"

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
	int _defense;

	int _rangedAttack;
	int _chargeAttack;
	int _chargeDefense;

	std::string _description;

	bool _isInFight;
	int _position;


};

}