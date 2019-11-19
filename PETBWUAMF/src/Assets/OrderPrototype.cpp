#include "OrderPrototype.h"


void OrderPrototype::loadAsset(const nlohmann::json & assetFile)
{
	_description = assetFile["description"].get<std::string>();

	_texture = assetFile["texture"].get<std::string>();
	_icon = assetFile["icon"].get <std::string>();


	if (assetFile["allowedTypes"].size() == 0 && assetFile["allowedUnits"].size() == 0)
	{
		_canBeUsedOnAllUnit = true;
	}

	for (auto &a : assetFile["allowedTypes"])
	{
		_allowedTypes.push_back(a.get<std::string>());
	}
	for (auto &a : assetFile["allowedUnits"])
	{
		_allowedUnits.push_back(a.get<std::string>());
	}

	_target = assetFile["target"];
	_targetCount = assetFile["targetCount"];
	_cost = assetFile["cost"];
	_useNum = assetFile["useNum"];

}


void OrderPrototype::set_execute(const std::function<MoveRes(Unit *, const Move &)> & f)
{
	_execute = f;
}
