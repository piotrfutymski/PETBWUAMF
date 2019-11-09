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

	std::string _unitType;

	int _attack;
	int _health;
	int _armor;
	int _defence;

	int _rangedAttack;
	int _chargeAttack;
	int _chargeDefense;

	std::string _description;
	std::string _fraction;

	std::string _texture;

};