#pragma once
#include <map>
#include "nlohmann/json.hpp"
#include "SFML/Graphics.hpp"
#include <fstream>
#include <iostream>
#include "Asset.h"
#include "../Utility/Logger.h"
#include "TextureAsset.h"
#include "GUIElementPrototype.h"
#include "FontAsset.h"
#include "OrderPrototype.h"
#include "UnitPrototype.h"

namespace Didax
{

class AssetMeneger
{
public:

	using AssetHolder_t = std::map<std::string, std::unique_ptr<Asset>>;

	AssetMeneger();
	~AssetMeneger();

//Loading all assets
	static bool loadAllAssets(const nlohmann::json &settings);

//Loading one type of assets

	static bool loadAssetsFromFile(const std::string & filename);

	template <typename T>
	static T * createAsset(const std::string name);

	template <typename T>
	static T * getAsset(const std::string name);

private:
	
	static AssetHolder_t _assets;

};


template<typename T>
static T * AssetMeneger::createAsset(const std::string name)
{
	_assets[name] = std::make_unique<T>(name);
	return static_cast<T *> (_assets[name].get());
}

template <typename T>
static T * AssetMeneger::getAsset(const std::string name)
{
	if (_assets.find(name) == _assets.end())
		return nullptr;
	else
		return static_cast<T*> (_assets[name].get());
}

}

