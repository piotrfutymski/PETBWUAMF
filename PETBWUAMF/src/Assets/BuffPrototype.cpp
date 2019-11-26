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

int BuffPrototype::toUParameter(const std::string & p)
{

	if (p == "Protection")
		return 3;
	else if (p == "Morale")
		return 0;
	else if (p == "Armor")
		return 4;
	else if (p == "Attack")
		return 2;
	else if (p == "ChargeAttack")
		return 8;
	else if (p == "ChargeDefence")
		return 7;
	else if (p == "Defence")
		return 5;
	else if (p == "Health")
		return 1;
	else if (p == "Move")
		return 10;
	else if (p == "Range")
		return 9;
	else if (p == "RangedAttack")
		return 6;
	else 
		return -1 * std::stoi(p);

}