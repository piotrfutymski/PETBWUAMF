#include "UnitPrototype.h"


void UnitPrototype::loadAsset(const nlohmann::json & assetFile)
{
	_attack =  assetFile["attack"];
	_power = assetFile["power"];
	_defence =  assetFile["defence"];
	_armor = assetFile["armor"];
	_health =  assetFile["health"];

	_rangedAttack = assetFile["rangedAttack"];
	if (_rangedAttack != 0)
		_range = assetFile["rangedRange"];
	else
		_range = 0;
	_chargeAttack = assetFile["chargeAttack"];
	_chargeDefence = assetFile["chargeDefence"];

	_move = assetFile["move"];
	_morale = assetFile["morale"];
	_formationSize = assetFile["formationSize"];

	_description = assetFile["description"].get<std::string>();
	_faction = assetFile["faction"].get<std::string>();
	_unitType = assetFile["unitType"].get<std::string>();
	_name = assetFile["name"].get<std::string>();
	_texture = assetFile["texture"].get<std::string>();

}
