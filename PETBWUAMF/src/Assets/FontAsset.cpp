#include "FontAsset.h"


FontAsset::loadAsset(const nlohmann::json & assetFile)
{
	_font.loadFromFile(_name);

}
