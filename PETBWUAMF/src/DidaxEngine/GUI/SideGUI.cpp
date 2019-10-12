#include "SideGUI.h"

Didax::SideGUI::SideGUI()
{
}


Didax::SideGUI::~SideGUI()
{
}

void Didax::SideGUI::setOnHourglassClicked(const std::function<int()>& func)
{
	_onHourglassClicked = func;
}

int Didax::SideGUI::onHourglassClicked()
{
	if (_onHourglassClicked != nullptr)
		return _onHourglassClicked();
	return -1;
}

void Didax::SideGUI::_init(GUIElementPrototype * prototype, AssetMeneger * assets)
{
	_widgets.push_back(std::make_unique<TextArea>());
	_widgets.push_back(std::make_unique<ImageWidget>());
	_text = static_cast<TextArea *>(_widgets[1].get());
	_hourglass = static_cast<ImageWidget *>(_widgets[2].get());

	//	root

	_root->setSize({ prototype->_values["widthR"], (prototype->_values["heightR"]) });
	_root->setPosition({ prototype->_values["xPosR"], (prototype->_values["yPosR"]) });

	auto textback = assets->getAsset<TextureAsset>(prototype->_strings["background"]);
	_root->setTexture(&(textback->_texture));

	_root->addChild(_text);
	_root->addChild(_hourglass);

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

}

void Didax::SideGUI::_initLogic(GUIElementPrototype * prototype, AssetMeneger * assets)
{
	_hourglass->setWidgetEvent(Widget::CallbackType::onHoverIn, [](Widget * w, float dt) {
		w->setColor({ 255,255,255,200 }); });
	_hourglass->setWidgetEvent(Widget::CallbackType::onHoverOut, [](Widget * w, float dt) {
		w->setColor({ 255,255,255,255 }); });
	_hourglass->setWidgetEvent(Widget::CallbackType::onPress, [this](Widget * w, float dt) {
		w->setColor({ 255,255,255,150 });
		this->hourglassClicked();
	});
	_hourglass->setWidgetEvent(Widget::CallbackType::onRelease, [](Widget * w, float dt) {
		if(w->isHovered())
			w->setColor({ 255,255,255,200 }); 
		else
			w->setColor({ 255,255,255,255 });
	});

}

void Didax::SideGUI::addTime(float t)
{
	_dT += t;
}

float Didax::SideGUI::getTime()const
{
	return _dT;
}
void Didax::SideGUI::hourglassClicked()
{
	auto state = this->onHourglassClicked();
	try
	{
		_text->setText(_displayedTexts[state]);
	}
	catch (std::exception e)
	{
		Logger::log(e.what());
		_text->setText(_displayedTexts[0]);
	}

	if(state == 2)
	{ 
		_dT = 0;
		_hourglass->setActive(false);
		_hourglass->setColor({ 255,255,255,50 });
		_root->onUpdate([this](Widget * w, float dt) {
			this->addTime(dt);
			if (this->getTime() >= 3)
				this->hourglassClicked();
		});
	}
	if (state == 0)
	{
		_root->resetOnUpdate();
		_hourglass->setActive(true);
		_hourglass->setColor({ 255,255,255,255 });
	}

}