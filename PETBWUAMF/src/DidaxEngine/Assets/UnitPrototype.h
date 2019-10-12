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
	int _defence;
	int _health;

	bool _distanceUnit;

	std::string _fraction;
	std::string _unitType;

	std::string _texture;

};

}