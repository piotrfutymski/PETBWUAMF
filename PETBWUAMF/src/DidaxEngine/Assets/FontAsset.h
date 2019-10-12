#pragma once
#include "Asset.h"


namespace Didax
{

class FontAsset :public Asset
{
public:
	FontAsset(const std::string & name) :Asset(name) {};
	~FontAsset() {};

	// Inherited via Asset
	virtual void loadAsset(const nlohmann::json & assetFile) override;

public:

	sf::Font _font;

};

}