#include "BuffPrototype.h"

void BuffPrototype::loadAsset(const nlohmann::json & assetFile)
{
	_time = assetFile["time"];
	_Fvalue = assetFile["firstValue"];
	_Svalue = assetFile["secondValue"];
}
