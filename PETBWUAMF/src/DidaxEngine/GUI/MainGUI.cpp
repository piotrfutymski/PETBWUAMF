#include "MainGUI.h"
#include "../Engine.h"

Didax::MainGUI::MainGUI()
{
}


Didax::MainGUI::~MainGUI()
{
}

void Didax::MainGUI::startHourglassOnState()
{
	try
	{
		_text->setText(_displayedTexts[_state]);
	}
	catch (std::exception e)
	{
		Logger::log(e.what());
		_text->setText(_displayedTexts[0]);
	}

	if (_state == 2)
	{
		_dT = 0;
		_hourglass->setActive(false);
		_hourglass->setColor({ 255,255,255,50 });
		_root->onUpdate([this](Widget * w, float dt) {
			this->addTime(dt);
			if (this->getTime() >= 3)
				this->nextState();
		});
	}
	if (_state == 0)
	{
		_root->resetOnUpdate();
		_hourglass->setActive(true);
		_hourglass->setColor({ 255,255,255,255 });
	}
}

void Didax::MainGUI::nextState()
{
	if (_state == 2)
		_state = 0;
	else
		_state++;
	this->startHourglassOnState();
}


void Didax::MainGUI::_init(GUIElementPrototype * prototype, AssetMeneger * assets)
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

void Didax::MainGUI::_initLogic(GUIElementPrototype * prototype, AssetMeneger * assets, const std::vector<std::function<void()>> & func)
{
	this->createEmptyButton("hourglass", _hourglass);
	this->setOnPressToButton("hourglass", [this]() {
		this->nextState();
	});
	this->createEmptyButton("exit",_exitButton);
	this->setOnPressToButton("exit", func[0]);

}

void Didax::MainGUI::addTime(float t)
{
	_dT += t;
}

float Didax::MainGUI::getTime()const
{
	return _dT;
}

Didax::Widget * Didax::MainGUI::getHourglass() const
{
	return _hourglass;
}
