#pragma once
#include "Asset.h"


class GUIElementPrototype :public Asset
{
public:
	GUIElementPrototype(const std::string & name) :Asset(name) {};
	~GUIElementPrototype() {};

	// Inherited via Asset
	virtual void loadAsset(const nlohmann::json & assetFile) override;

public:

	std::map<std::string, std::string> _strings;
	std::map<std::string, float> _values;

};

