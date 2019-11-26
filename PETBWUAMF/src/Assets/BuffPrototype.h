#pragma once
#include "Asset.h"
#include "../Game/Move.h"

class BuffPrototype :public Asset
{
public:

	enum class BuffType {
		ParameterBoost, UnableToAttack, Bleeding
	};

	BuffPrototype(const std::string & name) :Asset(name) {};
	~BuffPrototype() {};
	// Inherited via Asset

	virtual void loadAsset(const nlohmann::json & assetFile) override;
	bool onTurnEnd(float & v)const;

public:

	BuffType _type;
	UParameter _parameterToBoost;
	int _time;
	float _value;
	bool _isGood;

};