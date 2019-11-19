#include "BuffPrototype.h"

void BuffPrototype::loadAsset(const nlohmann::json & assetFile)
{
	_time = assetFile["time"];
	if (assetFile["begin"].size() == 2)
	{
		beginFlag = true;
		_begin = std::make_pair(assetFile["begin"]["value"].get<std::string>(), assetFile["begin"]["target"].get<std::string>());
	}

	if (assetFile["turnEnd"].size() == 2)
	{
		turnFlag = true;
		_turnEnd = std::make_pair(assetFile["turnEnd"]["value"].get<std::string>(), assetFile["turnEnd"]["target"].get<std::string>());
	}

	if (assetFile["end"].size() == 2)
	{
		endFlag = true;
		_end = std::make_pair(assetFile["end"]["value"].get<std::string>(), assetFile["end"]["target"].get<std::string>());
	}

	for (auto &file : assetFile["flags"])
	{

	}

}