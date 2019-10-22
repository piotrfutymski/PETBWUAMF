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
	void setOnTable(AssetMeneger * assets, int side, Canvas * parent);

	// GUI functions

	void setDescriptable();
	void setUnClicable();
	void setCHoosableAsOrderTarget();
	void setCHoosableAsUnitTarget();


	static void setFunctions(const std::map<std::string, std::function<void(Unit * u)>> & f);

private:

	static std::map<std::string, std::function<void(Unit * u)>> _functions;

	UnitPrototype * _prototype;

	bool _onTabe{ false };

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