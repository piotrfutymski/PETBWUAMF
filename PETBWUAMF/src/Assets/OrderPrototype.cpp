#include "OrderPrototype.h"


void OrderPrototype::loadAsset(const nlohmann::json & assetFile)
{
	_description = assetFile["description"].get<std::string>();

	_texture = assetFile["texture"].get<std::string>();
	_icon = assetFile["icon"].get <std::string>();

	for ( auto &a : assetFile["targets"])
	{
		if (a.get<std::string>() == "position")
			_targets.push_back(OrderPrototype::Target::Position_target);
		else if(a.get<std::string>() == "unit")
			_targets.push_back(OrderPrototype::Target::Unit_target);
	}
}
