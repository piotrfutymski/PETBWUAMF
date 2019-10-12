#pragma once
#include "Asset.h"

namespace Didax
{

class BoardPrototype :public Asset
{
public:
	BoardPrototype(const std::string & name):Asset(name) {};
	~BoardPrototype() {};

	// Inherited via Asset
	virtual void loadAsset(const nlohmann::json & assetFile) override;


public:

	std::string _backgroundTexture;
	sf::Vector2f _mainGuiPos;
	std::string _mainGuiName;
	sf::Vector2f _sideGuiPos;
	std::string _sideGuiName;

};

}