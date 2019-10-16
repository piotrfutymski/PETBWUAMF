#include "OrderPrototype.h"


void Didax::OrderPrototype::loadAsset(const nlohmann::json & assetFile)
{
	_description = assetFile["description"].get<std::string>();

	_texture = assetFile["texture"].get<std::string>();
}
