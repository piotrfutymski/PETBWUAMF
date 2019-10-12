#include "FontAsset.h"


void Didax::FontAsset::loadAsset(const nlohmann::json & assetFile)
{
	_font.loadFromFile(_name);

}
