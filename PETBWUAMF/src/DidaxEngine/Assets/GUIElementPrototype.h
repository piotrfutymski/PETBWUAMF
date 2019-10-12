#pragma once
#include "Asset.h"

namespace Didax
{

class GUIElementPrototype :public Asset
{
public:
	GUIElementPrototype(const std::string & name) :Asset(name) {};
	~GUIElementPrototype() {};

	// Inherited via Asset
	virtual void loadAsset(const nlohmann::json & assetFile) override;

public:

	std::map<std::string, std::string> _fileNames;
	std::map<std::string, float> _values;

};

}