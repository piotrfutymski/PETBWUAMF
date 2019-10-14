#include "UnitPrototype.h"


void Didax::UnitPrototype::loadAsset(const nlohmann::json & assetFile)
{
	_attack =  assetFile["attack"];
	_defense =  assetFile["defense"];
	_armor = assetFile["armor"];
	_health =  assetFile["health"];

	_rangedAttack = assetFile["rangedAttack"];
	_chargeAttack = assetFile["chargeAttack"];
	_chargeDefense = assetFile["chargeDefense"];

	_description = assetFile["description"].get<std::string>();
	_faction = assetFile["faction"].get<std::string>();
	_unitType = assetFile["unitType"].get<std::string>();
	_name = assetFile["name"].get<std::string>();
	_texture = assetFile["texture"].get<std::string>();
}
