#include "MainGUI.h"

void Didax::MainGUI::_init(GUIElementPrototype * prototype, AssetMeneger * assets)
{
	for (size_t i = 0; i < 16; i++)
	{
		_widgets.push_back(std::make_unique<ImageWidget>());
		_borders[i] = static_cast<ImageWidget *>((_widgets.end() - 1)->get());
	}

	//root

	_root->setSize({ prototype->_values["widthR"], (prototype->_values["heightR"]) });
	auto text = assets->getAsset<TextureAsset>(prototype->_strings["background"]);
	_root->setTexture(&(text->_texture));
	for (size_t i = 0; i < 16; i++)
	{
		_root->addChild(_borders[i]);
	}

	//borders

	text = assets->getAsset<TextureAsset>(prototype->_strings["border"]);

	for (size_t i = 0; i < 16; i++)
	{
		_borders[i]->setPosition(POSITIONTAB[i].x-5, POSITIONTAB[i].y - 5);
		_borders[i]->setTexture(&(text->_texture));
		_borders[i]->setPrority(5);
	}

	// to have proper colors

	this->unsetReadyToChoose();

}

void Didax::MainGUI::_initLogic(GUIElementPrototype * prototype, AssetMeneger * assets)
{
	for (size_t i = 0; i < 16; i++)
	{
		_borders[i]->setWidgetEvent(Widget::CallbackType::onHoverIn, [this, i](Widget * w, float dt) {
			if (this->getIfCanBeChoosen(i))
				w->setColor(this->getColorFromSide(i,_side)*INTERACTIONCOLORS[1]);
		});
		_borders[i]->setWidgetEvent(Widget::CallbackType::onHoverOut, [this, i](Widget * w, float dt) {
			if (this->getIfCanBeChoosen(i))
				w->setColor(this->getColorFromSide(i, _side)*INTERACTIONCOLORS[0]);
		});
		_borders[i]->setWidgetEvent(Widget::CallbackType::onPress, [this, i](Widget * w, float dt) {
			if (this->getIfCanBeChoosen(i))
			{
				this->onPressElement(w);
				w->setColor(this->getColorFromSide(i, _side)*INTERACTIONCOLORS[2]);
			}			
		});
		_borders[i]->setWidgetEvent(Widget::CallbackType::onRelease, [this, i](Widget * w, float dt) {
			if (this->getIfCanBeChoosen(i))
			{
				if (this->getIfCanBeChoosen(i) && w->isHovered())
					w->setColor(this->getColorFromSide(i, _side)*INTERACTIONCOLORS[1]);
				else
					w->setColor(this->getColorFromSide(i, _side)*INTERACTIONCOLORS[0]);
			}		
		});
	}

}

Didax::MainGUI::MainGUI()
{
}

Didax::MainGUI::~MainGUI()
{
}

void Didax::MainGUI::setReadyToChoose(const bool posTab[16], YellowSide side)
{
	for (size_t i = 0; i < 16; i++)
	{
		_choosablePositions[i] = posTab[i];
		_side = side;
		if (!posTab[i])
			continue;	
		_borders[i]->setColor(this->getColorFromSide(i, side));
	}
}

sf::Color Didax::MainGUI::getColorFromSide(int p, YellowSide s)const
{
	sf::Color l = BORDERCOLORS[1];
	sf::Color r = BORDERCOLORS[2];
	if (s == YellowSide::right)
		std::swap(l, r);
	if (p < 8)
		return l;
	return r;
}

void Didax::MainGUI::unsetReadyToChoose()
{
	for (size_t i = 0; i < 16; i++)
	{
		_choosablePositions[i] = false;
		_borders[i]->setColor(BORDERCOLORS[0]);
	}
}

void Didax::MainGUI::setOnChoosed(const std::function<void()>& func)
{
	for (size_t i = 0; i < 16; i++)
	{
		this->_setPress(_borders[i], func);
	}
}

void Didax::MainGUI::resetOnChoosed()
{
	for (size_t i = 0; i < 16; i++)
	{
		this->_resetPress(_borders[i]);
	}
}

const bool * Didax::MainGUI::getChoosablePositions() const
{
	return _choosablePositions;
}

bool Didax::MainGUI::getIfCanBeChoosen(int pos) const
{
	return _choosablePositions[pos];
}

int Didax::MainGUI::getLastChoosed() const
{
	return 0;
}


