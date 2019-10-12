#include "BoardPrototype.h"

void Didax::BoardPrototype::loadAsset(const nlohmann::json & assetFile)
{

	_backgroundTexture = assetFile["backgroundTexture"].get<std::string>();
	_mainGuiPos.x = assetFile["mainGuiPosX"];
	_mainGuiPos.y = assetFile["mainGuiPosY"];
	_mainGuiName = assetFile["mainGuiName"].get<std::string>();
	_sideGuiPos.x = assetFile["sideGuiPosX"];
	_sideGuiPos.y = assetFile["sideGuiPosY"];
	_sideGuiName = assetFile["sideGuiName"].get<std::string>();	

}
