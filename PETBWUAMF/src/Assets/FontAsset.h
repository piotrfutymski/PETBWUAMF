#pragma once
#include "Asset.h"



class FontAsset :public Asset
{
public:
	FontAsset(const std::string & name) :Asset(name) {};
	~FontAsset() {};

	// Inherited via Asset
	virtual void loadAsset(const nlohmann::json & assetFile) override; /* Loads data from asset file*/

public:

	sf::Font _font;

};
