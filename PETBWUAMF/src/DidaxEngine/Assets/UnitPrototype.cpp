#include "UnitPrototype.h"


void Didax::UnitPrototype::loadAsset(const nlohmann::json & assetFile)
{
	_attack =  assetFile["attack"];
	_defence =  assetFile["defence"];
	_health =  assetFile["health"];

	_distanceUnit = assetFile["distance"];

	_fraction = assetFile["fraction"].get<std::string>();
	_unitType = assetFile["unitType"].get<std::string>();
	_name = assetFile["name"].get<std::string>();
	_texture = assetFile["texture"].get<std::string>();
}
