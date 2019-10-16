#pragma once
#include "Asset.h"

namespace Didax
{

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
	int _defense;

	std::string _description;
	std::string _faction;
	std::string _unitType;

	std::string _texture;

};

}
/*	std::string tag;
	std::string name;
	std::string description;
	std::string faction;
	int price;
	int attack;
	int chargeAttack;
	int chargeDefense;
	int armor;
	int shield;
	int defense;
	int rangeAttack;
	int rangeDistance;
	int rangeAccuracy;
	int quantity;
	int size;
	std::vector<std::string> skills;*/