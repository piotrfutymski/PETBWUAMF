#pragma once
#include "GameObject.h"
#include "../GUI/UnitRepresentation.h"

namespace Didax
{

class Unit :
	public GameObject
{
public:
	Unit(UnitPrototype * prototype, AssetMeneger * assets);
	~Unit();

	void setPosition(int pos);
	void setOwner(int o);

	const UnitPrototype * getPrototype()const;

	int getPositionOnBord(int side)const;

	void setOnTable(AssetMeneger * assets, int side, Canvas * parent, const std::function<void(Unit * u)> & hi, const std::function<void(Unit *)> & ho);

	void setHoverInHoverOutEffects(const std::function<void(Unit * u)> & hi, const std::function<void(Unit *)> & ho);

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