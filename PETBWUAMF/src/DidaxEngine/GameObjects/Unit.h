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

	void setPosition(int pos);
	void setOwner(int o);

	int getPositionOnBord(int side)const;

	Canvas * setOnTable(AssetMeneger * assets, int side);

private:

	UnitPrototype * _prototype;

	int _attack;
	int _defense;
	int _health;

	int _position{ 0 };
	int _owner{ 0 };

	UnitRepresentation::ParameterColor getParameterColorA();
	UnitRepresentation::ParameterColor getParameterColorD();
	UnitRepresentation::ParameterColor getParameterColorH();

};

}