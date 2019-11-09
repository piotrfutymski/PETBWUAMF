#include "GUIElementPrototype.h"


void GUIElementPrototype::loadAsset(const nlohmann::json & assetFile)
{
	auto files = assetFile["strings"];
	auto values = assetFile["values"];

	for (nlohmann::json::iterator it = files.begin(); it != files.end(); ++it)
	{
		_strings[it.key()] = it.value().get<std::string>();
	}
	for (nlohmann::json::iterator it = values.begin(); it != values.end(); ++it)
	{
		_values[it.key()] = it.value();
	}
}
