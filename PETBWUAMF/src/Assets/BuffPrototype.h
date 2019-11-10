#pragma once
#include "Asset.h"

class BuffPrototype :public Asset
{

	BuffPrototype(const std::string & name) :Asset(name) {};
	~BuffPrototype() {};
	// Inherited via Asset
	virtual void loadAsset(const nlohmann::json & assetFile) override;
};