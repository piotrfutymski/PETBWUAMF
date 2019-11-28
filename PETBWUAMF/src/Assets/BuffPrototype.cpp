#include "BuffPrototype.h"

void BuffPrototype::loadAsset(const nlohmann::json & assetFile)
{
	_name = assetFile["name"].get<std::string>();

	_type = BuffPrototype::BuffType(assetFile["buffType"]);
	if (_type == BuffType::ParameterBoost)
	{
		_parameterToBoost = UParameter(assetFile["parameter"]);
		_time = assetFile["time"];
		_value = assetFile["value"];
		if (_value == 0)
			_valueParameter = UParameter(assetFile["valueParameter"]);
	}
	_isGood = assetFile["isGood"];

}

bool BuffPrototype::onTurnEnd(float & v) const
{
	if (_type == BuffType::Bleeding)
	{
		v *= 0.75;
		if (v < 0.5)
			return true;
	}
	return false;
}
