#include "SideGUI.h"

Didax::SideGUI::SideGUI()
{
}


Didax::SideGUI::~SideGUI()
{
}

void Didax::SideGUI::setOnHourglassClicked(const std::function<void()>& func)
{
	this->_setPress(_hourglass, func);
}

void Didax::SideGUI::setOnExitButtonClicked(const std::function<void()>& func)
{
	this->_setPress(_exitButton, func);
}

void Didax::SideGUI::startHourglassOnState(int state)
{
	try
	{
		_text->setText(_displayedTexts[state]);
	}
	catch (std::exception e)
	{
		Logger::log(e.what());
		_text->setText(_displayedTexts[0]);
	}

	if (state == 2)
	{
		_dT = 0;
		_hourglass->setActive(false);
		_hourglass->setColor({ 255,255,255,50 });
		_root->onUpdate([this](Widget * w, float dt) {
			this->addTime(dt);
			if (this->getTime() >= 3)
				this->onPressElement(this->getHourglass());
		});
	}
	if (state == 0)
	{
		_root->resetOnUpdate();
		_hourglass->setActive(true);
		_hourglass->setColor({ 255,255,255,255 });
	}
}


void Didax::SideGUI::_init(GUIElementPrototype * prototype, AssetMeneger * assets)
{
	_widgets.push_back(std::make_unique<TextArea>());
	_widgets.push_back(std::make_unique<ImageWidget>());
	_widgets.push_back(std::make_unique<ImageWidget>());
	_text = static_cast<TextArea *>(_widgets[1].get());
	_hourglass = static_cast<ImageWidget *>(_widgets[2].get());
	_exitButton = static_cast<ImageWidget *>(_widgets[3].get());

	//	root

	_root->setSize({ prototype->_values["widthR"], (prototype->_values["heightR"]) });
	_root->setPosition({ prototype->_values["xPosR"], (prototype->_values["yPosR"]) });

	auto textback = assets->getAsset<TextureAsset>(prototype->_strings["background"]);
	_root->setTexture(&(textback->_texture));

	_root->addChild(_text);
	_root->addChild(_hourglass);
	_root->addChild(_exitButton);

	//	text

	_displayedTexts[0] = prototype->_strings["dispText0"];
	_displayedTexts[1] = prototype->_strings["dispText1"];
	_displayedTexts[2] = prototype->_strings["dispText2"];

	_text->setPosition({ prototype->_values["xPosT"], (prototype->_values["yPosT"]) });
	_text->setText(_displayedTexts[0]);
	
	auto f = assets->getAsset<FontAsset>(prototype->_strings["font"]);

	_text->setFont(&(f->_font));
	_text->setFontColor(sf::Color::White);

	// hourglass

	_hourglass->setPosition({ prototype->_values["xPosH"], (prototype->_values["yPosH"]) });
	textback = assets->getAsset<TextureAsset>(prototype->_strings["hourglass"]);
	_hourglass->setTexture(&(textback->_texture));

	// exit

	_exitButton->setPosition({ prototype->_values["xPosE"], (prototype->_values["yPosE"]) });
	textback = assets->getAsset<TextureAsset>(prototype->_strings["exit"]);
	_exitButton->setTexture(&(textback->_texture));

}

void Didax::SideGUI::_initLogic(GUIElementPrototype * prototype, AssetMeneger * assets)
{
	this->_initElement(_hourglass);
	this->_initElement(_exitButton);

}

void Didax::SideGUI::addTime(float t)
{
	_dT += t;
}

float Didax::SideGUI::getTime()const
{
	return _dT;
}

Didax::Widget * Didax::SideGUI::getHourglass() const
{
	return _hourglass;
}
