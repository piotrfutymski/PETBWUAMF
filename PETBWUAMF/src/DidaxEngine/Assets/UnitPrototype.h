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



};

}