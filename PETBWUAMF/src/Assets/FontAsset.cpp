#include "FontAsset.h"


void FontAsset::loadAsset(const nlohmann::json & assetFile)
{
	_font.loadFromFile(_name);

}
