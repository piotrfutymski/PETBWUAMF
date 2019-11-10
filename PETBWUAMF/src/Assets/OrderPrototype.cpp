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

void OrderPrototype::set_canBeUsed(const std::function<bool(Unit*)>& f)
{
	_canBeUsed = f;
}

void OrderPrototype::set_isProperAsTargetP(const std::function<bool(Unit*, int, const sf::Vector2i&)>& f)
{
	_isProperAsTargetP = f;
}

void OrderPrototype::set_isProperAsTargetU(const std::function<bool(Unit*, int, size_t)>& f)
{
	_isProperAsTargetU = f;
}

void OrderPrototype::set_execute(const std::function<bool(Unit *, const Move &)> & f)
{
	_execute = f;
}
