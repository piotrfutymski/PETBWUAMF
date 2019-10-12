#include "GUIElementPrototype.h"


void Didax::GUIElementPrototype::loadAsset(const nlohmann::json & assetFile)
{
	auto files = assetFile["files"];
	auto values = assetFile["values"];

	for (nlohmann::json::iterator it = files.begin(); it != files.end(); ++it)
	{
		_fileNames[it.key()] = it.value().get<std::string>();
	}
	for (nlohmann::json::iterator it = values.begin(); it != values.end(); ++it)
	{
		_values[it.key()] = it.value();
	}
}
