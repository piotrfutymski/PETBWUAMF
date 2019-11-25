#pragma once
#include "Asset.h"

class BuffPrototype :public Asset
{
public:
	BuffPrototype(const std::string & name) :Asset(name) {};
	~BuffPrototype() {};
	// Inherited via Asset

	virtual void loadAsset(const nlohmann::json & assetFile) override;

	struct Action {
		int type;
		int value;
		bool add;
		bool onStart;
		bool onEnd;
	};

public:


	bool _instant;
	int _time;

	std::vector<Action> _actions;

};