#include "BoardGUI.h"

void Didax::BoardGUI::_init(AssetMeneger * assets)
{
	for (size_t i = 0; i < 16; i++)
	{
		_widgets.push_back(std::make_unique<SwitchableImage>());
		_borders[i] = static_cast<SwitchableImage *>((_widgets.end() - 1)->get());
	}

	//root

	_root->setSize({ _prototype->_values["widthR"], (_prototype->_values["heightR"]) });
	auto text = assets->getAsset<TextureAsset>(_prototype->_strings["background"]);
	_root->setTexture(&(text->_texture));
	for (size_t i = 0; i < 16; i++)
	{
		_root->addChild(_borders[i]);
	}

	//borders

	auto text0 = &(assets->getAsset<TextureAsset>(_prototype->_strings["border0"])->_texture);
	auto text1 = &(assets->getAsset<TextureAsset>(_prototype->_strings["border1"])->_texture);
	auto text2 = &(assets->getAsset<TextureAsset>(_prototype->_strings["border2"])->_texture);

	for (size_t i = 0; i < 16; i++)
	{
		_borders[i]->setPosition(UNITPOSITIONTAB[i].x-5, UNITPOSITIONTAB[i].y - 5);
		_borders[i]->init({ text0,text1,text2 });
	}

	// to have proper colors
	this->unsetReadyToChoose();

}

void Didax::BoardGUI::_initLogic(AssetMeneger * assets)
{
	for (size_t i = 0; i < 16; i++)
	{
		this->createEmptyButton("Pos" + std::to_string(i), _borders[i]);
	}

}

Didax::BoardGUI::BoardGUI(GUIElementPrototype * prototype):GUIElement(prototype)
{
}

Didax::BoardGUI::~BoardGUI()
{
}

void Didax::BoardGUI::setReadyToChoose(const bool posTab[16])
{
	for (size_t i = 0; i < 16; i++)
	{
		_choosablePositions[i] = posTab[i];
		if (!posTab[i])
			continue;	
		if (i < 8)
			_borders[i]->setOption(1);
		else
			_borders[i]->setOption(2);
	}
}


void Didax::BoardGUI::unsetReadyToChoose()
{
	for (size_t i = 0; i < 16; i++)
	{
		_choosablePositions[i] = false;
		_borders[i]->setOption(0);
	}
}


const bool * Didax::BoardGUI::getChoosablePositions() const
{
	return _choosablePositions;
}

bool Didax::BoardGUI::getIfCanBeChoosen(int pos) const
{
	return _choosablePositions[pos];
}

int Didax::BoardGUI::getLastChoosed() const
{
	return 0;
}
