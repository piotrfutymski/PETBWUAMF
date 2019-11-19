#pragma once
#include "Asset.h"

class Buff;

class BuffPrototype :public Asset
{
public:
	BuffPrototype(const std::string & name) :Asset(name) {};
	~BuffPrototype() {};
	// Inherited via Asset

	virtual void loadAsset(const nlohmann::json & assetFile) override;

public:


	bool _forAlways;

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
	float _formationSize{ 0 };

};