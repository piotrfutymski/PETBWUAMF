#include "AssetMeneger.h"

Didax::AssetMeneger::AssetMeneger()
{
}

Didax::AssetMeneger::~AssetMeneger()
{
}

bool Didax::AssetMeneger::loadAssetsFromFile(const std::string & filename)
{
	std::ifstream stream(filename);
	nlohmann::json assetFile;

	if (stream.is_open())
	{
		stream >> assetFile;
		Logger::log("Asset file loaded succesfully");
	}
	else
	{
		Logger::log("Unable to load assets succesfully");
		return false;
	}

	for (auto& element : assetFile)
	{
		Asset * a;
		if (element["type"] == "font")
			a = this->createAsset<FontAsset>(element["name"]);
		else if (element["type"] == "texture")
			a = this->createAsset<TextureAsset>(element["name"]);
		else if (element["type"] == "gui")
			a = this->createAsset<GUIElementPrototype>(element["name"]);
		else if (element["type"] == "board")
			a = this->createAsset<BoardPrototype>(element["name"]);
		else if (element["type"] == "unit")
			a = this->createAsset<UnitPrototype>(element["name"]);
		else if (element["type"] == "order")
			a = this->createAsset<OrderPrototype>(element["name"]);
		else
			return false;
		try
		{
			a->loadAsset(element);
		}
		catch (const std::exception & e)
		{
			Logger::log(e.what());
			return false;
		}

	}
	return true;
}
