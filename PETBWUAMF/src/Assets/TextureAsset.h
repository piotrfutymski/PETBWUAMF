#pragma once
#include "Asset.h"


class TextureAsset :public Asset
{
public:
	TextureAsset(const std::string & name) :Asset(name) {};
	~TextureAsset() {};

	// Inherited via Asset
	virtual void loadAsset(const nlohmann::json & assetFile) override;

public:

	sf::Texture _texture;

};

