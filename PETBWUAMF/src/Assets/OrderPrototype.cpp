#include "OrderPrototype.h"


void OrderPrototype::loadAsset(const nlohmann::json & assetFile)
{
	_description = assetFile["description"].get<std::string>();

	_texture = assetFile["texture"].get<std::string>();
	_icon = assetFile["icon"].get <std::string>();

	for ( auto &a : assetFile["targets"])
	{
		if (a.get<std::string>() == "position")
			_targets.push_back(OrderPrototype::TargetType::Position_target);
		else if(a.get<std::string>() == "unit")
			_targets.push_back(OrderPrototype::TargetType::Unit_target);
	}
}

void OrderPrototype::set_canBeUsed(const std::function<bool(Unit*)>& f)
{
	_canBeUsed = f;
}

void OrderPrototype::set_getProperTargets(const std::function<std::vector<Target>(Unit *, int)> & f)
{
	_getProperTargets = f;
}

void OrderPrototype::set_execute(const std::function<bool(Unit *, const Move &)> & f)
{
	_execute = f;
}
