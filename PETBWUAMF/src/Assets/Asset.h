#pragma once

#include <SFML/Graphics.hpp>
#include "nlohmann/json.hpp"
#include "../Utility/Logger.h"
#include <map>


class Asset
{
public:

	Asset(const std::string & name);
	~Asset();


	virtual void loadAsset(const nlohmann::json & assetFile) = 0;

	const std::string & getName()const;

protected:

	std::string _name;

};

