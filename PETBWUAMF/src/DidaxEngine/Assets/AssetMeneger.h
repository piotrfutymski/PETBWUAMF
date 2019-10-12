#pragma once
#include <map>
#include "nlohmann/json.hpp"
#include "SFML/Graphics.hpp"
#include <fstream>
#include <iostream>
#include "Asset.h"
#include "../Utility/Logger.h"
#include "BoardPrototype.h"
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

	bool loadAssetsFromFile(const std::string & filename);

	template <typename T>
	T * createAsset(const std::string name);

	template <typename T>
	T * getAsset(const std::string name);

private:
	
	AssetHolder_t _assets;

};



/*	enum class Quality {
		Brown, Gold
	};
	enum class Fraction {
		Humans
	};
	enum class UType {
		Warrior, Corsair, Scout
	};


	unsigned int _attack;
	unsigned int _deffence;
	unsigned int _health;

	bool _distanceUnit;

	Quality _quality;
	Fraction _fraction;
	UType _unitType;
	std::string _name;

	std::string texture;

*/



template<typename T>
inline T * AssetMeneger::createAsset(const std::string name)
{
	_assets[name] = std::make_unique<T>(name);
	return static_cast<T *> (_assets[name].get());
}

template <typename T>
inline T * AssetMeneger::getAsset(const std::string name)
{
	if (_assets.find(name) == _assets.end())
		return nullptr;
	else
		return static_cast<T*> (_assets[name].get());
}

}

