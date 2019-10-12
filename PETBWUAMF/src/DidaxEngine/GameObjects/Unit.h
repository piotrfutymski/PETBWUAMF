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
	int _defence;
	int _health;
	bool _distanceUnit;

	int _position;


};

}