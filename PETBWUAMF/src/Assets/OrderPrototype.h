#pragma once
#include "Asset.h"

class OrderPrototype :public Asset
{
public:
	OrderPrototype(const std::string & name) :Asset(name) {};
	~OrderPrototype() {};

	// Inherited via Asset
	virtual void loadAsset(const nlohmann::json & assetFile) override;

public:

	std::string _description;

	std::string _texture;
	std::string _icon;

};
