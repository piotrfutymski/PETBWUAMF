#pragma once
#include "Asset.h"


class UnitPrototype : public Asset
{
public:
	UnitPrototype(const std::string & name) :Asset(name) {};
	~UnitPrototype() {};

	// Inherited via Asset
	virtual void loadAsset(const nlohmann::json & assetFile) override;

public:

	int _attack;
	int _health;
	int _armor;
	int _defence;

	int _rangedAttack;
	int _range;
	int _chargeAttack;
	int _chargeDefence;

	int _move;
	int _morale;
	float _formationSize;

	std::string _description;
	std::string _faction;
	std::string _unitType;

	std::string _texture;

};